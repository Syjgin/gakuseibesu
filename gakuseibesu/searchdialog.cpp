#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    searchFields = QList<Database::SearchFields>();
    searchResults = QList<Profile>();
    ui->setupUi(this);
    QRegExp rx("\\d*");
    QValidator *validator = new QRegExpValidator(rx, this);
    ui->telephone->setValidator(validator);
    ui->document->setValidator(validator);
    ui->gradeDateStart->setDate(QDate::currentDate());
    ui->gradeDateEnd->setDate(QDate::currentDate());
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::CollectSearchResults()
{
    QDate dateStart = QDate();
    QDate dateEnd = QDate();
    QDate gradeDateStart = QDate();
    QDate gradeDateEnd = QDate();
    if(searchFields.contains(Database::SearchFields::date))
    {
        int yearStart = QDate::currentDate().year() - ui->ageStart->value();
        dateStart = QDate(yearStart, QDate::currentDate().month(), QDate::currentDate().day());
        int yearEnd = QDate::currentDate().year() - ui->ageEnd->value();
        dateEnd = QDate(yearEnd, QDate::currentDate().month(), QDate::currentDate().day());
    }
    if(searchFields.contains(Database::SearchFields::gradedate))
    {
        gradeDateStart = ui->gradeDateStart->date();
        gradeDateEnd = ui->gradeDateEnd->date();
    }
    Profile searchUser = Profile();
    if(ui->firstname->text() != "")
    {
        searchFields.append(Database::SearchFields::firstname);
        searchUser.Firstname = ui->firstname->text();
    }
    if(ui->lastname->text() != "")
    {
        searchFields.append(Database::SearchFields::lastname);
        searchUser.Lastname = ui->lastname->text();
    }
    if(ui->patronym->text() != "")
    {
        searchFields.append(Database::SearchFields::patronym);
        searchUser.Patronym = ui->patronym->text();
    }
    if(searchFields.contains(Database::SearchFields::sex))
    {
        searchUser.Sex = ui->sex->currentIndex()==0;
    }
    if(ui->document->text() != "")
    {
        searchFields.append(Database::SearchFields::document);
        searchUser.Document = ui->document->text();
    }
    if(ui->addres->text() != "")
    {
        searchFields.append(Database::SearchFields::addres);
        searchUser.Addres = ui->addres->text();
    }
    if(ui->telephone->text() != "")
    {
        searchFields.append(Database::SearchFields::telephone);
        searchUser.Telephone = ui->telephone->text();
    }
    if(ui->sensei->text() != "")
    {
        searchFields.append(Database::SearchFields::sensei);
        searchUser.Sensei = ui->sensei->text();
    }
    Grade searchGrade = Grade();
    if(ui->grade->text() != "")
    {
        searchFields.append(Database::SearchFields::grade);
        searchGrade.GradeString = ui->grade->text();
    }
    bool useOr = ui->searchMethod->currentIndex()==0;
    searchResults = Database::GetInstance()->FindProfiles(searchFields, searchUser, dateEnd, dateStart, searchGrade, gradeDateStart, gradeDateEnd, useOr);
}

QList<Profile> SearchDialog::GetSearchResults()
{
    return searchResults;
}




void SearchDialog::on_searchByAge_clicked(bool checked)
{
    if(checked)
    {
        if(!searchFields.contains(Database::SearchFields::date))
            searchFields.append(Database::SearchFields::date);
    }
    ui->ageStart->setEnabled(checked);
    ui->ageEnd->setEnabled(checked);
}


void SearchDialog::on_searchBySex_clicked(bool checked)
{
    if(checked)
    {
        if(!searchFields.contains(Database::SearchFields::sex))
            searchFields.append(Database::SearchFields::sex);
    }
    ui->sex->setEnabled(checked);
}


void SearchDialog::on_buttonBox_accepted()
{
    CollectSearchResults();
}

void SearchDialog::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        if(!searchFields.contains(Database::SearchFields::gradedate))
            searchFields.append(Database::SearchFields::gradedate);
    }
    ui->gradeDateStart->setEnabled(checked);
    ui->gradeDateEnd->setEnabled(checked);
}
