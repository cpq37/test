#include "SkinImageItem.h"
#include "../UIEngine/fui_imagesfactory.h"
#include "../Common/setdebugnew.h"

#include <QPainter>
#include <QImageReader>
#include <QDebug>

using namespace SkinCtrl;

CSkinImageItem::CSkinImageItem(unsigned int nID, void *parent )
	: CSkinBase(nID, parent)
	, m_pImage(NULL)
{
	setFlags(ItemIsMovable | ItemIsSelectable);
}

CSkinImageItem::~CSkinImageItem()
{
	if(m_pImage)
	{
		delete m_pImage;
		m_pImage = NULL;
	}
}

void CSkinImageItem::LoadImageFromHImage(HImage himg)
{
	m_hImage = himg;

	if(m_pImage)
	{
		delete m_pImage;
		m_pImage = NULL;
	}

	const ImageData * pTempData = FUI_ImagesFactory::GetInstance()->GetImageData(m_hImage);

	if(pTempData)
	{
		m_pImage = new QImage(pTempData->pImageHead->width,pTempData->pImageHead->height, QImage::Format_RGB32);

		unsigned int * p_bits = NULL;
		const unsigned char* datas = NULL;
		p_bits = (uint*)m_pImage->bits();
		datas = pTempData->pDatas;
		if( datas == NULL ) return;
		for(int i=0,j=0; i<pTempData->pImageHead->size; i+=4,j++)
		{
			p_bits[j] = qRgb(datas[i+2], datas[i+1], datas[i]);
		}
	}

	
}

void CSkinImageItem::LoadImageFromFile(const QString &imagePath)
{
	if(m_pImage)
	{
		delete m_pImage;
		m_pImage = NULL;
	}

	if( NULL == m_pImage )
	{
		//QImage test(imagePath);
 		m_pImage = new QImage(imagePath); //��Qt4.7.1�У����ܲ����κη�ʽ��ȡͼ���ļ����ᵼ���ڴ�й©����֪��ԭ��
	}

	// new temp
	ImageData *p_ImageData = new ImageData;//(ImageData*)malloc(sizeof(ImageData));
	if(p_ImageData)
		memset(p_ImageData, 0, sizeof(ImageData));

	if( NULL == p_ImageData->pImageHead )
	{
		p_ImageData->pImageHead = new ImageInfo;
		if(p_ImageData->pImageHead)
			memset(p_ImageData->pImageHead, 0, sizeof(ImageInfo));
	}

	if( m_pImage )
	{
		p_ImageData->pImageHead->size = m_pImage->byteCount();
		p_ImageData->pImageHead->width = m_pImage->width();
		p_ImageData->pImageHead->height = m_pImage->height();
		p_ImageData->pDatas = m_pImage->bits();
	}

	m_hImage = FUI_ImagesFactory::GetInstance()->AddImage(p_ImageData);

	//delet all
	if( p_ImageData )
	{
		if(p_ImageData->pImageHead)
			delete p_ImageData->pImageHead;
		//if(p_ImageData->pDatas)
		//	delete p_ImageData->pDatas;

		 p_ImageData;
	}
}

void CSkinImageItem::Draw(void *painter /* = NULL */)
{
	if( m_pImage != NULL && this->childItems().size() == 0)
	{
		((QPainter*)painter)->setRenderHint(QPainter::Antialiasing, true);
		QPixmap pixmapToShow = QPixmap::fromImage( m_pImage->scaled(m_pImage->size(), Qt::KeepAspectRatio) );  
		//((QPainter*)painter)->drawPixmap(0, 0, pixmapToShow);
		DrawPixmap(painter, 0, 0, &pixmapToShow);
	}
}

// void CSkinImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
// {
// 	Q_UNUSED(option);
// 	Q_UNUSED(widget);
// 	Draw(painter);
// }

QRectF CSkinImageItem::boundingRect()const
{
	if( m_pImage )
		return QRectF( m_pImage->rect() );
	else
		return QRectF();
}
