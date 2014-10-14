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
    base = new Database();
    RefreshProfileList();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete base;
}

void MainWindow::on_buttonAdd_clicked()
{
    profileDialog = new AddNewProfileDialog(this);
    profileDialog->setModal(true);
    profileDialog->SetPurpose(AddNewProfileDialog::Purpose::AddNewProfile);
    if(profileDialog->exec() == QDialog::Accepted)
    {
        auto profileToAdd = profileDialog->GetUpdatedProfile();
        profileToAdd.Id = currentIndex;
        base->AddProfile(profileToAdd);
        RefreshProfileList();
        profileDialog->~AddNewProfileDialog();
    }
}

void MainWindow::RefreshProfileList()
{
    ui->listWidget->clear();
    auto profilesList = base->AllProfiles();
    int currentRow = 0;
    currentIndex = 0;
    foreach (Profile currentProfile, profilesList) {
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(currentProfile.Firstname+" "+currentProfile.Patronym+" "+currentProfile.Lastname);
        item->setData(Qt::UserRole, currentProfile.Id);
        ui->listWidget->insertItem(currentRow, item);
        currentRow++;
        if(currentProfile.Id > currentIndex)
            currentIndex = currentProfile.Id;
    }
    currentIndex++;
}

void MainWindow::on_buttonEdit_clicked()
{
    if(ui->listWidget->selectedItems().count() > 0)
    {
        profileDialog = new AddNewProfileDialog(this);
        profileDialog->setModal(true);
        profileDialog->SetPurpose(AddNewProfileDialog::Purpose::EditProfile);
        int id = ui->listWidget->selectedItems()[0]->data(Qt::UserRole).toInt();
        Profile selectedProfile = base->GetUserById(id);
        profileDialog->LoadProfile(selectedProfile);
        if(profileDialog->exec() == QDialog::Accepted)
        {
            base->UpdateProfile(profileDialog->GetUpdatedProfile());
            RefreshProfileList();
            profileDialog->~AddNewProfileDialog();
        }
    }
}
