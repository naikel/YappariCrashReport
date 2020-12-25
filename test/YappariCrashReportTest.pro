message( "Building test" )

TARGET = YappariCrashReportTest
TEMPLATE = app

mac:CONFIG -= app_bundle
CONFIG += c++14

QT += widgets

if ( !include( ../YappariCrashReport.pri ) ) {
    error( Could not find the YappariCrashReport.pri file. )
}

SOURCES += \
    choosecrashdialog.cpp \
    main.cpp

FORMS += \
    choosecrashdialog.ui

HEADERS += \
    choosecrashdialog.h
