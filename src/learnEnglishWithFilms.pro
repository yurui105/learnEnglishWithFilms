QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    NewProjectWizard/firstpage.cpp \
    NewProjectWizard/secondpage.cpp \
    NewProjectWizard/wizard.cpp \
    config/newproject_config.cpp \
    costomMessageBox/messagebox.cpp \
    fileOperate/fileoperate.cpp \
    fileOperate/openproject.cpp \
    main.cpp \
    mainwindow.cpp \
    media/videoinformation.cpp \
    patronpage.cpp \
    subtittleProcess/dividestr2dict.cpp \
    welcomepage.cpp

HEADERS += \
    NewProjectWizard/firstpage.h \
    NewProjectWizard/secondpage.h \
    NewProjectWizard/wizard.h \
    config/newproject_config.h \
    costomMessageBox/messagebox.h \
    dataProcess/ASinfo.h \
    fileOperate/fileoperate.h \
    fileOperate/openproject.h \
    mainwindow.h \
    media/videoinformation.h \
    patronpage.h \
    subtittleProcess/dividestr2dict.h \
    welcomepage.h

FORMS += \
    NewProjectWizard/firstpage.ui \
    NewProjectWizard/secondpage.ui \
    mainwindow.ui \
    patronpage.ui \
    welcomepage.ui

TRANSLATIONS += \
    learnEnglishWithFilms_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    config/LEWFconfig.json

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include

LIBS += -L$$PWD/../lib/ -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc -lswresample -lswscale


#LIBS += -L$$PWD/../lib/avcodec.lib \
#        -L$$PWD/../lib/avdevice.lib \
#        -L$$PWD/../lib/avfilter.lib \
#        -L$$PWD/../lib/avformat.lib \
#        -L$$PWD/../lib/avutil.lib \
#        -L$$PWD/../lib/postproc.lib \
#        -L$$PWD/../lib/swresample.lib \
#        -L$$PWD/../lib/swscale.lib


#LIBS += -L$$PWD/../bin -lavcodec-58
#LIBS += -L$$PWD/../bin -lavdevice-58
#LIBS += -L$$PWD/../bin -lavformat-58
#LIBS += -L$$PWD/../bin -lpostproc-55
#LIBS += -L$$PWD/../bin -lswresample-3
#LIBS += -L$$PWD/../bin -lswscale-5




