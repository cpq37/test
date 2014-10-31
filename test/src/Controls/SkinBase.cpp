#include <QGraphicsSceneMouseEvent>

#include "SkinBase.h"

using namespace SkinCtrl;

/******************************************************************************
*
*   功能：  构造函数
*
******************************************************************************/
CSkinBase::CSkinBase(unsigned int nID, void *parent /* = NULL */)
	: QGraphicsObject((QGraphicsItem*)(parent))
	, CDrawUnit(parent,nID)
{

}


/******************************************************************************
*
*   功能：  析构函数
*
******************************************************************************/
CSkinBase::~CSkinBase()
{
}

/******************************************************************************
*
*   功能：  Paint
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
*   功能：
*
******************************************************************************/
QRectF CSkinBase::boundingRect(void) const
{
	return QRectF(m_sRect.x, m_sRect.y, m_sRect.width, m_sRect.height);
}

/******************************************************************************
*
*   功能：  鼠标压下事件
*
******************************************************************************/
void CSkinBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	OnMousePress(event->pos());
}

/******************************************************************************
*
*   功能：  鼠标释放事件
*
******************************************************************************/
void CSkinBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	OnMouseRelease(event->pos());
}

/******************************************************************************
*
*   功能：  鼠标移动事件
*
******************************************************************************/
void CSkinBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	OnMouseMove(event->pos());
}