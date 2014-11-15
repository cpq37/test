#include <QGraphicsRectItem>

#include "workscene.h"
#include "Common/setdebugnew.h"

WorkScene::WorkScene(QObject *parent)

     : QGraphicsScene(parent)
{
	QGraphicsRectItem *pRect = new QGraphicsRectItem(-1,-1,801,481, 0, this);
	QPen testPen;
	testPen.setColor(QColor(255,0,0));
	pRect->setPen(testPen);
	this->addItem(pRect);
}



WorkScene::~WorkScene()
{

}

