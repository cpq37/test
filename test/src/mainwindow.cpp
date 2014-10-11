#include <QtGui>

#include "mainwindow.h"
#include "workscene.h"

#include "UIEngine/ImageResourceManager.h"
#include "Common/setdebugnew.h"


MainWindow::MainWindow()
{
    //createActions();
    createMenus();
    createStatusBar();

	testWidget = new MyWidget;
	testTreeDialog = new Ui::Dialog();
	testTreeDialog->setupUi( (QDialog*)testWidget);

	QDockWidget* pPicManagerDock = new QDockWidget(tr("Picture Manager"), this);
	pPicManagerDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
	pPicManagerDock->setAllowedAreas(Qt::LeftDockWidgetArea);
	testWidget->SetSize(200, 100);
	pPicManagerDock->setWidget(testWidget);
	//pPicManagerDock->setMinimumWidth(200);
	addDockWidget(Qt::LeftDockWidgetArea,pPicManagerDock);  

    scene = new WorkScene(this);
    scene->setSceneRect( QRectF(0, 0, 800, 480) );
    view = new MyGraphicsView(scene);
    //view->resize(800, 480);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget( view );
    QWidget* widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget( widget );
}



MainWindow::~MainWindow()
{
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
     QString fileName = path;
	
	
     if (fileName.isNull())
         fileName = QFileDialog::getOpenFileName(this,\
         tr("Open Image"), "", "Image Files (*.png *.jpg *.bmp *.gif *.data *.pack)");
	QTime startTime = QTime::currentTime();
     if( !fileName.isEmpty())
     {
		 if( fileName.endsWith(tr(".pack")) )
		 {
			 if(UIEngine::CImageDatasManager::GetInstance()->ReadImagePacket( fileName.toStdString().data() ) )
			 {
				 qDebug() << "Read packet time:" << QTime::currentTime().secsTo(startTime);
				 int i = 0;
				 int count = UIEngine::CImageDatasManager::GetInstance()->GetImagesCount();
				 for(i=0; i< count; i++)
				 {
					MyImageItem* imageItem = new MyImageItem();
					const unsigned  char *tempBuffer = UIEngine::CImageDatasManager::GetInstance()->\
						GetImageDatasByIndex(i, imageItem->GetImageData());
					qDebug() << "Read one picture:" << QTime::currentTime().secsTo(startTime);
					imageItem->LoadImageFromDatas(tempBuffer);
					scene->addItem(imageItem);
					scene->update(scene->sceneRect());
					m_ImageList.push_back(imageItem);
				 }
			 }
			 qDebug() << "all time:" << QTime::currentTime().secsTo(startTime);
		 }
		 else
		 {
			 MyImageItem* imageItem = new MyImageItem();
			 imageItem->LoadImageFromFile(fileName);
			 scene->addItem(imageItem);
			 scene->update(scene->sceneRect());
			 m_ImageList.push_back(imageItem);
		 }

     }
	
}

void MainWindow::openDialog()
{

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
	qDebug() << "MainWindow::mousePress";
}

void MainWindow::saveAllImage()
{
	std::list<MyImageItem *>::iterator it = m_ImageList.begin();
	while( it != m_ImageList.end() )
	{
		MyImageItem *tempImageItem = *it;
		tempImageItem->SaveImage("test.data");
		it++;
	}
}


void MainWindow::test()
{
	std::list<MyImageItem *>::iterator it = m_ImageList.begin();
	UIEngine::CImageDatasManager::GetInstance()->CleanAllImages();
	while( it != m_ImageList.end() )
	{
		MyImageItem *tempImageItem = *it;
		UIEngine::CImageDatasManager::GetInstance()->AddImage(tempImageItem->GetImageData());
		it++;
	}

	UIEngine::CImageDatasManager::GetInstance()->SaveAllImages();
}

