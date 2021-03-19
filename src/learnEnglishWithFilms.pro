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
    main.cpp \
    mainwindow.cpp \
    patronpage.cpp \
    welcomepage.cpp

HEADERS += \
    NewProjectWizard/firstpage.h \
    NewProjectWizard/secondpage.h \
    NewProjectWizard/wizard.h \
    config/newproject_config.h \
    costomMessageBox/messagebox.h \
    fileOperate/fileoperate.h \
    mainwindow.h \
    patronpage.h \
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
