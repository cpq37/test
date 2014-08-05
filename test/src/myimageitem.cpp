#include "myimageitem.h"
#include "Common/setdebugnew.h"


#include <QtGui>




MyImageItem::MyImageItem(QGraphicsItem *parent) 
	: QGraphicsObject(parent)
	, m_Image(NULL)
	, m_ImageData(NULL)
{
    setFlags(ItemIsMovable | ItemIsSelectable);
}

MyImageItem::~MyImageItem()
{
	if( m_ImageData )
	{
		if( m_ImageData->pImageHead )
		{
			delete m_ImageData->pImageHead;
			m_ImageData->pImageHead = NULL;
		}
		delete m_ImageData;
		m_ImageData = NULL;
	}
	if(m_Image)
	{
		delete m_Image;
		m_Image = NULL;
	}
}

void MyImageItem::LoadImageFromFile(const QString &imagePath)
{
    if(m_Image)
    {
        delete m_Image;
        m_Image = NULL;
    }

	QTime startTime = QTime::currentTime();
	DWORD Count = GetTickCount();
	if( imagePath.endsWith(tr(".data")) )
	{
		QFile file(imagePath);
		file.open(QIODevice::ReadOnly);
		int dataSize = file.size();
		unsigned char *dataBuffer = new unsigned char[dataSize];

 		file.read((char*)dataBuffer ,dataSize);
		m_Image = new QImage(800,600, QImage::Format_RGB32);

		unsigned int * p_bits;
		p_bits = (uint*)m_Image->bits();
		for(int i=0,j=0; i<dataSize; i+=4,j++)
		{
			p_bits[j] = qRgb(dataBuffer[i+2], dataBuffer[i+1], dataBuffer[i]);
		}

		//Ìî³ä£¬x¡¢y¾ÓÈ»µ¹ÖÃ
// 		QRgb rgb;
// 		for(int i=0; i<600; i++)
// 		{
// 			for(int j=0; j<800; j++)
// 			{
// 				int r = dataBuffer[i*800*4+j*4+2];
// 				int g = dataBuffer[i*800*4+j*4+1];
// 				int b = dataBuffer[i*800*4+j*4];
// 				rgb = qRgb(r, g, b);
// 				m_Image->setPixel(j,i, rgb);
// 			}
// 		}
		qDebug() << dataSize;
		delete dataBuffer;
		file.close();
	}
	else
	{
		m_Image = new QImage(imagePath);
	}
	QTime endTime = QTime::currentTime();
	qDebug() << "load+decode" << startTime.msecsTo(endTime);
	qDebug() << "load+decode" << GetTickCount()-Count;

}

bool MyImageItem::LoadImageFromDatas(const unsigned char *datas)
{
	bool ret = false;
	if( datas )
	{
		if(m_Image)
		{
			delete m_Image;
			m_Image = NULL;
		}
		
		if(m_ImageData)
		{
			m_Image = new QImage(m_ImageData->pImageHead->width,m_ImageData->pImageHead->height, QImage::Format_RGB32);

			unsigned int * p_bits;
			p_bits = (uint*)m_Image->bits();
			for(int i=0,j=0; i<m_ImageData->pImageHead->size; i+=4,j++)
			{
				p_bits[j] = qRgb(datas[i+2], datas[i+1], datas[i]);
			}
		}
	}

	return ret;
}

void MyImageItem::SaveImage(const QString& filenamePath)
{
	if(m_Image)
	{
		QFile file(filenamePath);
		file.open(QIODevice::ReadWrite | QIODevice::Append);

		QDataStream fileStream(&file);
		//m_Image->convertToFormat(QImage::Format_ARGB32);
		qDebug() << m_Image->format() << m_Image->width() << m_Image->height() << m_Image->bytesPerLine();
		//fileStream.setByteOrder(QDataStream::LittleEndian);
		int bufferSize = m_Image->byteCount();
		unsigned char *datas = m_Image->bits();

		fileStream.writeRawData((const char*)datas, bufferSize);
		//file.write((const char*)m_Image->constBits(), m_Image->byteCount());
		//bool ret = m_Image->save(&file, "jpg");
		//qDebug() << ret;
		file.close();
// 		QImage testImage((uchar*)tempBuffer, m_Image->width(), m_Image->height(), m_Image->bytesPerLine(), QImage::Format_RGB32);
// 		QGraphicsPixmapItem* testItem = new QGraphicsPixmapItem(QPixmap::fromImage(testImage), this);
	}
}

void MyImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);
	if( m_Image != NULL && this->childItems().size() == 0)
	{
		painter->setRenderHint(QPainter::Antialiasing, true);
		QTime startTime = QTime::currentTime();
		QPixmap pixmapToShow = QPixmap::fromImage( m_Image->scaled(m_Image->size(), Qt::KeepAspectRatio) );  
		//painter->drawImage( 0, 0, *m_Image);
		//painter->drawPixmap(0, 0, QPixmap::fromImage(*m_Image));
		QTime endTime = QTime::currentTime();
		painter->drawPixmap(0, 0, pixmapToShow);
		qDebug() << "paint" << startTime.msecsTo(endTime);
	}
}

QRectF MyImageItem::boundingRect()const
{
    if( m_Image )
        return QRectF( m_Image->rect() );
    else
        return QRectF();
}

void MyImageItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
    setCursor(Qt::ClosedHandCursor);
	//qDebug() << event->pos().x() << "," << event->pos().y(); 
}

void MyImageItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
}

void MyImageItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseReleaseEvent(event);
    setCursor(Qt::OpenHandCursor);
	qDebug() << pos().x() << "," << pos().y();
}


ImagdeData* MyImageItem::GetImageData()
{
	if( NULL == m_ImageData )
	{
		m_ImageData = new ImagdeData;
		memset(m_ImageData, 0, sizeof(ImagdeData));

		if( NULL == m_ImageData->pImageHead )
		{
			m_ImageData->pImageHead = new ImageInfo;
			memset(m_ImageData->pImageHead, 0, sizeof(ImageInfo));
		}
	}

	if( m_Image )
	{
		m_ImageData->pImageHead->size = m_Image->byteCount();
		m_ImageData->pImageHead->width = m_Image->width();
		m_ImageData->pImageHead->height = m_Image->height();
		m_ImageData->pDatas = m_Image->bits();
	}
	return m_ImageData;
}