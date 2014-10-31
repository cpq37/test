#ifndef SKINIMAGEITEM_H
#define SKINIMAGEITEM_H

#include "SkinBase.h"
#include "../UIEngine/imagemgr.h"

class QImage;


namespace SkinCtrl
{
	class CSkinImageItem : public CSkinBase 
	{
		Q_OBJECT

	public:
		CSkinImageItem(unsigned int nID = 0, void *parent = NULL);
		~CSkinImageItem();

		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		QRectF boundingRect()const;
		virtual void Draw(void *painter = NULL);

		void LoadImageFromFile(const QString& imagePath);
		//ImagdeData *GetImageData();

	private:
		QImage					*m_pImage;
		HImage					m_hImage;
	};
};


#endif // SKINIMAGEITEM_H
