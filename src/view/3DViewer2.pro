QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../QtGifImage/src/gifimage/qtgifimage.pri)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/controller.cc \
    ../model/facade.cc \
    ../model/fileparcer.cc \
    ../model/objdata.cc \
    ../model/objtransform.cc \
    main.cc \
    scene.cc \
    view.cc

HEADERS += \
    ../controller/controller.h \
    ../model/facade.h \
    ../model/fileparcer.h \
    ../model/objdata.h \
    ../model/objtransform.h \
    scene.h \
    view.h

FORMS += \
    view.ui

win32 {
    LIBS += -lopengl32
}

unix {
    !macx {
        LIBS += -lGL
    }
    macx {
        LIBS += -framework OpenGL
    }
}
CONFIG+=sdk_no_version_check


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
