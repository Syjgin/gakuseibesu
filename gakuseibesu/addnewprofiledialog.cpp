#include "addnewprofiledialog.h"
#include "ui_addnewprofiledialog.h"

AddNewProfileDialog::AddNewProfileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewProfileDialog)
{
    ui->setupUi(this);
    profileToEdit = Profile();
    ui->telephone->setValidator(new QIntValidator());
}

AddNewProfileDialog::~AddNewProfileDialog()
{
    delete ui;
}

void AddNewProfileDialog::LoadProfile(Profile profile)
{
    profileToEdit = profile;
    ui->firstName->setText(profileToEdit.Firstname);
    ui->lastName->setText(profileToEdit.Lastname);
    ui->patronymic->setText(profileToEdit.Patronym);
    ui->calendarWidget->setSelectedDate(profileToEdit.Birthday);
    ui->document->setText(profileToEdit.Document);
    ui->address->setText(profileToEdit.Addres);
    ui->telephone->setText(QString::number(profileToEdit.Telephone));
    ui->sexComboBox->setCurrentIndex(profileToEdit.Sex==0);
}

Profile AddNewProfileDialog::GetUpdatedProfile()
{
    return profileToEdit;
}

void AddNewProfileDialog::SetPurpose(AddNewProfileDialog::Purpose purpose)
{
    switch (purpose) {
    case Purpose::AddNewProfile:
        setWindowTitle(AddNewTitle);
        break;
    case Purpose::EditProfile:
        setWindowTitle(EditTitle);
        break;
    default:
        break;
    }
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

