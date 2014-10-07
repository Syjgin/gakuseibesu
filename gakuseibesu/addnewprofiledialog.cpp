#include "addnewprofiledialog.h"
#include "ui_addnewprofiledialog.h"

AddNewProfileDialog::AddNewProfileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewProfileDialog)
{
    ui->setupUi(this);
}

AddNewProfileDialog::~AddNewProfileDialog()
{
    delete ui;
}
