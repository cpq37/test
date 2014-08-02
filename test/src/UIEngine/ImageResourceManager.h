#ifndef IMAGE_RESOURCE_MANAGER_H
#define IMAGE_RESOURCE_MANAGER_H

#include <string>
#include <list>


namespace UIEngine
{
	typedef struct
	{
		unsigned int U32_Id;
		unsigned int U32_Offset;
		unsigned int U32_Width;
		unsigned int U32_Height;
		unsigned int U32_Size;
	}ImageInfo;


	class CImageResourceManager
	{
	public:
		class BitmapMap
		{
		public:
			BitmapMap()
			{	
				m_ImageDatas = NULL;
				m_refcount = 0;
			}
			virtual ~BitmapMap()
			{

			}
			ImageInfo					m_ImageIndex;
			const unsigned char*		m_ImageDatas;
			std::string					m_filename;
			long						m_refcount;
		};

		CImageResourceManager();
		~CImageResourceManager();

		static CImageResourceManager* GetInstance();
		void		AddImage(BitmapMap* pBitmap);
		void		ReleasImage(unsigned int bitmapID);
		BitmapMap*	GetImage(unsigned int bitmapID);
	private:
		static CImageResourceManager *m_singelton;
		std::list<BitmapMap*>	m_pImageList;
		unsigned int			m_nImageSize;
		
	};
}//UIEngine

#endif