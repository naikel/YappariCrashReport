#include "choosecrashdialog.h"
#include "ui_choosecrashdialog.h"

#include <QListWidgetItem>

ChooseCrashDialog::ChooseCrashDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseCrashDialog)
{
    ui->setupUi(this);

    new QListWidgetItem(tr("Divide By Zero"), ui->listWidget);
    new QListWidgetItem(tr("Access Violation"), ui->listWidget);
    new QListWidgetItem(tr("Stack Overflow"), ui->listWidget);
    new QListWidgetItem(tr("Throw Error"), ui->listWidget);
    new QListWidgetItem(tr("Out of Bounds"), ui->listWidget);
    new QListWidgetItem(tr("Abort"), ui->listWidget);
}

ChooseCrashDialog::~ChooseCrashDialog()
{
    delete ui;
}

int ChooseCrashDialog::getCrashType()
{

    QList<QListWidgetItem *> selectedItems = ui->listWidget->selectedItems();

    if (selectedItems.size() > 0)
        return ui->listWidget->currentRow();

    return -1;
}
