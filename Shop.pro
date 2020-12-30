QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += Core GUI

SOURCES += \
    Core/CoreGlobals.cpp \
    Core/Database/Database.cpp \
    Core/Starter.cpp \
    GUI/Admin_pages/AdminMainPage.cpp \
    GUI/Cashier_pages/CashierMainPage.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    Core/CoreGlobals.h \
    Core/Database/Database.h \
    Core/Database/Utils/DataStructs.h \
    Core/Database/Utils/Enums.h \
    Core/Starter.h \
    GUI/Admin_pages/AdminMainPage.h \
    GUI/Cashier_pages/CashierMainPage.h \
    MainWindow.h

FORMS += \
    GUI/Admin_pages/AdminMainPage.ui \
    GUI/Cashier_pages/CashierMainPage.ui \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
