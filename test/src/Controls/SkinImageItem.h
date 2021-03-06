#ifndef SKINIMAGEITEM_H
#define SKINIMAGEITEM_H

#include "SkinBase.h"
#include "../UIEngine/imagemgr.h"

#include <QDebug>
class QImage;


namespace SkinCtrl
{
	class CSkinImageItem : public CSkinBase 
	{
		Q_OBJECT

	public:
		CSkinImageItem(unsigned int nID = 0, QGraphicsItem *parent = NULL);
		~CSkinImageItem();

		//void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		QRectF boundingRect()const;
		virtual void Draw(void *painter = NULL);
		virtual void ReadDatas(void){}
		virtual void WriteDatas(void){}

		void mouseMoveEvent(QGraphicsSceneMouseEvent *event){QGraphicsObject::mouseMoveEvent(event);}
		void mousePressEvent(QGraphicsSceneMouseEvent *event){qDebug()<<this->pos().x()<<this->pos().y();QGraphicsObject::mousePressEvent(event);}
		void mouseReleaseEvent(QGraphicsSceneMouseEvent *event){QGraphicsObject::mouseReleaseEvent(event);}

		void LoadImageFromFile(const QString& imagePath);
		void LoadImageFromHImage(HImage himg);
		//ImagdeData *GetImageData();
		HImage GetImageHandle(void){ return m_hImage;}

	private:
		QImage					*m_pImage;
		HImage					m_hImage;
	};
}


#endif // SKINIMAGEITEM_H
