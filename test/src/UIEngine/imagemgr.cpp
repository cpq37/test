
#include "imagemgr.h"

#ifdef _DEBUG 
#include "vld.h" 
#endif

int ImageMgr::AssignID(int id)
{
	//if( 0 == id )
	{
		while( m_NameIndex.find(id) != m_NameIndex.end() )
		{
			id++;
			if(0 == id)
				id++;
		}
	}

	return id;
}


HImage ImageMgr::AddImage(const ImageData* pBitmap)
{
    assert(pBitmap);

    ImageData *pImageData = NULL;
    HImage hImage = HImage();
    pImageData = m_Images.Acquire( hImage );

	// Assign ID
	if( 0 == pBitmap->pImageHead->id )
		pBitmap->pImageHead->id = AssignID(hImage.GetHandle());

    // insert
    NameIndexInsertRc rc =
        m_NameIndex.insert( std::make_pair( pBitmap->pImageHead->id, hImage ) );
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
        ImageData *pImageData = m_Images.Dereference(it->second);
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
        //delete pImageData;
        //pImageData = NULL;

        // delete from db
        m_Images.Release(it->second);
		// delete from index
		//m_NameIndex.erase(it);
        it++;
    }

    m_NameIndex.clear();
    m_fPacketFile.Close();
    m_nImagesCount = 0;
}


// HImage	ImageMgr::GetImage( const char* name )
// {
//     // find
//     NameIndex::iterator it = m_NameIndex.find( std::string(name) );
//     return ( it->second );
// }

HImage ImageMgr::GetImage(const unsigned int index)
{
	NameIndex::iterator it = m_NameIndex.begin();
	while (it != m_NameIndex.end())
	{
		if( index == it->second.GetIndex() )
			return it->second;

		it++;
	}
	HImage hImage;
	return hImage;
}

HImage ImageMgr::GetImageByID(const unsigned int bitmapID)
{
	NameIndex::iterator it = m_NameIndex.begin();
	while (it != m_NameIndex.end())
	{
		ImageData* pImageData = m_Images.Dereference( it->second );
		if( pImageData->pImageHead->id == bitmapID )
			return it->second;

		it++;
	}
	HImage hImage;
	return hImage;
}

const ImageData* ImageMgr::GetImageData(HImage himg)
{
	return m_Images.Dereference( himg );
}

void ImageMgr::DeleteImage( HImage himg )
{
	ImageData* pImageData = m_Images.Dereference( himg );

	if( pImageData )
	{
		// delete from index
		m_NameIndex.erase( m_NameIndex.find(pImageData->pImageHead->id) );


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
		// delete from db
		m_Images.Release( himg );
	}
}