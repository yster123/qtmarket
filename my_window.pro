QT       += core gui
QT       += sql charts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    manager_port.cpp \
    mybtn.cpp \
    mylabel.cpp \
    payout.cpp \
    register_window.cpp \
    shoppinglist.cpp \
    sqlconnect.cpp

HEADERS += \
    mainwindow.h \
    manager_port.h \
    mybtn.h \
    mylabel.h \
    payout.h \
    register_window.h \
    shoppinglist.h \
    sqlconnect.h

FORMS += \
    mainwindow.ui \
    manager_port.ui \
    payout.ui \
    register_window.ui \
    shoppinglist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
