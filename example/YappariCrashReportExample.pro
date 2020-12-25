message( "Building example" )

TARGET = YappariCrashReportExample
TEMPLATE = app

mac:CONFIG -= app_bundle
CONFIG += c++14

QT += widgets

if ( !include( ../YappariCrashReport.pri ) ) {
    error( Could not find the YappariReport.pri file. )
}

SOURCES += \
    main.cpp
