#-------------------------------------------------
#
# Project created by QtCreator 2012-05-09T01:10:59
#
#-------------------------------------------------

# 建立一个应用程序的makefile
TEMPLATE = app 


# 告诉qmake关于应用程序的配置信息
#CONFIG   += console
#CONFIG   -= app_bundle


# qt库
QT       += core \
    gui


# 指定生成的应用程序名
TARGET = Test

# 放置可执行程序目标的目录
DESTDIR =  #../../lib/x86


# moc文件存放路径
MOC_DIR += temp


# 宏定义
# 路径
PLATFORM_PATH =

# 应用程序中的所有.ui文件（由Qt设计器生成）的列表
FORMS += ../../src/TestUI.ui
RESOURCES += 


# 应用程序中的所有源文件的列表
SOURCES += \
    ../../src/UIEngine/ImageResourceManager.cpp \
    ../../src/Controls/SkinBase.cpp \
    ../../src/Controls/DrawUnit.cpp \
    ../../src/Common/setdebugnew.cpp \
    ../../src/Common/xFile/xmemfile.cpp \
    ../../src/main.cpp \
    ../../src/mainwindow.cpp \
    ../../src/workscene.cpp \
    ../../src/myimageitem.cpp \
    ../../src/Controls/DrawUnit.cpp \
    ../../src/Controls/SkinBase.cpp

# 应用程序所需的额外的包含路径的列表
HEADERS += \
    ../../src/UIEngine/ImageResourceManager.h \
    ../../src/Controls/SkinBase.h \
    ../../src/Controls/DrawUnit.h \
    ../../src/Common/setdebugnew.h \
    ../../src/Common/xFile/xfile.h \
    ../../src/Common/xFile/xiofile.h \
    ../../src/Common/xFile/xmemfile.h \
    ../../src/mainwindow.h \
    ../../src/workscene.h \
    ../../src/myimageitem.h \
    ../../src/Controls/DrawUnit.h \
    ../../src/Controls/SkinBase.h


# 应用程序所需的额外的包含路径的列表
INCLUDEPATH +=

# 寻找补充文件的搜索路径
VPATH += 

# -L：引入路径 -l：引入lib(不含后缀)
LIBS +=