/*
 * Copyright (C) 2020 Naikel Aparicio. All rights reserved.
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

#include <QFileDialog>
#include <QDebug>
#include <QDir>

#include "CrashReportDialog.h"
#include "ui_crashreportdialog.h"

namespace YappariCrashReport
{
CrashReportDialog::CrashReportDialog(QString fileName, QString stackTrace, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CrashReportDialog)
{
    this->stackTraceFileName = fileName;

    ui->setupUi(this);

    this->setWindowIcon(QApplication::windowIcon());
    this->setWindowTitle(QCoreApplication::applicationName());
    this->setWhatsThis("Crash report window");

    ui->dialogTitle->setText(QCoreApplication::applicationName() + " has stopped working");
    ui->iconLabel->setPixmap(QPixmap(":icons/bomb.png").scaled(64, 64));

    ui->infoLabel->setTextFormat(Qt::RichText);
    ui->infoLabel->setText("Unfortunately a fatal error has occurred and this application has stopped.<br><br>"
                           "You can look at the report for more information. Press the <b>Save report</b> button to save it to a file.");

    ui->textEdit->setText(stackTrace);
    ui->textEdit->setReadOnly(true);
    ui->textEdit->setWhatsThis("Report of the exception that occurred including the exception's name and the stack trace");

    ui->saveStackTraceBtn->setWhatsThis("Click here to save the report to a file");
    ui->closeProgramBtn->setWhatsThis("Click here to close the program");

    connect(ui->closeProgramBtn, &QPushButton::clicked, this, &CrashReportDialog::closeProgram);
    connect(ui->saveStackTraceBtn, &QPushButton::clicked, this, &CrashReportDialog::saveStackTrace);
}

CrashReportDialog::~CrashReportDialog()
{
    delete ui;
}

void CrashReportDialog::saveStackTrace()
{
    QFileDialog *fileDialog = new QFileDialog(this);

    connect(fileDialog, &QFileDialog::fileSelected, this, &CrashReportDialog::writeLog);

    fileDialog->setFileMode(QFileDialog::DirectoryOnly);
    fileDialog->exec();
}

void CrashReportDialog::closeProgram()
{
    done(1);
}

void CrashReportDialog::writeLog(const QString &fileName)
{
    if (!fileName.isEmpty()) {

        QString newFileName = fileName + "/" + stackTraceFileName;

        qDebug() << newFileName;

        QFile file(newFileName);

        if (file.open( QIODevice::WriteOnly | QIODevice::Text ))
        {
           QTextStream stream( &file );

           QString data = ui->textEdit->toPlainText();
           stream << data << endl;

           file.close();
        }
    }
}
}
