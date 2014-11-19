#ifndef PICMANAGER_H
#define PICMANAGER_H

#include <QWidget>

#include "ui_picmanager.h"
#include "UIEngine/fui_imagesfactory.h"

namespace Ui {
class PicManager;
}

class QTreeWidgetItem;
class QGraphicsScene;

class PicManager : public QWidget, public Ui_PicManager
{
    Q_OBJECT

Q_SIGNALS:
	void signalAddPicture(const HImage &hImage);
    
public:
    explicit PicManager(QWidget *parent = 0);
    ~PicManager();
    
public slots:
    void on_addPicButton_clicked();
	void on_deletItem();
    void on_test();
	void on_showItem(QTreeWidgetItem * item, int column);
protected:
	void contextMenuEvent(QContextMenuEvent* e);
private:
    bool addImages(const QString &path);
	void createActions(void);
	void createTreeWidget(void);
private:
    //Ui::PicManager *ui;
    QGraphicsScene	*m_pScene;
	QAction			*deleteAction;
	QAction			*testAction;
};

#endif // PICMANAGER_H
