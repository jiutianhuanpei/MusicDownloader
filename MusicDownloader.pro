QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR = "Build_Debug"
RCC_DIR = "Build_Debug"
MOC_DIR = "Build_Debug"
UI_DIR = "Build_Debug"
#OUT_PWD = "Build_Debug"



SOURCES += \
    main.cpp \

HEADERS += \

FORMS += \

TRANSLATIONS += \

INCLUDEPATH += "UI"


include(Base/Base.pri)
include(Model/Model.pri)
include(Net/Net.pri)
include(UI/UI.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
