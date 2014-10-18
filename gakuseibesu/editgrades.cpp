#include "editgrades.h"
#include "ui_editgrades.h"

int EditGrades::lastIndex = 0;

EditGrades::EditGrades(int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditGrades)
{
    ui->setupUi(this);
    db = Database::GetInstance();
    userId = id;
    RefreshGrades();
    grades = QList<Grade>();
}

EditGrades::~EditGrades()
{
    delete ui;
}

void EditGrades::RefreshGrades()
{
    ui->listWidget->clear();
    grades = db->GetGradesByProfile(userId);
    int currentRow = 0;
    foreach (Grade currentGrade, grades)
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(currentGrade.GradeString);
        item->setData(Qt::UserRole, currentGrade.Id);
        ui->listWidget->insertItem(currentRow, item);
        currentRow++;
        if(currentGrade.Id > lastIndex)
            lastIndex = currentGrade.Id;
    }
}

void EditGrades::StartEditGrade(int id)
{
    Grade gradeToEdit = db->GetGradeById(id);
    auto editGradeDialog = new addNewGrade(this);
    editGradeDialog->setModal(true);
    editGradeDialog->SetGrade(gradeToEdit);
    if(editGradeDialog->exec() == QDialog::Accepted)
    {
        auto gradeToUpdate = editGradeDialog->GetUpdatedGrade();
        db->UpdateGrade(gradeToUpdate);
        RefreshGrades();
        delete editGradeDialog;
    }
}

void EditGrades::on_deleteGrade_clicked()
{
    if(ui->listWidget->selectedItems().count() > 0)
    {
        auto itemToDelete = ui->listWidget->selectedItems()[0];
        int idToDelete = itemToDelete->data(Qt::UserRole).toInt();
        db->DeleteGrade(idToDelete);
        RefreshGrades();
    }
}


void EditGrades::on_editGrade_clicked()
{
    if(ui->listWidget->selectedItems().count() > 0)
    {
        auto itemToUpdate = ui->listWidget->selectedItems()[0];
        int idToUpdate = itemToUpdate->data(Qt::UserRole).toInt();
        StartEditGrade(idToUpdate);
    }
}

void EditGrades::on_listWidget_doubleClicked(const QModelIndex &index)
{
    StartEditGrade(index.data(Qt::UserRole).toInt());
}

void EditGrades::on_addNewGrade_clicked()
{
    auto editGradeDialog = new addNewGrade(this);
    editGradeDialog->setModal(true);
    Grade gradeToEdit = Grade();
    gradeToEdit.Id = lastIndex+1;
    gradeToEdit.PeopleId = userId;
    editGradeDialog->SetGrade(gradeToEdit);
    if(editGradeDialog->exec() == QDialog::Accepted)
    {
        auto gradeToUpdate = editGradeDialog->GetUpdatedGrade();
        db->AddGrade(gradeToUpdate);
        RefreshGrades();
        delete editGradeDialog;
    }
}
