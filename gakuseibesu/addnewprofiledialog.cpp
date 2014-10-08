#include "addnewprofiledialog.h"
#include "ui_addnewprofiledialog.h"

AddNewProfileDialog::AddNewProfileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewProfileDialog)
{
    ui->setupUi(this);
    profileToEdit = Profile();
}

AddNewProfileDialog::~AddNewProfileDialog()
{
    delete ui;
}

void AddNewProfileDialog::LoadProfile(Profile profile)
{

}

Profile AddNewProfileDialog::GetUpdatedProfile()
{
    return profileToEdit;
}


void AddNewProfileDialog::on_buttonBox_accepted()
{
    profileToEdit.Firstname = ui->firstName->text();
    profileToEdit.Lastname = ui->lastName->text();
    profileToEdit.Patronym = ui->patronymic->text();
    profileToEdit.Birthday = ui->calendarWidget->selectedDate();
    profileToEdit.Document = ui->document->text();
    profileToEdit.Addres = ui->address->text();
    profileToEdit.Telephone = ui->telephone->text().toUInt();
    profileToEdit.Sex = ui->sexComboBox->currentIndex()==0;
}
