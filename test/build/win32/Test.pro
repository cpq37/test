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
SOURCES += ../../src/main.cpp \
    ../../src/mainwindow.cpp \
    ../../src/workscene.cpp \
    ../../src/myimageitem.cpp

# Ӧ�ó�������Ķ���İ���·�����б�
HEADERS += \
    ../../src/mainwindow.h \
    ../../src/workscene.h \
    ../../src/myimageitem.h

# Ӧ�ó�������Ķ���İ���·�����б�
INCLUDEPATH +=

# Ѱ�Ҳ����ļ�������·��
VPATH += 

# -L������·�� -l������lib(������׺)
LIBS +=