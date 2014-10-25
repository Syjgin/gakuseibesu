#include <QSqlDatabase>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (!QSqlDatabase::drivers().contains("QSQLITE"))
            QMessageBox::critical(this, "Unable to load database", "This demo needs the SQLITE driver");
    base = Database::GetInstance();
    RefreshProfileList();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete base;
}

void MainWindow::on_buttonAdd_clicked()
{
    auto profileDialog = new AddNewProfileDialog(this);
    profileDialog->setModal(true);
    profileDialog->SetPurpose(AddNewProfileDialog::Purpose::AddNewProfile);
    profileDialog->SetId(currentIndex+1);
    if(profileDialog->exec() == QDialog::Accepted)
    {
        auto profileToAdd = profileDialog->GetUpdatedProfile();
        base->AddProfile(profileToAdd);
        RefreshProfileList();
    }
    delete profileDialog;
}

void MainWindow::FillProfilesList(QList<Profile> profilesList, bool changeCurrentIndex)
{
    ui->listWidget->clear();
    int currentRow = 0;
    if(changeCurrentIndex)
        currentIndex = 0;
    foreach (Profile currentProfile, profilesList) {
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(currentProfile.Firstname+" "+currentProfile.Patronym+" "+currentProfile.Lastname);
        item->setData(Qt::UserRole, currentProfile.Id);
        ui->listWidget->insertItem(currentRow, item);
        currentRow++;
        if(changeCurrentIndex)
        {
            if(currentProfile.Id > currentIndex)
                currentIndex = currentProfile.Id;
        }
    }
}

void MainWindow::RefreshProfileList()
{
    auto profilesList = base->AllProfiles();
    FillProfilesList(profilesList, true);
}

void MainWindow::ShowEditDialog(int id)
{
    auto profileDialog = new AddNewProfileDialog(this);
    profileDialog->setModal(true);
    profileDialog->SetPurpose(AddNewProfileDialog::Purpose::EditProfile);
    Profile selectedProfile = base->GetUserById(id);
    profileDialog->LoadProfile(selectedProfile);
    if(profileDialog->exec() == QDialog::Accepted)
    {
        base->UpdateProfile(profileDialog->GetUpdatedProfile());
        RefreshProfileList();
    }
    delete profileDialog;
}

void MainWindow::on_buttonEdit_clicked()
{
    if(ui->listWidget->selectedItems().count() > 0)
    {
        int id = ui->listWidget->selectedItems()[0]->data(Qt::UserRole).toInt();
        ShowEditDialog(id);
    }
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    int id = index.data(Qt::UserRole).toInt();
    ShowEditDialog(id);
}

void MainWindow::on_buttonSearch_clicked()
{
    auto searchDialog = new SearchDialog(this);
    searchDialog->setModal(true);
    if(searchDialog->exec() == QDialog::Accepted)
    {
        auto profiles = searchDialog->GetSearchResults();
        FillProfilesList(profiles, false);
    }
    delete searchDialog;
}

void MainWindow::on_buttonClear_clicked()
{
    RefreshProfileList();
}

void MainWindow::on_buttonDelete_clicked()
{
    if(ui->listWidget->selectedItems().count() > 0)
    {
        int id = ui->listWidget->selectedItems()[0]->data(Qt::UserRole).toInt();
        base->DeleteProfile(id);
        ui->listWidget->removeItemWidget(ui->listWidget->selectedItems()[0]);
    }
}
