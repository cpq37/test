#include "ImageResourceManager.h"
#include "../Common/setdebugnew.h"


#define TEST_FILE "test.pack"

using namespace UIEngine;

CImageDatasManager *CImageDatasManager::m_singelton = NULL;

CImageDatasManager::CImageDatasManager()
{
	m_nImagesCount = 0;
	m_nBaseOffset = 0;
	m_pDatasBuffer = NULL;
}

CImageDatasManager::~CImageDatasManager()
{
	
	CleanAllImages();
	if( m_pDatasBuffer )
	{
		free((void*)m_pDatasBuffer);
		m_pDatasBuffer = NULL;
	}

	//delete m_singelton;
	m_singelton = NULL;
}


CImageDatasManager *CImageDatasManager::GetInstance()
{
	CImageDatasManager *result = NULL;

	if(m_singelton == NULL)
	{
		m_singelton = new CImageDatasManager();
	}
	result = m_singelton;

	return result;
}

void CImageDatasManager::CleanAllImages()
{
	std::list<ImagdeData*>::iterator it = m_pImageHeadList.begin();
	while (it != m_pImageHeadList.end())
	{
		ImagdeData *pImageData = *it;
		if( 1 == pImageData->flag )
		{
			if( pImageData->pImageHead )
			{
				delete pImageData->pImageHead;
				pImageData->pImageHead = NULL;
			}
		}
		delete *it;
		*it = NULL;
		it++;
	}
	m_pImageHeadList.clear();
	m_fPacketFile.Close();
}

void CImageDatasManager::AddImage(ImagdeData* pBitmap)
{
	if( NULL != pBitmap )
	{
		//ImagdeData *pImageData = new ImagdeData;
		if( 0 == pBitmap->pImageHead->id )
		{
			pBitmap->pImageHead->id = m_pImageHeadList.size() + 1;
		}
// 		if( 0 == m_pImageHeadList.size() )
// 		{
// 			pBitmap->pImageHead->offset = 0;
// 		}
// 		else
// 		{
// 			ImagdeData *pPrevImage = m_pImageHeadList.back();
// 			pBitmap->pImageHead->offset = pPrevImage->pImageHead->offset + pPrevImage->pImageHead->size;
// 		}
		
		//memcpy(pImageData, pBitmap, sizeof(ImagdeData));
		m_pImageHeadList.push_back(pBitmap);
		m_nImagesCount++;
	}
}
void CImageDatasManager::AddImage(ImageInfo* pImageInfo, const unsigned char *datas)
{
	if(NULL != pImageInfo && NULL != datas)
	{
		ImagdeData *pImageData = new ImagdeData;

		if( 0 == pImageInfo->id )
		{
			pImageInfo->id = m_pImageHeadList.size() + 1;
		}
		if( 0 == m_pImageHeadList.size() )
		{
			pImageInfo->offset = 0;
		}
		else
		{
			ImagdeData *pPrevImage = m_pImageHeadList.back();
			pImageInfo->offset = pPrevImage->pImageHead->offset + pPrevImage->pImageHead->size;
		}

		pImageData->pImageHead = pImageInfo;
		pImageData->pDatas = datas;
		m_pImageHeadList.push_back(pImageData);
		//m_pImageSaveDatas.push_back(datas);
		m_nImagesCount++;
	}
}

void CImageDatasManager::SaveAllImages()
{
	CxIOFile file;

	if( m_nImagesCount != m_pImageHeadList.size() )
	{
		m_nImagesCount = m_pImageHeadList.size();
	}

	if( 0 == m_nImagesCount )
		return;


	file.Open(TEST_FILE, "wb+");
	file.Write(&m_nImagesCount, sizeof(m_nImagesCount), 1);
	unsigned int tempOffset = sizeof(m_nImagesCount) + sizeof(ImageInfo)*m_pImageHeadList.size();

	std::list<ImagdeData*>::iterator it_head = m_pImageHeadList.begin();
	while( it_head != m_pImageHeadList.end() )
	{
		ImagdeData *pTemp = *it_head;
		
		pTemp->pImageHead->offset = tempOffset;
		file.Write((const void*)(pTemp->pImageHead), sizeof(ImageInfo), 1);
		it_head++;
		tempOffset += pTemp->pImageHead->size;
	}

	std::list<ImagdeData*>::iterator  it_datas = m_pImageHeadList.begin();
	while( it_datas != m_pImageHeadList.end() )
	{
		ImagdeData *pTemp = *it_datas;
		file.Write(pTemp->pDatas, sizeof(char), pTemp->pImageHead->size);
		it_datas++;
	}
	file.Close();
}

bool CImageDatasManager::ReadImagePacket(const char *file)
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
	m_nBaseOffset += sizeof(nImageCount);

	if( m_nImagesCount )
	{
		CleanAllImages();
	}

	for(int i=0; i<nImageCount; i++)
	{
		ImagdeData *pImageData = new ImagdeData;
		memset(pImageData, 0, sizeof(ImagdeData));
		pImageData->pImageHead = new ImageInfo;
		memset(pImageData->pImageHead, 0, sizeof(ImageInfo));
		readSize = m_fPacketFile.Read(pImageData->pImageHead, sizeof(ImageInfo), 1);
		pImageData->flag = 1;
		AddImage(pImageData);
		m_nBaseOffset += sizeof(ImageInfo);
	}

	return ret;
}

const unsigned char* CImageDatasManager::GetImageDatas(unsigned int bitmapID)
{
	if( m_pDatasBuffer )
	{
		free((void*)m_pDatasBuffer);
		m_pDatasBuffer = NULL;
	}

	return m_pDatasBuffer;
}

const unsigned char* CImageDatasManager::GetImageDatasByIndex(unsigned int index, ImagdeData *pBitmap)
{
	if( m_pDatasBuffer )
	{
		free((void*)m_pDatasBuffer);
		m_pDatasBuffer = NULL;
	}

	std::list<ImagdeData*>::iterator it = m_pImageHeadList.begin();
	int count = 0; 
	while(it != m_pImageHeadList.end())
	{
		if( count == index )
		{
			ImagdeData *pImageData = *it;
			bool ret = m_fPacketFile.Seek(/*m_nBaseOffset+*/pImageData->pImageHead->offset, SEEK_SET);
			if( true == ret )
			{
				int size = pImageData->pImageHead->size;
				m_pDatasBuffer = (const unsigned char*)malloc(size*sizeof(char));
				m_fPacketFile.Read((void*)m_pDatasBuffer, size, 1);
				if( pBitmap )
				{
					memcpy(pBitmap->pImageHead, pImageData->pImageHead, sizeof(ImageInfo));
				}
			}

			return m_pDatasBuffer;
		}
		it++;
		count++;
	}

	return m_pDatasBuffer;
}



void CImageDatasManager::ReleasImageDatasBuffer()
{
	if( m_pDatasBuffer )
	{
		free((void*)m_pDatasBuffer);
		m_pDatasBuffer = NULL;
	}

}