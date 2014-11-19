#include "SkinContainer.h"

using namespace SkinCtrl;

CSkinContainer::CSkinContainer(unsigned int nID, QGraphicsItem *parent )
	: CSkinBase(nID, parent)
{
	setFlags(ItemIsMovable | ItemIsSelectable);
}

CSkinContainer::~CSkinContainer()
{

}   

// QRectF CSkinContainer::boundingRect() const
// {
// 	return CSkinBase::boundingRect();
// }

void CSkinContainer::Draw(void *painter)
{

}
