//#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include <QLabel>
#include <QPushButton>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /**********************************************************************
    QPushButton* button = new QPushButton(QObject::tr("Quit"));
    QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()) );
    button->show();
    **********************************************************************/

    MainWindow mainWindow;
    mainWindow.setGeometry(100, 100, 800, 500);
    mainWindow.show();

    return a.exec();
}
