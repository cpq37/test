#ifndef WORKSCENE_H
#define WORKSCENE_H

#include <QGraphicsScene>

class WorkScene : public QGraphicsScene
{
     Q_OBJECT

public:
     WorkScene(QObject *parent = 0);
     ~WorkScene();


protected:

private:
	QGraphicsRectItem *m_pRect;
};


#endif // WORKSCENE_H

