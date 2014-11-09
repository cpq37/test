#ifndef SKINBASE_H
#define SKINBASE_H

#include <QGraphicsItem>
#include <QGraphicsObject>

#include "DrawUnit.h"


namespace SkinCtrl
{
	class CSkinGraphicsView;

	class CSkinBase : public QGraphicsObject, public CDrawUnit
	{
		Q_OBJECT
	public:
		CSkinBase(unsigned int nID, void *parent = NULL);
		virtual ~CSkinBase();
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		QRectF boundingRect()const;

	signals:

	public slots:	

	protected:
		// ����¼����̳����벻Ҫʹ�����µ��麯����
		void mousePressEvent(QGraphicsSceneMouseEvent *event);
		void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
		void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

		// �̳�����Ӧ����¼���ʹ�����µ��麯��
		virtual void OnMousePress(const QPointF &pos) {Q_UNUSED(pos);}
		virtual void OnMouseRelease(const QPointF &pos) {Q_UNUSED(pos);}
		virtual void OnMouseMove(const QPointF &pos) {Q_UNUSED(pos);}

		//using by paint,to draw,to update
		virtual void Draw(void *painter = NULL)=0;

		//draw image
		void DrawPixmap(void* painter, int x, int y, const QPixmap *ppix) const;
		//draw text
	protected:
		//QSizeF m_size;
	private:
	};
};

#endif // SKINBASE_H