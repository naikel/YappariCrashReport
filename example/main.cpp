/*
 * Copyright (C) 2017, 2020 Andy Maloney, Naikel Aparicio. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ''AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation
 * are those of the author and should not be interpreted as representing
 * official policies, either expressed or implied, of the copyright holder.
 */

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
