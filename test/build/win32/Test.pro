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
DESTDIR =  #../../lib/x86


# moc�ļ����·��
MOC_DIR += temp


# �궨��
# ·��
PLATFORM_PATH =

# Ӧ�ó����е�����.ui�ļ�����Qt��������ɣ����б�
FORMS += ../../src/TestUI.ui
RESOURCES += 


# Ӧ�ó����е�����Դ�ļ����б�
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

# Ӧ�ó�������Ķ���İ���·�����б�
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


# Ӧ�ó�������Ķ���İ���·�����б�
INCLUDEPATH +=

# Ѱ�Ҳ����ļ�������·��
VPATH += 

# -L������·�� -l������lib(������׺)
LIBS +=