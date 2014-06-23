#ifndef MYIMAGEITEM_H
#define MYIMAGEITEM_H

#include <QGraphicsObject>
#include <QGraphicsItem>

class MyImageItem : public QGraphicsObject
{
    Q_OBJECT
public:
    MyImageItem(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect()const;
    void LoadImageFromFile(const QString& imagePath);
signals:
    
public slots:



protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QImage* m_Image;
};

#endif // MYIMAGEITEM_H
