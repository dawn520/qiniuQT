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
    lib/CUnit/Examples/WinTest/StdAfx.cpp \
    lib/CUnit/Examples/WinTest/WinTest.cpp \
    lib/CUnit/Examples/WinTest/WinTest_v1.cpp \
    main.cpp \
    mainwindow.cpp \
    lib/b64/b64.c \
    lib/b64/urlsafe_b64.c \
    lib/cJSON/cJSON.c \
    lib/CUnit/CUnit/Sources/Automated/Automated.c \
    lib/CUnit/CUnit/Sources/Basic/Basic.c \
    lib/CUnit/CUnit/Sources/Console/Console.c \
    lib/CUnit/CUnit/Sources/Curses/Curses.c \
    lib/CUnit/CUnit/Sources/Framework/CUError.c \
    lib/CUnit/CUnit/Sources/Framework/MyMem.c \
    lib/CUnit/CUnit/Sources/Framework/TestDB.c \
    lib/CUnit/CUnit/Sources/Framework/TestRun.c \
    lib/CUnit/CUnit/Sources/Framework/Util.c \
    lib/CUnit/CUnit/Sources/Test/test_cunit.c \
    lib/CUnit/CUnit/Sources/Win/Win.c \
    lib/CUnit/Examples/AutomatedTest/AutomatedTest.c \
    lib/CUnit/Examples/BasicTest/BasicTest.c \
    lib/CUnit/Examples/ConsoleTest/ConsoleTest.c \
    lib/CUnit/Examples/CursesTest/CursesTest.c \
    lib/CUnit/Examples/ExampleTests.c \
    lib/demo/demo.c \
    lib/docs/gist/client.c \
    lib/docs/gist/server.c \
    lib/qiniu/auth_mac.c \
    lib/qiniu/base.c \
    lib/qiniu/base_io.c \
    lib/qiniu/conf.c \
    lib/qiniu/http.c \
    lib/qiniu/io.c \
    lib/qiniu/resumable_io.c \
    lib/qiniu/rs.c \
    lib/tests/equal.c \
    lib/tests/seq.c \
    lib/tests/test.c \
    lib/tests/test_base_io.c \
    lib/tests/test_fmt.c \
    lib/tests/test_io_put.c \
    lib/tests/test_resumable_io.c \
    lib/tests/test_rs_ops.c \
    qiniu.cpp

HEADERS += \
        mainwindow.h \
    lib/b64/b64.h \
    lib/b64/urlsafe_b64.h \
    lib/cJSON/cJSON.h \
    lib/CUnit/CUnit/Headers/Automated.h \
    lib/CUnit/CUnit/Headers/Basic.h \
    lib/CUnit/CUnit/Headers/Console.h \
    lib/CUnit/CUnit/Headers/CUCurses.h \
    lib/CUnit/CUnit/Headers/CUError.h \
    lib/CUnit/CUnit/Headers/CUnit.h \
    lib/CUnit/CUnit/Headers/CUnit_intl.h \
    lib/CUnit/CUnit/Headers/MyMem.h \
    lib/CUnit/CUnit/Headers/TestDB.h \
    lib/CUnit/CUnit/Headers/TestRun.h \
    lib/CUnit/CUnit/Headers/Util.h \
    lib/CUnit/CUnit/Sources/Win/resource.h \
    lib/CUnit/CUnit/Sources/Win/Win.h \
    lib/CUnit/doc/headers/Automated.h \
    lib/CUnit/doc/headers/Basic.h \
    lib/CUnit/doc/headers/Console.h \
    lib/CUnit/doc/headers/CUCurses.h \
    lib/CUnit/doc/headers/CUError.h \
    lib/CUnit/doc/headers/CUnit.h \
    lib/CUnit/doc/headers/CUnit_intl.h \
    lib/CUnit/doc/headers/MyMem.h \
    lib/CUnit/doc/headers/TestDB.h \
    lib/CUnit/doc/headers/TestRun.h \
    lib/CUnit/doc/headers/Util.h \
    lib/CUnit/doc/headers/Win.h \
    lib/CUnit/doc/headers/wxWidget.h \
    lib/CUnit/Examples/WinTest/StdAfx.h \
    lib/qiniu/base.h \
    lib/qiniu/conf.h \
    lib/qiniu/http.h \
    lib/qiniu/io.h \
    lib/qiniu/resumable_io.h \
    lib/qiniu/rs.h \
    lib/tests/test.h \
    mainwindow.h \
    qiniu.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    images.qrc
