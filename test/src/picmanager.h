#ifndef PICMANAGER_H
#define PICMANAGER_H

#include <QWidget>

#include "ui_picmanager.h"

namespace Ui {
class PicManager;
}

class QTreeWidgetItem;
class QGraphicsScene;

class PicManager : public QWidget, public Ui_PicManager
{
    Q_OBJECT
    
public:
    explicit PicManager(QWidget *parent = 0);
    ~PicManager();
    
public slots:
    void on_addPicButton_clicked();
    void on_test(QTreeWidgetItem * item, int column);
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
};

#endif // PICMANAGER_H
