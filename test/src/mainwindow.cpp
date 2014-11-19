#include <QtGui>

#include "mainwindow.h"
#include "workscene.h"
#include "picmanager.h"

#include "Common/setdebugnew.h"
#include "Controls/SkinImageItem.h"
#include "Controls/SkinContainer.h"

#ifdef _DEBUG 
#include "vld.h" 
#endif



MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags f)
    : QMainWindow(parent, f)
	, m_pCurrentParent(NULL)
{
    //createActions();
    createMenus();
    createStatusBar();


    pPicManagerDock = new QDockWidget(tr("Picture Manager"), this);
    //pPicManagerDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
	pPicManagerDock->setAllowedAreas(Qt::LeftDockWidgetArea);
    pPicManagerWidget = new PicManager(this);
    //pPicManagerWidget->SetSize(200, 100);
    pPicManagerDock->setWidget(pPicManagerWidget);
    pPicManagerDock->setMinimumWidth(200);
	addDockWidget(Qt::LeftDockWidgetArea,pPicManagerDock);  
	connect(pPicManagerWidget, SIGNAL(signalAddPicture(const HImage&)), this, SLOT(slotAddPicToCurrentParent(const HImage&)));

    scene = new WorkScene(this);
    scene->setSceneRect( QRectF(-1, -1, 800+2, 480+2) );
    view = new MyGraphicsView(scene, this);
    setCentralWidget( view );
}

MainWindow::~MainWindow()
{
// 	while( m_ImageList.size() )
// 	{
// 		std::list<CSkinImageItem*>::iterator it = m_ImageList.begin();
// 		delete (*it);
// 		m_ImageList.pop_front();
// 	}
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

void MainWindow::openImage()
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
			/*static */string tempPath(fileName.toStdString());

			bool ret = FUI_ImagesFactory::GetInstance()->ReadImagePacket( tempPath.c_str() );
			if(ret)
			{
				qDebug() << "Read packet time:" << QTime::currentTime().msecsTo(startTime);
				int i = 0;
				int count = FUI_ImagesFactory::GetInstance()->GetImagesCount();
				for(i=0; i< count; i++)
				{
					CSkinImageItem* imageItem = new CSkinImageItem(i);
					imageItem->LoadImageFromHImage(FUI_ImagesFactory::GetInstance()->GetImage(i));
					scene->addItem((QGraphicsItem*)(imageItem));
					m_ImageList.push_back(imageItem);
				}
			}
			qDebug() << "all time:" << QTime::currentTime().msecsTo(startTime);
			scene->update(scene->sceneRect());
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
}

void MainWindow::mousePressEvent(QMouseEvent *)
{
	//scene->sendEvent()
    //qDebug() << "MainWindow::mousePress";
}

void MainWindow::saveAllImage()
{

}


void MainWindow::test()
{

}

void MainWindow::slotAddPicToCurrentParent(const HImage& hImage)
{
	if( m_pCurrentParent )
	{
		delete m_pCurrentParent;
		m_pCurrentParent = NULL;
	}

	m_pCurrentParent = new CSkinContainer;
	CSkinImageItem *pTempImgItem = new CSkinImageItem(0, m_pCurrentParent);
	pTempImgItem->LoadImageFromHImage(hImage);
	m_pCurrentParent->AddItem(pTempImgItem);

	scene->addItem(m_pCurrentParent);
}