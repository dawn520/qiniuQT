#-------------------------------------------------
#
# Project created by QtCreator 2018-01-18T17:43:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qiniuQT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        qiniu.cpp

HEADERS += \
        mainwindow.h \
        mainwindow.h \
        qiniu.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    images.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/qiniu/lib/ -lqiniu
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/qiniu/lib/ -lqiniu
else:unix: LIBS += -L$$PWD/lib/qiniu/lib/ -lqiniu

INCLUDEPATH += $$PWD/lib/qiniu/include
DEPENDPATH += $$PWD/lib/qiniu/include

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/qiniu/lib/libqiniu.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/qiniu/lib/libqiniu.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/qiniu/lib/qiniu.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/qiniu/lib/qiniu.lib
#else:unix: PRE_TARGETDEPS += $$PWD/lib/qiniu/lib/libqiniu.a

#win32: LIBS += -L$$PWD/../qiniuQT/lib/qiniu/lib/ -lqiniu

#INCLUDEPATH += $$PWD/../qiniuQT/lib/qiniu/include
#DEPENDPATH += $$PWD/../qiniuQT/lib/qiniu/include

#win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../qiniuQT/lib/qiniu/lib/qiniu.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/../qiniuQT/lib/qiniu/lib/libqiniu.a

win32-g++{
    message("config win32-g++");
}
else:win32{
 message("config win32");
}
else:unix{
 message("config unix");
}

#unix|win32: LIBS += -L$$PWD/../qiniuQT/lib/qiniu/lib/ -lqiniu

#INCLUDEPATH += $$PWD/../qiniuQT/lib/qiniu/include
#DEPENDPATH += $$PWD/../qiniuQT/lib/qiniu/include

#win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../qiniuQT/lib/qiniu/lib/qiniu.lib
#else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../qiniuQT/lib/qiniu/lib/libqiniu.a

#win32: LIBS += -L$$PWD/lib/qiniu/lib/ -lqiniu

#INCLUDEPATH += $$PWD/lib/qiniu/include
#DEPENDPATH += $$PWD/lib/qiniu/include

#win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/qiniu/lib/qiniu.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/qiniu/lib/libqiniu.a
