QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

#LIBS   += -lopengl32

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/controller.cc \
    Model/glwidget.cc \
    Model/parser.cc \
    Model/model.cc\
    Model/affine.cc \
    main.cc \
    View/mainwindow.cc


HEADERS += \
    Controller/controller.h \
    Model/glwidget.h \
    Model/parser.h \
    Model/model.h \
    Model/affine.h \
    View/mainwindow.h

FORMS += \
    View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
