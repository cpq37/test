#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <list>
#include <QMainWindow>

#include "myimageitem.h"
#include "ui_TestUI.h"

class WorkScene;
class QGraphicsScene;
class QGraphicsView;
class QLabel;
class MyImageItem;

class MainWindow : public QMainWindow
{
     Q_OBJECT

public:
     MainWindow();
     ~MainWindow();

	 virtual void mousePressEvent(QMouseEvent *);


public slots:
     void openImage(const QString& path = QString());
	 void openDialog(void);
	 void saveAllImage(void);
	 void test(void);

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

	 QWidget*			testWidget;

     QLabel*            formulaLabel;

     QGraphicsView*         view;
     QGraphicsScene*        scene;
     //WorkScene*             scene;
     //MyImageItem* imageItem;
	 Ui::Dialog*		testTreeDialog;
	
	 std::list<MyImageItem*>  m_ImageList;
};



#endif // MAINWINDOW_H

