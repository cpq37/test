#include "workscene.h"
#include "Common/setdebugnew.h"

#include <QGraphicsRectItem>

WorkScene::WorkScene(QObject *parent)

     : QGraphicsScene(parent)
{
	QGraphicsRectItem *pRect = new QGraphicsRectItem(-1,-1,802,482);
	QPen testPen;
	testPen.setColor(QColor(255,0,0));
	pRect->setPen(testPen);
	this->addItem(pRect);
}



WorkScene::~WorkScene()
{

}

