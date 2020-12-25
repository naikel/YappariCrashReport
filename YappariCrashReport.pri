
CONFIG (release, release|debug) {
    !build_pass:message( 'Enabling YappariCrashReport and including debug symbols' )

    QT += widgets

    DEFINES += YAPPARI_CRASH_REPORT

VPATH += $$PWD/src
    DEPENDPATH += $$PWD/src
    INCLUDEPATH += $$PWD/src

    HEADERS += \
    $$PWD/src/YappariCrashReport.h

    SOURCES += \
    $$PWD/src/YappariCrashReport.cpp

    FORMS += \
        $$PWD/src/crashreportdialog.ui


    RESOURCES += \
        $$PWD/src/resources.qrc


    win32-g++* {
        QMAKE_CFLAGS_RELEASE -= -O2
        QMAKE_CXXFLAGS_RELEASE -= -O2

        QMAKE_CFLAGS_RELEASE += -g -O0
        QMAKE_CXXFLAGS_RELEASE += -g -O0
        QMAKE_LFLAGS_RELEASE =

        LIBS += -lDbghelp
    }

    mac {
        QMAKE_CFLAGS_RELEASE -= -O2
        QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO -= -O2
        QMAKE_CXXFLAGS_RELEASE -= -O2
        QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO -= -O2

        QMAKE_CFLAGS_RELEASE += -g -fno-pie -fno-omit-frame-pointer -O0
        QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO += -fno-pie -fno-omit-frame-pointer -O0
        QMAKE_CXXFLAGS_RELEASE += -g -fno-pie -fno-omit-frame-pointer -O0
        QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO += -fno-pie -fno-omit-frame-pointer -O0

        QMAKE_LFLAGS_RELEASE += -Wl,-no_pie
    }

    linux {
        QMAKE_CFLAGS_RELEASE -= -O2
        QMAKE_CXXFLAGS_RELEASE -= -O2

        QMAKE_CFLAGS_RELEASE += -g -O0
        QMAKE_CXXFLAGS_RELEASE += -g -O0
    }
}

CONFIG (debug, release|debug) {
    message( 'NOTE: YappariCrashReport is only valid for release builds' )
}

SOURCES += \
    $$PWD/src/CrashReportDialog.cpp

HEADERS += \
    $$PWD/src/CrashReportDialog.h
