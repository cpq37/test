//#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include <QLabel>
#include <QPushButton>

#include "mainwindow.h"

#include "UIEngine/ImageResourceManager.h"
#include "Common/setdebugnew.h"

int main(int argc, char *argv[])
{
#ifdef _DEBUG 
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    QApplication a(argc, argv);

    /**********************************************************************
    QPushButton* button = new QPushButton(QObject::tr("Quit"));
    QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()) );
    button->show();
    **********************************************************************/

    MainWindow mainWindow;
    mainWindow.setGeometry(100, 100, 1100, 680);
    mainWindow.show();

#if defined(WIN32) && defined(_DEBUG)  
	setFilterDebugHook();  
#endif  
    return a.exec();
}
