#ifndef IMAGAGEMGR_H
#define IMAGAGEMGR_H

#include <vector>
#include <map>
#include <cassert>

#include "handle.h"
#include "handlemgr.h"
#include "../Common/xFile/xiofile.h"

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

typedef struct
{
	unsigned char		flag;
	//std::string			m_Name;        // for reconstruction
	ImageInfo			*pImageHead;
	const unsigned char *pDatas;		//还是没解决图像数据的分配，保存，释放。
										//是否应该把文件读写放在上一层，根据实际应用考虑是否分配图像数据的空间
}ImageData;

class ImageMgr
{
public:

// Lifetime.

	ImageMgr( void )  {  /* ... */  }
    virtual ~ImageMgr( void ) { /* ... */ };


// management.

    HImage		AddImage(const ImageData* pBitmap);
    HImage		GetImage   ( const char* name );
    //void		DeleteImage( HImage himg );

	void		CleanAllImages();

// Texture query.

// 	const std::string& GetName( HImage himg ) const
// 	{  return ( m_Images.Dereference( himg )->m_Name );  }
	int GetWidth( HImage himg ) const
	{  return ( m_Images.Dereference( himg )->pImageHead->width );  }
	int GetHeight( HImage himg ) const
	{  return ( m_Images.Dereference( himg )->pImageHead->height );  }

protected:
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




#endif	//IMAGAGEMGR_H
