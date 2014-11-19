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

typedef struct _ImageInfo
{
	unsigned int id;
	unsigned int offset;
	unsigned int width;
	unsigned int height;
	unsigned int size;
}ImageInfo;//total 20 bytes

typedef struct
{
	unsigned char		flag;
	//std::string			m_Name;        // for reconstruction
	::ImageInfo			*pImageHead;
	const unsigned char *pDatas;		//����û���ͼ�����ݵķ��䣬���棬�ͷš�
										//�Ƿ�Ӧ�ð��ļ���д������һ�㣬����ʵ��Ӧ�ÿ����Ƿ����ͼ�����ݵĿռ�
}ImageData;

class ImageMgr
{
public:

// Lifetime.

	ImageMgr( void ) : m_nImagesCount(0), m_nBaseOffset(0) {  /* ... */ }
    virtual ~ImageMgr( void ) { /* ... */ };


// management.

    HImage		AddImage(const ImageData* pBitmap);
    //HImage		GetImage(const char* name);
	HImage		GetImage(const unsigned int index);
	HImage      GetImageByID(const unsigned int bitmapID);
    void		DeleteImage( HImage himg );
	const ImageData* GetImageData(HImage himg); 

	void		CleanAllImages();

// Texture query.

// 	const std::string& GetName( HImage himg ) const
// 	{  return ( m_Images.Dereference( himg )->m_Name );  }
	int GetWidth( HImage himg ) const
	{  return ( m_Images.Dereference( himg )->pImageHead->width );  }
	int GetHeight( HImage himg ) const
	{  return ( m_Images.Dereference( himg )->pImageHead->height );  }
	int GetImagesCount() const
	{  return ( m_nImagesCount );  }

	int AssignID(int id);
protected:
	typedef HandleMgr <ImageData, HImage> HImageHandleMgr;

	// Index by name into db.

	// case-insensitive string comparison predicate
// 	struct istring_less
// 	{
// 		bool operator () ( const std::string& l, const std::string& r ) const
// 		{  return ( ::stricmp( l.c_str(), r.c_str() ) < 0 );  }
// 	};

	typedef std::map <unsigned int, HImage> NameIndex;
	typedef std::pair <NameIndex::iterator, bool> NameIndexInsertRc;

// Private data.

	HImageHandleMgr			m_Images;
	NameIndex				m_NameIndex;
	CxIOFile				m_fPacketFile;
	unsigned int			m_nImagesCount;
	unsigned int			m_nBaseOffset;
};




#endif	//IMAGAGEMGR_H
