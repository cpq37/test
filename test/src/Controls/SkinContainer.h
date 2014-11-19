#ifndef SKINCONTAINER_H
#define SKINCONTAINER_H



#include "SkinBase.h"

namespace SkinCtrl
{
	class CSkinContainer : public CSkinBase 
	{
		Q_OBJECT

	public:
		CSkinContainer(unsigned int nID = 0, QGraphicsItem *parent = NULL);
		~CSkinContainer();

		//void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		//QRectF boundingRect()const;
		virtual void Draw(void *painter = NULL);
		virtual void ReadDatas(void){}
		virtual void WriteDatas(void){}
	};
}

#endif //SKINCONTAINER_H