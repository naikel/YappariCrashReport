#include <QApplication>
#include <QMessageBox>
#include <QIcon>
#include <QDebug>

#include <cassert>

#ifdef YAPPARI_CRASH_REPORT
#include "YappariCrashReport.h"
#endif

class crashTest
{
   public:
      void  crashMe() { _function1(); }

   private:
      // The purpose of all the private methods is just to provide a slightly longer call stack

      void  _divideByZero( int val )
      {
         int   foo = val / 0;
      }

      void  _function2( int val )
      {
         ++val;

         _divideByZero( val );
      }

      void  _function1()
      {
         _function2( 41 );
      }
};


int main( int argc, char** argv )
{
   QApplication  app( argc, argv );

   app.setApplicationName( QStringLiteral( "YappariCrashReportExample" ) );
   app.setApplicationVersion( QStringLiteral( "1.0.0" ) );
   app.setWindowIcon(QIcon(QPixmap(":icons/bomb.png")));


#ifdef YAPPARI_CRASH_REPORT
   YappariCrashReport::setSignalHandler( [] (const QString &inStackTrace) {

       const QStringList strList = QStringList(inStackTrace.split("\n"));
       for (const QString &str : strList)
           qCritical() << str;
   });
#endif


   crashTest().crashMe();

   return app.exec();
}
