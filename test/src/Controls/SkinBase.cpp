#include <QGraphicsSceneMouseEvent>

#include "SkinBase.h"

using namespace SkinCtrl;

/******************************************************************************
*
*   ���ܣ�  ���캯��
*
******************************************************************************/
CSkinBase::CSkinBase(unsigned int nID, void *parent /* = NULL */)
	: QGraphicsObject((QGraphicsItem*)(parent))
	, CDrawUnit(parent,nID)
{

}


/******************************************************************************
*
*   ���ܣ�  ��������
*
******************************************************************************/
CSkinBase::~CSkinBase()
{
}

/******************************************************************************
*
*   ���ܣ�  Paint
*
******************************************************************************/
void CSkinBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);
	Draw(painter);
}

/******************************************************************************
*
*   ���ܣ�
*
******************************************************************************/
QRectF CSkinBase::boundingRect(void) const
{
	return QRectF(m_sRect.x, m_sRect.y, m_sRect.width, m_sRect.height);
}

/******************************************************************************
*
*   ���ܣ�  ���ѹ���¼�
*
******************************************************************************/
void CSkinBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	OnMousePress(event->pos());
}

/******************************************************************************
*
*   ���ܣ�  ����ͷ��¼�
*
******************************************************************************/
void CSkinBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	OnMouseRelease(event->pos());
}

/******************************************************************************
*
*   ���ܣ�  ����ƶ��¼�
*
******************************************************************************/
void CSkinBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	OnMouseMove(event->pos());
}