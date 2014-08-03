#include "mainwindow.h"
#include "workscene.h"
#include "Common/setdebugnew.h"

#include <QtGui>

MainWindow::MainWindow()
{
    //createActions();
    createMenus();
    createStatusBar();

	testWidget = new QWidget;
	testTreeDialog = new Ui::Dialog();
	testTreeDialog->setupUi( (QDialog*)testWidget);

    scene = new WorkScene(this);
    scene->setSceneRect( QRectF(0, 0, 800, 480) );
    view = new QGraphicsView(scene);
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
	imageMen = menuBar()->addMenu( tr("Image") );

	openImgAction = new QAction( tr("Open Image"), this );
	connect( openImgAction, SIGNAL(triggered()), this, SLOT(openImage()) );
	imageMen->addAction( openImgAction );

	openTestDialog = new QAction( tr("Open Dialog"), this );
	connect( openTestDialog, SIGNAL(triggered()), this , SLOT(openDialog()) );
	imageMen->addAction( openTestDialog );

	saveAllImg = new QAction( tr("Save All Image"), this );
	connect( saveAllImg, SIGNAL(triggered()), this , SLOT(saveAllImage()) );
	imageMen->addAction( saveAllImg );
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
	 MyImageItem* imageItem = new MyImageItem();

     if (fileName.isNull())
         fileName = QFileDialog::getOpenFileName(this,\
         tr("Open Image"), "", "Image Files (*.png *.jpg *.bmp *.gif *.data)");

     if( !fileName.isEmpty())
     {
         imageItem->LoadImageFromFile(fileName);
         scene->addItem(imageItem);
         scene->update(scene->sceneRect());
		 m_ImageList.push_back(imageItem);
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

void MainWindow::mousePressEvent(QMouseEvent *)
{
	//scene->sendEvent()
	qDebug() << "MainWindow::mousePress";
}