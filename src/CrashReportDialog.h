#ifndef CRASHREPORTDIALOG_H
#define CRASHREPORTDIALOG_H

#include <QDialog>

namespace Ui {
class CrashReportDialog;
}

namespace YappariCrashReport
{
class CrashReportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CrashReportDialog(QString fileName, QString stackTrace, QWidget *parent = nullptr);
    ~CrashReportDialog();

public slots:
    void saveStackTrace();
    void closeProgram();
    void writeLog(const QString &fileName);


private:
    Ui::CrashReportDialog *ui;

    QString stackTraceFileName;
};
}

#endif // CRASHREPORTDIALOG_H
