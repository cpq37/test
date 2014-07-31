#include "myimageitem.h"
#include "setdebugnew.h"

#include <QtGui>
#include <windows.h>

MyImageItem::MyImageItem(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    m_Image = NULL;
    setFlags(ItemIsMovable | ItemIsSelectable);
}

void MyImageItem::LoadImageFromFile(const QString &imagePath)
{
    if(m_Image)
    {
        delete m_Image;
        m_Image = NULL;
    }
	DWORD count = GetTickCount();
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
		for(int i=0; i<dataSize; i+=4)
		{
			p_bits[i/4] = qRgb(dataBuffer[i+2], dataBuffer[i+1], dataBuffer[i]);
		}

		//Ìî³ä£¬x¡¢y¾ÓÈ»µ¹ÖÃ
// 		QRgb rgb;
// 		for(int i=0; i<40; i++)
// 		{
// 			for(int j=0; j<40; j++)
// 			{
// 				int r = dataBuffer[i*40*4+j*4+2];
// 				int g = dataBuffer[i*40*4+j*4+1];
// 				int b = dataBuffer[i*40*4+j*4];
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
	qDebug() << GetTickCount()-count;
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
		//QPixmap pixmapToShow = QPixmap::fromImage( m_Image->scaled(m_Image->size(), Qt::KeepAspectRatio) );  
		painter->setRenderHint(QPainter::Antialiasing, true);
		//painter->drawImage( 0, 0, *m_Image);
		painter->drawPixmap(0, 0, QPixmap::fromImage(*m_Image));
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


