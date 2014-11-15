#include <QGraphicsRectItem>

#include "workscene.h"
#include "Common/setdebugnew.h"

WorkScene::WorkScene(QObject *parent)

     : QGraphicsScene(parent)
{
	m_pRect = new QGraphicsRectItem(-1,-1,801,481, 0, this);
	QPen testPen;
	testPen.setColor(QColor(255,0,0));
	m_pRect->setPen(testPen);
	this->addItem(m_pRect);
}



WorkScene::~WorkScene()
{
	if(m_pRect)
	{
		delete m_pRect;
		m_pRect = NULL;
	}
}

