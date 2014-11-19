#include "picmanager.h"


#include "Controls/SkinImageItem.h"
#include "Common/setdebugnew.h"

#include <QFileDialog>
#include <QImageReader>
#include <QDebug>

#include <QGraphicsScene>
#include <QMenu>
#include <QContextMenuEvent>

#ifdef _DEBUG 
#include "vld.h" 
#endif

using namespace SkinCtrl;

PicManager::PicManager(QWidget *parent)
    : QWidget(parent)
    //, ui(new Ui::PicManager)
    , m_pScene(NULL)
{
//     ui->setupUi(this);
	setupUi(this);
	//graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

	createTreeWidget();
	createActions();

    connect( treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(on_showItem(QTreeWidgetItem*,int)) );
}

PicManager::~PicManager()
{
	if( m_pScene )
		delete m_pScene;

    //delete ui;
	//delete FUI_ImagesFactory::GetInstance();
    //FUI_ImagesFactory::GetInstance()->SaveImagesToFile();
}

void PicManager::createTreeWidget()
{
	treeWidget->setColumnCount(5);
	QStringList treeLabels(tr("Index"));	//0
	treeLabels += tr("Name");				//1
	treeLabels += tr("Bitmap ID");			//2
	treeLabels += tr("Size");				//3
	treeLabels += tr("Path");				//4
	treeWidget->setHeaderLabels(treeLabels);
	treeWidget->setColumnHidden(4, true);
	treeWidget->setColumnHidden(1, true);
}

void PicManager::createActions()
{
	deleteAction = new QAction(tr("Delete"), this);
	testAction   = new QAction(tr("Add To..."), this);
	connect(deleteAction, SIGNAL(triggered()), this, SLOT(on_deletItem()) );
	connect(testAction, SIGNAL(triggered()), this, SLOT(on_test()) );
}

void PicManager::on_addPicButton_clicked()
{
    addImages(0);
}

void PicManager::on_deletItem()
{
	QTreeWidgetItem *deleteItem = treeWidget->currentItem();
	unsigned int id = deleteItem->text(0).toInt();
	HImage hImage = FUI_ImagesFactory::GetInstance()->GetImage(id);
	FUI_ImagesFactory::GetInstance()->DeleteImage(hImage);
	delete deleteItem;
}

void PicManager::on_test()
{
	QTreeWidgetItem *deleteItem = treeWidget->currentItem();
	unsigned int id = deleteItem->text(0).toInt();
	HImage hImage = FUI_ImagesFactory::GetInstance()->GetImage(id);
	emit signalAddPicture(hImage);
}

void PicManager::on_showItem(QTreeWidgetItem * item, int column)
{
    if( m_pScene )
        delete m_pScene;
    m_pScene = new QGraphicsScene(this);

	HImage hImage = FUI_ImagesFactory::GetInstance()->GetImage(item->text(0).toInt());
	CSkinImageItem *pImageItem = new CSkinImageItem;
	pImageItem->LoadImageFromHImage(hImage);

	m_pScene->addItem(pImageItem);
    graphicsView->setScene(m_pScene);

//     qreal sx = 1.0;
//     qreal sy = 1.0;
//     static qreal max_scale = qMin(sx,sy);
//     graphicsView->scale(1.0/max_scale,1.0/max_scale);
//     //scale
//     sx = static_cast<qreal>(graphicsView->width())/static_cast<qreal>(pic.width())*0.9;
//     sy = static_cast<qreal>(graphicsView->height())/static_cast<qreal>(pic.height())*0.9;
//     //qDebug() << sx << sy;
//     max_scale = qMin(sx,sy);
//     graphicsView->scale(max_scale, max_scale);

}

bool PicManager::addImages(const QString &path)
{
    QString dirName = path;

    if (dirName.isNull())
        dirName = QFileDialog::getExistingDirectory(this,\
		tr("Open Image Directory"), "D:\\uidp4086\\Desktop", QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);

    if( !dirName.isEmpty())
    {

        qDebug()<<dirName;
        QDir dir(dirName);
        QStringList filters;
// 		filters.append(QString("*.jpg"));
// 		filters.append(QString("*.jpeg"));
// 		filters.append(QString("*.png"));
// 		filters.append(QString("*.bmp"));
        foreach(QByteArray format, QImageReader::supportedImageFormats())
            filters += "*." + format;

        QList<QTreeWidgetItem *> items; 
        static int i = 0;
        foreach(QString file, dir.entryList(filters, QDir::Files))
        {
            QStringList tempItemStr(QString("%1").arg(i++));
            tempItemStr.append(QString("%1").arg(file));
            
            file = dirName + QDir::separator() + file;
			CSkinImageItem tempPicItem(0,0);
			tempPicItem.LoadImageFromFile(file);
			tempItemStr.append(QString("%1").arg(tempPicItem.GetImageHandle().GetHandle()));
			tempItemStr.append(tr(""));
            tempItemStr.append(QString("%1").arg(file));
            items.append(new QTreeWidgetItem((QTreeWidget*)treeWidget, tempItemStr));

        }

        treeWidget->addTopLevelItems(items);


        foreach(QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
            this->addImages(dirName + QDir::separator() + subDir);
    }

    return true;
}

void PicManager::contextMenuEvent(QContextMenuEvent* e)
{
	if( treeWidget->currentItem() )
	{
		QMenu *menu = new QMenu();  
		menu->addAction(deleteAction);
		menu->addAction(testAction);

		menu->exec(e->globalPos());  
		delete menu;  
	}

}
