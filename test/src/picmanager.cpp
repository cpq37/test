#include "picmanager.h"
#include "ui_picmanager.h"

#include <QFileDialog>
#include <QImageReader>
#include <QDebug>

PicManager::PicManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PicManager)
{
    ui->setupUi(this);

    ui->treeWidget->setColumnCount(2);
    QStringList treeLabels(tr("Name"));
    treeLabels += tr("Size");
    ui->treeWidget->setHeaderLabels(treeLabels);

    connect( ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(on_test(QTreeWidgetItem*,int)) );
}

PicManager::~PicManager()
{
    delete ui;
}

void PicManager::on_addPicButton_clicked()
{
    addImages(0);
}

void PicManager::on_test(QTreeWidgetItem * item, int column)
{
    qDebug() << column << item->text(column);
}

bool PicManager::addImages(const QString &path)
{
    QString dirName = path;

    if (dirName.isNull())
        dirName = QFileDialog::getExistingDirectory(this,\
        tr("Open Image Directory"), "" );

    if( !dirName.isEmpty())
    {

        // qDebug()<<dirName;
        QDir dir(dirName);
        QStringList filters;
        foreach(QByteArray format, QImageReader::supportedImageFormats())
            filters += "*." + format;

        QList<QTreeWidgetItem *> items;
        foreach(QString file, dir.entryList(filters, QDir::Files))
        {
            file = dirName + QDir::separator() + file;
            items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("%1").arg(file))));
        }

        ui->treeWidget->addTopLevelItems(items);

        foreach(QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
            this->addImages(dirName + QDir::separator() + subDir);
    }

    return true;
}
