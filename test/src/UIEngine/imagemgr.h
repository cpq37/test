#ifndef IMAGAGEMGR_H
#define IMAGAGEMGR_H

#include <vector>
#include <map>
#include <cassert>

#include "handle.h"
#include "handlemgr.h"
#include "../Common/xFile/xiofile.h"

#define TEST_FILE "test.pack"

struct tagImage  {  };
typedef Handle <tagImage> HImage;

typedef struct
{
	unsigned int id;
	unsigned int offset;
	unsigned int width;
	unsigned int height;
	unsigned int size;
}ImageInfo;

struct ImageData
{
	unsigned char		flag;
	std::string			m_Name;        // for reconstruction
	ImageInfo			*pImageHead;
	const unsigned char *pDatas;		//还是没解决图像数据的分配，保存，释放。
										//是否应该把文件读写放在上一层，根据实际应用考虑是否分配图像数据的空间
};

class ImageMgr
{
public:

// Lifetime.

	ImageMgr( void )  {  /* ... */  }
	~ImageMgr( void );

	bool		SaveImagesToFile(const char* file=NULL);
	bool		ReadImagePacket(const char* file=NULL);
// management.

	HImage		AddImage(const ImagdeData* pBitmap);
	HImage		GetImage   ( const char* name );
	void		DeleteImage( HImage himg );

	void		CleanAllImages();

// Texture query.

	const std::string& GetName( HImage himg ) const
	{  return ( m_Images.Dereference( himg )->m_Name );  }
	int GetWidth( HImage himg ) const
	{  return ( m_Images.Dereference( himg )->pImageHead->width );  }
	int GetHeight( HImage himg ) const
	{  return ( m_Images.Dereference( himg )->pImageHead->height );  }

private:
	typedef HandleMgr <ImageData, HImage> HTextureMgr;

	// Index by name into db.

	// case-insensitive string comparison predicate
	struct istring_less
	{
		bool operator () ( const std::string& l, const std::string& r ) const
		{  return ( ::stricmp( l.c_str(), r.c_str() ) < 0 );  }
	};

	typedef std::map <std::string, HImage, istring_less > NameIndex;
	typedef std::pair <NameIndex::iterator, bool> NameIndexInsertRc;

// Private data.

	HTextureMgr				m_Images;
	NameIndex				m_NameIndex;
	CxIOFile				m_fPacketFile;
	unsigned int			m_nImagesCount;
	unsigned int			m_nBaseOffset;
};

HImage ImageMgr::AddImage(const ImagdeData* pBitmap)
{
	assert(pBitmap);
	
	ImagdeData *pImageData = NULL;
	HImage hImage = HImage();
	pImageData = m_Images.Acquire( hImage );

	char str[32];
	if( pImageData )
	{
		sprintf(str, "%d", hImage.GetHandle());
	}
// 	else
// 	{
// 		return 0;
// 	}
	// insert
	NameIndexInsertRc rc =
		m_NameIndex.insert( std::make_pair( str, hImage ) );
	if ( rc.second )
	{
		// this is a new insertion
		memcpy(pImageData, pBitmap, sizeof(ImagdeData));
		m_nImagesCount++;

	}
	return ( rc.first->second );
}

void ImageMgr::CleanAllImages()
{
	NameIndex::iterator it = m_NameIndex.begin();
	while (it != m_NameIndex.end())
	{
		ImagdeData *pImageData = m_Images->Acquire(it->second);
		if( pImageData )
		{
			if( pImageData->pImageHead )
			{
				delete pImageData->pImageHead;
				pImageData->pImageHead = NULL;
			}
			if( pImageData->pDatas )
			{
				delete pImageData->pDatas;
				pImageData->pDatas = NULL;
			}
		}
		delete pImageData;
		pImageData = NULL;
		// delete from index
		m_NameIndex.erase(it);
		// delete from db
		m_Images.Release(it->second);
		it++;
	}

	m_NameIndex.clear();
	m_fPacketFile.Close();
	m_nImagesCount = 0;
}

bool ImageMgr::SaveImagesToFile(const char* file)
{
	CxIOFile file;
	bool ret = false;

	if( m_nImagesCount != m_NameIndex.size() )
	{
		m_nImagesCount = m_NameIndex.size();
	}

	if( 0 == m_nImagesCount )
		return ret;

	if( NULL == file )
		ret = file.Open(TEST_FILE, "wb+");
	else
		ret = file.Open(file, "wb+");

	if( ret )
		file.Write(&m_nImagesCount, sizeof(m_nImagesCount), 1);
	else
		return ret;

	NameIndex::iterator it_head = m_NameIndex.begin();
	unsigned int tempOffset = 0;
	while( it_head != m_NameIndex.end() )
	{
		ImagdeData *pTemp =  m_Images->Acquire(it_head->second);
		pTemp->pImageHead->offset = tempOffset;
		file.Write((const void*)(pTemp->pImageHead), sizeof(ImageInfo), 1);
		tempOffset += pTemp->pImageHead->size;
		it_head++;
	}

	NameIndex::iterator  it_datas = m_NameIndex.begin();
	while( it_datas != m_NameIndex.end() )
	{
		ImagdeData *pTemp = m_Images->Acquire(it_datas->second);
		file.Write(pTemp->pDatas, sizeof(char), pTemp->pImageHead->size);
		it_datas++;
	}


	ret = file.Close();
	return ret;
}

bool ImageMgr::ReadImagePacket(const char* file)
{
	bool ret = false;
	size_t readSize = 0;
	if( NULL == file )
	{
		ret = m_fPacketFile.Open(TEST_FILE, "rb+");
	}
	else
	{
		ret = m_fPacketFile.Open(file, "rb+");
	}

	if( ret == false )
	{
		return ret;
	}

	unsigned int nImageCount = 0;
	readSize = m_fPacketFile.Read(&nImageCount, sizeof(m_nImagesCount), 1);
	//m_nBaseOffset += sizeof(nImageCount);

	if( m_nImagesCount )
	{
		CleanAllImages();
	}

	for(int i=0; i<nImageCount; i++)
	{
		ImagdeData imageData;
		memset(&imageData, 0, sizeof(ImagdeData));
		imageData.pImageHead = new ImageInfo;
		memset(imageData.pImageHead, 0, sizeof(ImageInfo));
		readSize = m_fPacketFile.Read(imageData.pImageHead, sizeof(ImageInfo), 1);
		imageData.flag = 1;
		AddImage(&imageData);
		//m_nBaseOffset += sizeof(ImageInfo);
	}

	return ret;
}

HImage	ImageMgr::GetImage( const char* name )
{
    // find
	NameIndex::iterator it = m_NameIndex.find( std::string(name) );
// 	if ( rc.second )
// 	{
// 		ImagdeData *pImageDat = m_Images.Acquire( it->second );
// 	}
	return ( it->second );
}

#endif	//IMAGAGEMGR_H
