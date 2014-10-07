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

    //for debug
    auto exampleProfile = Profile();
    exampleProfile.Firstname = "Иван";
    exampleProfile.Lastname = "Иванов";
    exampleProfile.Patronym = "Иванович";
    base->AddProfile(exampleProfile);
    //for debug

    auto profilesList = base->AllProfiles();
    int currentRow = 0;
    foreach (Profile currentProfile, profilesList) {
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(currentProfile.Firstname+" "+currentProfile.Patronym+" "+currentProfile.Lastname);
        ui->listWidget->insertItem(currentRow, item);
        currentRow++;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete base;
}
