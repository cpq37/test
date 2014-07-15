#include "myimageitem.h"

#include <QtGui>

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

    m_Image = new QImage(imagePath);
}

void MyImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawImage( 0, 0, *m_Image);
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

}

void MyImageItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
}

void MyImageItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseReleaseEvent(event);
    setCursor(Qt::OpenHandCursor);
}


