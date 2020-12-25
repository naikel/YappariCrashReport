#ifndef CHOOSECRASHDIALOG_H
#define CHOOSECRASHDIALOG_H

#include <QDialog>

namespace Ui {
class ChooseCrashDialog;
}

class ChooseCrashDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseCrashDialog(QWidget *parent = nullptr);
    ~ChooseCrashDialog();

    int getCrashType();

private:
    Ui::ChooseCrashDialog *ui;
};

#endif // CHOOSECRASHDIALOG_H
