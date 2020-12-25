#ifndef ASMCRASHREPORT_H
#define ASMCRASHREPORT_H

#include <QString>


namespace YappariCrashReport {

   /// Function signature for a crash report callback, called after the user has seen the report
   /// @param inCrashReport The report including the stack trace as a QString
   using crashReportCallback = void (*)(const QString &);

   ///! Set a signal handler to capture stack trace to a log file.
   ///
   /// @param inCrashReportCallback A callback function to call after we've shown the dialog to the user
   void setSignalHandler( crashReportCallback inCrashReportCallback = nullptr );

}

#endif
