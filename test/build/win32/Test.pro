#-------------------------------------------------
#
# Project created by QtCreator 2012-05-09T01:10:59
#
#-------------------------------------------------

# ����һ��Ӧ�ó����makefile
TEMPLATE = app 


# ����qmake����Ӧ�ó����������Ϣ
#CONFIG   += console
#CONFIG   -= app_bundle


# qt��
QT       += core \
    gui


# ָ�����ɵ�Ӧ�ó�����
TARGET = Test

# ���ÿ�ִ�г���Ŀ���Ŀ¼
CONFIG(debug, debug|release){
    win32:DESTDIR = ../../bin/win32/debug
}
else{
    win32:DESTDIR = ../../bin/win32/release
}



# moc�ļ����·��
MOC_DIR = temp

# uic���ɵ�ͷ�ļ���ŵ�·��
UI_HEADERS_DIR = ui

# �궨��
# ·��
PLATFORM_PATH =

# Ӧ�ó����е�����.ui�ļ�����Qt��������ɣ����б�
FORMS += ../../src/TestUI.ui \
    ../../src/picmanager.ui
RESOURCES += 


# Ӧ�ó����е�����Դ�ļ����б�
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
    ../../src/picmanager.cpp \
    ../../src/UIEngine/fui_imagesfactory.cpp \
    ../../src/UIEngine/imagemgr.cpp

# Ӧ�ó�������Ķ���İ���·�����б�
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
    ../../src/picmanager.h \
    ../../src/UIEngine/fui_imagesfactory.h


# Ѱ�Ҳ����ļ�������·��
VPATH += 

# Ӧ�ó�������Ķ���İ���·�����б�
INCLUDEPATH += 

# -L������·�� -l������lib(������׺)
LIBS +=

win32{
 CONFIG(debug, debug|release) {  
	# vld 1.9h downloaded from http://vld.codeplex.com/   
	#VLD_PATH = ../../vld-1.9h
	INCLUDEPATH += ../../vld-1.9h/include 
	LIBS += -L../../vld-1.9h/lib/ -lvld  
	}
}