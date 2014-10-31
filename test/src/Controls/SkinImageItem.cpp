#include "SkinImageItem.h"
#include "../UIEngine/fui_imagesfactory.h"


#include <QPainter>

using namespace SkinCtrl;

CSkinImageItem::CSkinImageItem(unsigned int nID, void *parent )
	: CSkinBase(nID, parent)
	, m_pImage(NULL)
{

}

CSkinImageItem::~CSkinImageItem()
{

}

void CSkinImageItem::LoadImageFromFile(const QString &imagePath)
{
	if(m_pImage)
	{
		delete m_pImage;
		m_pImage = NULL;
	}

	m_pImage = new QImage(imagePath);

	// new temp
	ImageData *m_ImageData = new ImageData;
	memset(m_ImageData, 0, sizeof(ImageData));

	if( NULL == m_ImageData->pImageHead )
	{
		m_ImageData->pImageHead = new ImageInfo;
		memset(m_ImageData->pImageHead, 0, sizeof(ImageInfo));
	}

	if( m_pImage )
	{
		m_ImageData->pImageHead->size = m_pImage->byteCount();
		m_ImageData->pImageHead->width = m_pImage->width();
		m_ImageData->pImageHead->height = m_pImage->height();
		m_ImageData->pDatas = m_pImage->bits();
	}

	m_hImage = FUI_ImagesFactory::GetInstance()->AddImage(m_ImageData);

	//delet all
	if( m_ImageData )
	{
		if(m_ImageData->pImageHead)
			delete m_ImageData->pImageHead;
		if(m_ImageData->pDatas)
			delete m_ImageData->pDatas;

		delete m_ImageData;
	}
}

void CSkinImageItem::Draw(void *painter /* = NULL */)
{

}

void CSkinImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);
	if( m_pImage != NULL && this->childItems().size() == 0)
	{
		painter->setRenderHint(QPainter::Antialiasing, true);
		QPixmap pixmapToShow = QPixmap::fromImage( m_pImage->scaled(m_pImage->size(), Qt::KeepAspectRatio) );  
		painter->drawPixmap(0, 0, pixmapToShow);
	}
}

QRectF CSkinImageItem::boundingRect()const
{
	if( m_pImage )
		return QRectF( m_pImage->rect() );
	else
		return QRectF();
}
