#ifndef IMAGE_RESOURCE_MANAGER_H
#define IMAGE_RESOURCE_MANAGER_H

#include <string>
#include <list>
#include "../Common/xFile/xiofile.h"



namespace UIEngine
{
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
        const unsigned char *pDatas;
    }ImagdeData;
	class CImageDatasManager
	{
	public:
		CImageDatasManager();
		~CImageDatasManager();

		static CImageDatasManager* GetInstance();
		void		AddImage(ImagdeData* pBitmap);
		void		AddImage(ImageInfo* pImageInfo, const unsigned char *datas);
		//void		ReleasImage(unsigned int bitmapID);
		//ImageInfo*	GetImageInfo(unsigned int bitmapID);
		const unsigned char* GetImageDatas(unsigned int bitmapID);
		const unsigned char* GetImageDatasByIndex(unsigned int index, ImagdeData *pBitmap);
		void		ReleasImageDatasBuffer();
		
		void		CleanAllImages();
		int			GetImagesCount(){return m_nImagesCount;};

		//void		SaveImageInfo();
		//void		SaveImageDatas();
		void		SaveAllImages();
		bool		ReadImagePacket(const char* file=NULL);
	private:
		static CImageDatasManager *m_singelton;
		std::list<ImagdeData*>	m_pImageHeadList;
		//std::list<const unsigned char*> m_pImageSaveDatas;
		unsigned int			m_nImagesCount;
		unsigned int			m_nBaseOffset;
		const unsigned char		*m_pDatasBuffer;
		CxIOFile				m_fPacketFile;
		
	};
}//UIEngine

#endif
