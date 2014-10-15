#ifndef PICMANAGER_H
#define PICMANAGER_H

#include <QWidget>

namespace Ui {
class PicManager;
}

class QTreeWidgetItem;

class PicManager : public QWidget/*, public Ui::PicManager*/
{
    Q_OBJECT
    
public:
    explicit PicManager(QWidget *parent = 0);
    ~PicManager();
    
public slots:
    void on_addPicButton_clicked();
    void on_test(QTreeWidgetItem * item, int column);

private:
    bool addImages(const QString &path);
private:
    Ui::PicManager *ui;
};

#endif // PICMANAGER_H
