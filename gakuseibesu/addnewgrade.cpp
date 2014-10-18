#include "addnewgrade.h"
#include "ui_addnewgrade.h"

addNewGrade::addNewGrade(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewGrade)
{
    ui->setupUi(this);
    gradeToEdit = Grade();
    gradeToEdit.Id = 0;
    ui->dateEdit->setDate(QDate::currentDate());
}

addNewGrade::~addNewGrade()
{
    delete ui;
}

void addNewGrade::SetGrade(Grade grade)
{
    gradeToEdit = grade;
    ui->grade->setText(gradeToEdit.GradeString);
    ui->dateEdit->setDate(gradeToEdit.Date);
}

Grade addNewGrade::GetUpdatedGrade()
{
    gradeToEdit.Date = ui->dateEdit->date();
    gradeToEdit.GradeString = ui->grade->text();
    return gradeToEdit;
}
