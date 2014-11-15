#include <QtGui>

#include "mainwindow.h"
#include "workscene.h"
#include "picmanager.h"

//#include "UIEngine/ImageResourceManager.h"
#include "UIEngine/fui_imagesfactory.h"
//#include "Common/setdebugnew.h"


MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags f)
    : QMainWindow(parent, f)
{
    //createActions();
    createMenus();
    createStatusBar();

	// !test code
	testWidget = new MyWidget();
	testTreeDialog = new Ui::Dialog();
	testTreeDialog->setupUi( (QDialog*)testWidget);
	// test code !

    pPicManagerDock = new QDockWidget(tr("Picture Manager"), this);
    //pPicManagerDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
	pPicManagerDock->setAllowedAreas(Qt::LeftDockWidgetArea);
    pPicManagerWidget = new PicManager(this);
    //pPicManagerWidget->SetSize(200, 100);
    pPicManagerDock->setWidget(pPicManagerWidget);
    pPicManagerDock->setMinimumWidth(200);
	addDockWidget(Qt::LeftDockWidgetArea,pPicManagerDock);  

    scene = new WorkScene(this);
    scene->setSceneRect( QRectF(-1, -1, 800+2, 480+2) );
    view = new MyGraphicsView(scene, this);
    //view->resize(800+4, 480+4);
    setCentralWidget( view );
}



MainWindow::~MainWindow()
{
	while( m_ImageList.size() )
	{
		std::list<CSkinImageItem*>::iterator it = m_ImageList.begin();
		delete (*it);
		m_ImageList.pop_front();
	}

	if( testTreeDialog )
	{
		delete testTreeDialog;
		testTreeDialog = NULL;
	}
	if( testWidget )
	{
		delete testWidget;
		testWidget = NULL;
	}
}


void MainWindow::createActions()
{

}



void MainWindow::createMenus(void)
{
	fileMenu = menuBar()->addMenu( tr("&File") );
	
	exitAction = new QAction( tr("E&xit"), this );
	exitAction->setShortcuts( QKeySequence::Quit );
	exitAction->setStatusTip( tr("Quit Programe") );
	connect( exitAction, SIGNAL(triggered()), this, SLOT(close()) );
	fileMenu->addAction( exitAction );

	openAciton = new QAction( tr("&Open..."), this );
	openAciton->setShortcut( QKeySequence::Open );
	connect( openAciton, SIGNAL(triggered()), this, SLOT(openImage()) );
	fileMenu->addAction( openAciton );


	////////////////////////////////////////////////////////////////////////////
	imageMenu = menuBar()->addMenu( tr("Image") );

	openImgAction = new QAction( tr("Open Image"), this );
	connect( openImgAction, SIGNAL(triggered()), this, SLOT(openImage()) );
	imageMenu->addAction( openImgAction );

	openTestDialog = new QAction( tr("Open Dialog"), this );
	connect( openTestDialog, SIGNAL(triggered()), this , SLOT(openDialog()) );
	imageMenu->addAction( openTestDialog );

	saveAllImg = new QAction( tr("Save All Image"), this );
	connect( saveAllImg, SIGNAL(triggered()), this , SLOT(saveAllImage()) );
	imageMenu->addAction( saveAllImg );

	testAction = new QAction( tr("Test"), this );
	imageMenu->addAction(testAction);
	connect( testAction, SIGNAL(triggered()), this , SLOT(test()) );
}

void MainWindow::createStatusBar()
{
    /*
    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);
    statusBar()->addWidget( formulaLabel );
    */
    statusBar();
}

void MainWindow::openImage(const QString& path)
{
	
	QString fileName;
	
	
	if (fileName.isNull())
		fileName = QFileDialog::getOpenFileName(this,\
		tr("Open Image"), "", "Image Files (*.png *.jpg *.bmp *.gif *.data *.pack)");
	QTime startTime = QTime::currentTime();
	if( !fileName.isEmpty())
	{
		if( fileName.endsWith(tr(".pack")) )
		{
			static string tempPath(fileName.toStdString());

			bool ret = FUI_ImagesFactory::GetInstance()->ReadImagePacket( tempPath.c_str() );
			if(ret)
			{
				qDebug() << "Read packet time:" << QTime::currentTime().secsTo(startTime);
				int i = 0;
				int count = FUI_ImagesFactory::GetInstance()->GetImagesCount();
				for(i=0; i< count; i++)
				{
					CSkinImageItem* imageItem = new CSkinImageItem(i);
					imageItem->LoadImageFromHImage(FUI_ImagesFactory::GetInstance()->GetImage(i));
					scene->addItem((QGraphicsItem*)(imageItem));
					scene->update(scene->sceneRect());
					m_ImageList.push_back(imageItem);
				}
			}
			qDebug() << "all time:" << QTime::currentTime().secsTo(startTime);
		}
		else
		{
			CSkinImageItem* imageItem = new CSkinImageItem();
			imageItem->LoadImageFromFile(fileName);
			scene->addItem(imageItem);
			scene->update(scene->sceneRect());
			m_ImageList.push_back(imageItem);
		}

	}
	
}

void MainWindow::openDialog()
{
    QString dirName;


    if (dirName.isNull())
        dirName = QFileDialog::getExistingDirectory(this,\
        tr("Open Image Directory"), "" );
    if( !dirName.isEmpty())
    {
        qDebug()<<dirName;
    }

	testTreeDialog->treeWidget->setColumnCount(2);
	QStringList treeLabers(tr("Name"));
	treeLabers += tr("Size");
	testTreeDialog->treeWidget->setHeaderLabels(treeLabers);
	QList<QTreeWidgetItem *> items;
	for (int i = 0; i < 10; ++i)
		items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));

	//testTreeDialog->treeWidget->insertTopLevelItems(1, items);
	QTreeWidgetItem* testTreeItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("test")));
	testTreeItem->addChildren(items);
	testTreeDialog->treeWidget->insertTopLevelItem(0, testTreeItem);
	testTreeDialog->treeWidget->expandAll();
	testWidget->show();
}

void MainWindow::mousePressEvent(QMouseEvent *)
{
	//scene->sendEvent()
    //qDebug() << "MainWindow::mousePress";
}

void MainWindow::saveAllImage()
{
// 	std::list<MyImageItem *>::iterator it = m_ImageList.begin();
// 	while( it != m_ImageList.end() )
// 	{
// 		MyImageItem *tempImageItem = *it;
// 		tempImageItem->SaveImage("test.data");
// 		it++;
// 	}
}


void MainWindow::test()
{
// 	std::list<MyImageItem *>::iterator it = m_ImageList.begin();
// 	UIEngine::CImageDatasManager::GetInstance()->CleanAllImages();
// 	while( it != m_ImageList.end() )
// 	{
// 		MyImageItem *tempImageItem = *it;
// 		UIEngine::CImageDatasManager::GetInstance()->AddImage(tempImageItem->GetImageData());
// 		it++;
// 	}
// 
// 	UIEngine::CImageDatasManager::GetInstance()->SaveAllImages();
}

