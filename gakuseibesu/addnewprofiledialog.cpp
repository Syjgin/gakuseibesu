#include "addnewprofiledialog.h"
#include "ui_addnewprofiledialog.h"

AddNewProfileDialog::AddNewProfileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewProfileDialog)
{
    ui->setupUi(this);
    profileToEdit = Profile();
    ui->telephone->setValidator(new QIntValidator());
    ui->dateEdit->setDate(QDate::currentDate());
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
    ui->dateEdit->setDate(profileToEdit.Birthday);
    UpdateAgeLabel(profileToEdit.Birthday);
    ui->document->setText(profileToEdit.Document);
    ui->address->setText(profileToEdit.Addres);
    ui->telephone->setText(QString::number(profileToEdit.Telephone));
    ui->sexComboBox->setCurrentIndex(profileToEdit.Sex==0);
    ui->sensei->setText(profileToEdit.Sensei);
    UpdateGradeLabel();
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

void AddNewProfileDialog::SetId(int id)
{
    profileToEdit.Id = id;
}


void AddNewProfileDialog::on_buttonBox_accepted()
{
    profileToEdit.Firstname = ui->firstName->text();
    profileToEdit.Lastname = ui->lastName->text();
    profileToEdit.Patronym = ui->patronymic->text();
    profileToEdit.Birthday = ui->dateEdit->date();
    profileToEdit.Document = ui->document->text();
    profileToEdit.Addres = ui->address->text();
    profileToEdit.Telephone = ui->telephone->text().toUInt();
    profileToEdit.Sex = ui->sexComboBox->currentIndex()==0;
    profileToEdit.Sensei = ui->sensei->text();
}

void AddNewProfileDialog::UpdateAgeLabel(QDate date)
{
    QDateTime current = QDateTime::currentDateTime();
    QDateTime fullBirthday = QDateTime(date, QTime(0,0));
    auto totalSecs =  fullBirthday.secsTo(current);
    int totalYears = 0;
    while(totalSecs > 0)
    {
        totalSecs -= SecsInYear;
        if(totalSecs > 0)
            totalYears++;
    }
    ui->ageLabel->setText(Age + QString::number(totalYears));
}

void AddNewProfileDialog::UpdateGradeLabel()
{
    auto grades = Database::GetInstance()->GetGradesByProfile(profileToEdit.Id);
    Grade selectedGrade;
    if(grades.count() > 0)
        selectedGrade = grades[0];
    else
        return;
    if(grades.count() > 1)
        foreach (Grade currentGrade, grades) {
            if(currentGrade.Date > selectedGrade.Date)
                selectedGrade = currentGrade;
        }
    ui->lastGrade->setText(selectedGrade.GradeString);
}

void AddNewProfileDialog::on_dateEdit_userDateChanged(const QDate &date)
{
    UpdateAgeLabel(date);
}

void AddNewProfileDialog::on_editGrades_clicked()
{
    auto editGradesWindow = new EditGrades(profileToEdit.Id, this);
    editGradesWindow->setModal(true);
    editGradesWindow->exec();
    UpdateGradeLabel();
    delete editGradesWindow;
}
