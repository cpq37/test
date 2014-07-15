#include "workscene.h"

#include <QGraphicsRectItem>

WorkScene::WorkScene(QObject *parent)

     : QGraphicsScene(parent)
{
	QGraphicsRectItem *pRect = new QGraphicsRectItem(0,0,800,480);
	QPen testPen;
	testPen.setColor(QColor(255,0,0));
	pRect->setPen(testPen);
	this->addItem(pRect);
}



WorkScene::~WorkScene()
{

}

