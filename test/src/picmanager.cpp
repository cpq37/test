#include "picmanager.h"
#include "ui_picmanager.h"
#include "UIEngine/fui_imagesfactory.h"
#include "Controls/SkinImageItem.h"

#include <QFileDialog>
#include <QImageReader>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

using namespace SkinCtrl;

PicManager::PicManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PicManager)
    , m_pScene(NULL)
{
    ui->setupUi(this);

    //ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->treeWidget->setColumnCount(4);
    QStringList treeLabels(tr("ID"));
    treeLabels += tr("Name");
    treeLabels += tr("Size");
    treeLabels += tr("Path");
    ui->treeWidget->setHeaderLabels(treeLabels);
    ui->treeWidget->setColumnHidden(3, true);

    connect( ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(on_test(QTreeWidgetItem*,int)) );
}

PicManager::~PicManager()
{
    delete ui;
	delete FUI_ImagesFactory::GetInstance();
    //FUI_ImagesFactory::GetInstance()->SaveImagesToFile();
}

void PicManager::on_addPicButton_clicked()
{
    addImages(0);
}

void PicManager::on_test(QTreeWidgetItem * item, int column)
{
    //qDebug() << column << item->text(column);

    if( m_pScene )
        delete m_pScene;
    m_pScene = new QGraphicsScene(this);

    QPixmap pic(item->text(3));
    m_pScene->addPixmap(pic);
    ui->graphicsView->setScene(m_pScene);

    qreal sx = 1.0;
    qreal sy = 1.0;
    static qreal max_scale = qMin(sx,sy);
    ui->graphicsView->scale(1.0/max_scale,1.0/max_scale);
    //scale
    sx = static_cast<qreal>(ui->graphicsView->width())/static_cast<qreal>(pic.width())*0.9;
    sy = static_cast<qreal>(ui->graphicsView->height())/static_cast<qreal>(pic.height())*0.9;
    //qDebug() << sx << sy;
    max_scale = qMin(sx,sy);
    ui->graphicsView->scale(max_scale, max_scale);

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
        foreach(QByteArray format, QImageReader::supportedImageFormats())
            filters += "*." + format;

        QList<QTreeWidgetItem *> items;
        static int i = 0;
        foreach(QString file, dir.entryList(filters, QDir::Files))
        {
            QStringList tempItemStr(QString("%1").arg(i++));
            tempItemStr.append(QString("%1").arg(file));
            tempItemStr.append(tr(""));
            file = dirName + QDir::separator() + file;
            tempItemStr.append(QString("%1").arg(file));
            items.append(new QTreeWidgetItem((QTreeWidget*)ui->treeWidget, tempItemStr));

            CSkinImageItem tempPicItem(0,0);
            tempPicItem.LoadImageFromFile(file);
        }

        ui->treeWidget->addTopLevelItems(items);

        foreach(QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
            this->addImages(dirName + QDir::separator() + subDir);
    }

    return true;
}
