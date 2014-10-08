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

    ui->listWidget->clear();
    auto profilesList = base->AllProfiles();
    int currentRow = 0;
    currentIndex = 0;
    foreach (Profile currentProfile, profilesList) {
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(currentProfile.Firstname+" "+currentProfile.Patronym+" "+currentProfile.Lastname);
        ui->listWidget->insertItem(currentRow, item);
        currentRow++;
        if(currentProfile.Id > currentIndex)
            currentIndex = currentProfile.Id;
    }
    currentIndex++;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete base;
}

void MainWindow::on_buttonAdd_clicked()
{
    AddNewProfileDialog *dialog = new AddNewProfileDialog(this);
    if(dialog->exec() == QDialog::Accepted)
    {
        auto profileToAdd = dialog->GetUpdatedProfile();
        profileToAdd.Id = currentIndex;
        base->AddProfile(profileToAdd);
        RefreshProfileList();
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
        ui->listWidget->insertItem(currentRow, item);
        currentRow++;
        if(currentProfile.Id > currentIndex)
            currentIndex = currentProfile.Id;
    }
    currentIndex++;
}
