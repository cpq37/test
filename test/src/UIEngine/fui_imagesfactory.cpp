#include "fui_imagesfactory.h"

#ifdef _DEBUG 
#include "vld.h" 
#endif

#define TEST_FILE "test.pack"


FUI_ImagesFactory *FUI_ImagesFactory::m_singelton = NULL;

FUI_ImagesFactory::FUI_ImagesFactory()
{
}

FUI_ImagesFactory::~FUI_ImagesFactory()
{
	m_fPacketFile.Close();
    SaveImagesToFile();
	CleanAllImages();
	m_singelton = NULL;
}

FUI_ImagesFactory *FUI_ImagesFactory::GetInstance()
{
    FUI_ImagesFactory *result = NULL;

    if(m_singelton == NULL)
    {
        m_singelton = new FUI_ImagesFactory();
    }
    result = m_singelton;

    return result;
}

bool FUI_ImagesFactory::SaveImagesToFile(const char* path)
{
    CxIOFile file;
    bool ret = false;

    if( m_nImagesCount != m_NameIndex.size() )
    {
        m_nImagesCount = m_NameIndex.size();
    }

    if( 0 == m_nImagesCount )
        return ret;

    if( NULL == path )
        ret = file.Open(TEST_FILE, "wb+");
    else
        ret = file.Open(path, "wb+");

    if( ret )
        file.Write(&m_nImagesCount, sizeof(m_nImagesCount), 1);
    else
        return ret;

    NameIndex::iterator it_head = m_NameIndex.begin();
    unsigned int tempOffset = sizeof(m_nImagesCount) + sizeof(ImageInfo)*m_NameIndex.size();
    while( it_head != m_NameIndex.end() )
    {
        ImageData *pTemp =  m_Images.Dereference(it_head->second);
        pTemp->pImageHead->offset = tempOffset;
		if( pTemp->pImageHead->id == 0)
			pTemp->pImageHead->id = AssignID(it_head->second.GetHandle());			
        file.Write((const void*)(pTemp->pImageHead), sizeof(ImageInfo), 1);
        it_head++;
		tempOffset += pTemp->pImageHead->size;
    }

    NameIndex::iterator  it_datas = m_NameIndex.begin();
    while( it_datas != m_NameIndex.end() )
    {
        ImageData *pTemp = m_Images.Dereference(it_datas->second);
        file.Write(pTemp->pDatas, sizeof(char), pTemp->pImageHead->size);
        it_datas++;
    }


    ret = file.Close();
    return ret;
}

bool FUI_ImagesFactory::ReadImagePacket(const char* file)
{
    bool ret = false;
    size_t readSize = 0;
	if( m_nImagesCount )
	{
		CleanAllImages();
	}

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
    m_nBaseOffset = sizeof(nImageCount);

    for(unsigned int i=0; i<nImageCount; i++)
    {
        ImageData imageData;
        memset(&imageData, 0, sizeof(ImageData));
		ImageInfo imageInfo;
        imageData.pImageHead = &imageInfo;
        memset(imageData.pImageHead, 0, sizeof(ImageInfo));
        readSize = m_fPacketFile.Read(imageData.pImageHead, sizeof(ImageInfo), 1);
        imageData.flag = 1;
        m_nBaseOffset += sizeof(ImageInfo);
        bool ret = m_fPacketFile.Seek(imageData.pImageHead->offset, SEEK_SET);
        if( true == ret )
        {
            int size = imageData.pImageHead->size;
            imageData.pDatas = (const unsigned char*)malloc(size*sizeof(char));
            m_fPacketFile.Read((void*)imageData.pDatas, size, 1);

        }
        AddImage(&imageData);
		if( imageData.pDatas )
		{
			free((void*)imageData.pDatas);
			imageData.pDatas = NULL;
		}
		m_fPacketFile.Seek(m_nBaseOffset, SEEK_SET);
    }

	ret = m_fPacketFile.Close();
    return ret;
}








