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
CONFIG(debug, debug|release){
    win32:DESTDIR = ../../bin/win32/debug
}
else{
    win32:DESTDIR = ../../bin/win32/release
}



# moc文件存放路径
MOC_DIR = temp

# uic生成的头文件存放的路径
UI_HEADERS_DIR = ui

# 宏定义
# 路径
PLATFORM_PATH =

# 应用程序中的所有.ui文件（由Qt设计器生成）的列表
FORMS += ../../src/TestUI.ui \
    ../../src/picmanager.ui
RESOURCES += 


# 应用程序中的所有源文件的列表
SOURCES += \
    ../../src/UIEngine/ImageResourceManager.cpp \
    ../../src/Common/setdebugnew.cpp \
    ../../src/Common/xFile/xmemfile.cpp \
    ../../src/main.cpp \
    ../../src/mainwindow.cpp \
    ../../src/workscene.cpp \
    ../../src/myimageitem.cpp \
    ../../src/Controls/DrawUnit.cpp \
    ../../src/Controls/SkinBase.cpp \
    ../../src/Controls/SkinImageItem.cpp \
    ../../src/Controls/SkinContainer.cpp \
    ../../src/picmanager.cpp \
    ../../src/UIEngine/fui_imagesfactory.cpp \
    ../../src/UIEngine/imagemgr.cpp

# 应用程序所需的额外的包含路径的列表
HEADERS += \
    ../../src/UIEngine/ImageResourceManager.h \
    ../../src/UIEngine/handle.h \
    ../../src/UIEngine/handlemgr.h \
    ../../src/UIEngine/imagemgr.h \
    ../../src/Common/setdebugnew.h \
    ../../src/Common/xFile/xfile.h \
    ../../src/Common/xFile/xiofile.h \
    ../../src/Common/xFile/xmemfile.h \
    ../../src/mainwindow.h \
    ../../src/workscene.h \
    ../../src/myimageitem.h \
    ../../src/Controls/DrawUnit.h \
    ../../src/Controls/SkinBase.h \
    ../../src/Controls/SkinImageItem.h \
    ../../src/Controls/SkinContainer.h \
    ../../src/picmanager.h \
    ../../src/UIEngine/fui_imagesfactory.h


# 寻找补充文件的搜索路径
VPATH += 

# 应用程序所需的额外的包含路径的列表
INCLUDEPATH += 

# -L：引入路径 -l：引入lib(不含后缀)
LIBS +=

win32{
 CONFIG(debug, debug|release) {  
	# vld 1.9h downloaded from http://vld.codeplex.com/   
	#VLD_PATH = ../../vld-1.9h
	INCLUDEPATH += ../../vld-1.9h/include 
	LIBS += -L../../vld-1.9h/lib/ -lvld  
	}
}