#ifndef MYIMAGEITEM_H
#define MYIMAGEITEM_H

#include <QGraphicsObject>
#include <QGraphicsItem>
#include <windows.h>

#include "UIEngine/ImageResourceManager.h"

class MyImageItem : public QGraphicsObject
{
    Q_OBJECT
public:
    MyImageItem(QGraphicsItem *parent = NULL);
	~MyImageItem();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect()const;

    void LoadImageFromFile(const QString& imagePath);
	bool LoadImageFromDatas(const unsigned char *datas);
	void SaveImage(const QString& filenamePath);
	ImagdeData *GetImageData();
signals:
    
public slots:



protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QImage					*m_Image;
	ImagdeData				*m_ImageData; 
};

#endif // MYIMAGEITEM_H
