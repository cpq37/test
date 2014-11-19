#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <list>
#include <QMainWindow>
#include <QGraphicsView.h>
#include <QWheelEvent>
#include <cmath>
#include <QDebug>

//#include "Controls/SkinImageItem.h"
#include "UIEngine/fui_imagesfactory.h"


class WorkScene;
class QGraphicsScene;
class QGraphicsView;
class QLabel;
class PicManager;
class QDockWidget;

namespace SkinCtrl
{
class CSkinImageItem;
class CSkinBase;
class CSkinContainer;
}

using namespace SkinCtrl;

class MyWidget : public QWidget
{
public:  
	QSize sizeHint() const  
	{  
		return QSize(m_nWidth, m_nWidth); /* 在这里定义dock的初始大小 */  
	}  

	void SetSize(int w, int h)
	{
		m_nWidth = w;
		m_nHeight = h;
	}
private:
	int m_nWidth;
	int m_nHeight;
};

class MyGraphicsView : public QGraphicsView
{
public:
	MyGraphicsView(QWidget *parent = 0) : QGraphicsView(parent)
	{
		Init();
	}
	MyGraphicsView(QGraphicsScene *scene, QWidget *parent = 0) : QGraphicsView(scene,parent)
	{
		Init();
	}
	virtual ~MyGraphicsView(void){}


	void Init(void)
	{
		m_bScale = false;
	}

protected:
	bool m_bScale;
	void keyPressEvent ( QKeyEvent * event )
	{
		if( event->key() == Qt::Key_Control )
		{
			m_bScale = true;
		}
	}
	void keyReleaseEvent ( QKeyEvent * event )
	{
		if( event->key() == Qt::Key_Control )
		{
			m_bScale = false;
		}
	}
	void wheelEvent(QWheelEvent *event)
	{
		if( m_bScale )
		{
			double numDegrees = -event->delta() / 8.0;
			double numSteps = numDegrees / 15.0;
			double factor = std::pow(1.025, numSteps);
			scale(factor, factor);
			//qDebug() << transform().m11() << transform().m22();
		}

	}
	void paintEvent(QPaintEvent *event)
	{
		QPixmap pm(40, 40);
		QPainter pmp(&pm);
		pmp.fillRect(0, 0, 20, 20, Qt::white);
		pmp.fillRect(20, 20, 20, 20, Qt::white);
		pmp.fillRect(0, 20, 20, 20, Qt::lightGray);
		pmp.fillRect(20, 0, 20, 20, Qt::lightGray);
		pmp.end();
		QPalette pal = palette();
		pal.setBrush(backgroundRole(), QBrush(pm));
		setAutoFillBackground(true);
		setPalette(pal);
		QGraphicsView::paintEvent(event);
	}
};

class MainWindow : public QMainWindow
{
     Q_OBJECT

public:
     MainWindow(QWidget* parent=0, Qt::WindowFlags f=0);
     ~MainWindow();

	 virtual void mousePressEvent(QMouseEvent *);


private slots:
     void openImage();
	 void openDialog(void);
	 void saveAllImage(void);
	 void test(void);
	 void slotAddPicToCurrentParent(const HImage& hImage);

private:
     void createActions(void);
     void createMenus(void);
     void createStatusBar(void);


private:
     ////////////////////////////////////////////////////////////////////
     QMenu*             fileMenu;              //文件菜单
     QAction*           exitAction;            //退出菜单选项
     QAction*           openAciton;
     ////////////////////////////////////////////////////////////////////
     QMenu*             imageMenu;
     QAction*           openImgAction;
	 QAction*			openTestDialog;
	 QAction*			saveAllImg;
	 QAction*			testAction;

     PicManager*        pPicManagerWidget;
     QDockWidget*       pPicManagerDock;

     QLabel*            formulaLabel;

     QGraphicsView*         view;
     QGraphicsScene*        scene;
	
	 std::list<CSkinBase*>  m_ImageList;
	 CSkinBase *m_pCurrentParent;
};



#endif // MAINWINDOW_H

