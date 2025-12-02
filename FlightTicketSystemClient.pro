QT       += core gui
QT       +=core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    flight_result_widget.cpp \
    login_widget.cpp \
    main.cpp \
    mainwindow.cpp \
    network_manager.cpp \
    order_widget.cpp \
    personal_center_widget.cpp \
    register_widget.cpp

HEADERS += \
    flight_result_widget.h \
    login_widget.h \
    mainwindow.h \
    network_manager.h \
    order_widget.h \
    personal_center_widget.h \
    register_widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

FORMS +=
