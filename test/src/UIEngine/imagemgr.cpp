
#include "imagemgr.h"

HImage ImageMgr::AddImage(const ImageData* pBitmap)
{
    assert(pBitmap);

    ImageData *pImageData = NULL;
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
        memcpy(pImageData, pBitmap, sizeof(ImageData));
		if( pBitmap->pImageHead )
		{
			pImageData->pImageHead = (ImageInfo *)malloc(sizeof(ImageInfo));
			if( pImageData->pImageHead )
				memcpy((void*)pImageData->pImageHead, (void*)pBitmap->pImageHead, sizeof(ImageInfo));
		}
		if( pBitmap->pDatas )
		{
			pImageData->pDatas = (const unsigned char*)malloc((pBitmap->pImageHead->size)*sizeof(unsigned char));
			if( pImageData->pDatas )
				memcpy((void*)pImageData->pDatas, (void*)pBitmap->pDatas, pBitmap->pImageHead->size);
		}
        m_nImagesCount++;

    }
    return ( rc.first->second );
}

void ImageMgr::CleanAllImages()
{
    NameIndex::iterator it = m_NameIndex.begin();
    while (it != m_NameIndex.end())
    {
        ImageData *pImageData = m_Images.Acquire(it->second);
        if( pImageData )
        {
            if( pImageData->pImageHead )
            {
                free((void*)pImageData->pImageHead);
                pImageData->pImageHead = NULL;
            }
            if( pImageData->pDatas )
            {
                free((void*)pImageData->pDatas);
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

HImage ImageMgr::GetImage(const unsigned int bitmapID)
{
	NameIndex::iterator it = m_NameIndex.begin();
	while (it != m_NameIndex.end())
	{
		if( bitmapID == it->second.GetIndex() )
			return it->second;

		it++;
	}
}

const ImageData* ImageMgr::GetImageData(HImage himg)
{
	return m_Images.Dereference( himg );
}