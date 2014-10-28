#include <QSqlDatabase>
#include <QtWidgets/QMessageBox>
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

Grade MainWindow::GetLastGrade(int profileId)
{
    Grade lastGrade = Grade();
    auto grades = base->GetGradesByProfile(profileId);
    QDate minimalDate = QDate(1,1,1);
    foreach (Grade currentGrade, grades)
    {
        if(currentGrade.Date > minimalDate)
        {
            minimalDate = currentGrade.Date;
            lastGrade = currentGrade;
        }
    }
    return lastGrade;
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

void MainWindow::AddXlsData(QVariant data, int &currentColumn, int row, QXlsx::Format format, QXlsx::Document *fileToSave)
{
    fileToSave->write(row, currentColumn, data, format);
    currentColumn++;
}

void MainWindow::on_buttonExport_clicked()
{
    QString filter = "excel files(*.xlsx);;csv files (*.csv)";
    QString saveCaption = tr("Choose file to save database");
    auto *dialog = new QFileDialog(this, saveCaption, QString(), filter);
    QString defaultSuffix = ".xlsx";
    auto *saveDialog = new QFileDialog(this);
    saveDialog->setDefaultSuffix(defaultSuffix);
    QString fileName = saveDialog->getSaveFileName(this,
                                     saveCaption,
                                     QString(),
                                     filter);
    if(!fileName.endsWith(defaultSuffix))
    {
        fileName.append(defaultSuffix);
    }
    if(fileName.endsWith(".csv"))
    {
        QFile csvFile(fileName);

        if(!csvFile.open(QIODevice::WriteOnly | QIODevice::Text ))
            qDebug("error opening destination csv");
        else
        {
            QTextStream outTextStream(&csvFile);
            auto userList = base->GetInstance()->AllProfiles();
            outTextStream << tr("firstname, lastname, patronymic, birthday, document, address, telephone, sex, sensei, grade, gradedate");
            endl(outTextStream);
            const QString glueString = ", ";
            foreach(Profile currentProfile, userList)
            {
                QString sexString = currentProfile.Sex==0 ? tr("Man") : tr("Woman");
                auto lastGrade = GetLastGrade(currentProfile.Id);
                outTextStream << currentProfile.Firstname + glueString + currentProfile.Lastname + glueString + currentProfile.Patronym
                                 + glueString + currentProfile.Birthday.toString(Qt::ISODate) + glueString + currentProfile.Document + glueString
                                 + currentProfile.Addres + glueString + currentProfile.Telephone + glueString + sexString + glueString +
                                 currentProfile.Sensei + glueString + lastGrade.GradeString + glueString + lastGrade.Date.toString(Qt::ISODate);
                endl(outTextStream);
            }
            outTextStream.flush();
            csvFile.close();
        }
    }
    if(fileName.endsWith(".xlsx"))
    {
        QXlsx::Document fileToSave;
        int currentColumn = 1;
        QXlsx::Format format = QXlsx::Format();
        format.setFontBold(true);
        format.setHorizontalAlignment(QXlsx::Format::HorizontalAlignment::AlignHCenter);
        QXlsx::Format fieldFormat = QXlsx::Format();
        fieldFormat.setHorizontalAlignment(QXlsx::Format::HorizontalAlignment::AlignHCenter);
        fileToSave.setColumnWidth(currentColumn, 20);
        AddXlsData(tr("firstname"), currentColumn, 1, format, &fileToSave);
        fileToSave.setColumnWidth(currentColumn, 20);
        AddXlsData(tr("lastname"), currentColumn, 1, format, &fileToSave);
        fileToSave.setColumnWidth(currentColumn, 20);
        AddXlsData(tr("patronymic"), currentColumn, 1, format, &fileToSave);
        fileToSave.setColumnWidth(currentColumn, 15);
        AddXlsData(tr("birthday"), currentColumn, 1, format, &fileToSave);
        fileToSave.setColumnWidth(currentColumn, 20);
        AddXlsData(tr("document"), currentColumn, 1, format, &fileToSave);
        fileToSave.setColumnWidth(currentColumn, 20);
        AddXlsData(tr("address"), currentColumn, 1, format, &fileToSave);
        fileToSave.setColumnWidth(currentColumn, 20);
        AddXlsData(tr("telephone"), currentColumn, 1, format, &fileToSave);
        fileToSave.setColumnWidth(currentColumn, 10);
        AddXlsData(tr("sex"), currentColumn, 1, format, &fileToSave);
        fileToSave.setColumnWidth(currentColumn, 20);
        AddXlsData(tr("sensei"), currentColumn, 1, format, &fileToSave);
        fileToSave.setColumnWidth(currentColumn, 15);
        AddXlsData(tr("grade"), currentColumn, 1, format, &fileToSave);
        fileToSave.setColumnWidth(currentColumn, 15);
        AddXlsData(tr("grade date"), currentColumn, 1, format, &fileToSave);
        auto userList = base->GetInstance()->AllProfiles();
        int currentRow = 2;
        currentColumn = 1;
        foreach(Profile currentProfile, userList)
        {
            QString sexString = currentProfile.Sex==0 ? tr("Man") : tr("Woman");
            auto lastGrade = GetLastGrade(currentProfile.Id);
            AddXlsData(currentProfile.Firstname, currentColumn, currentRow, fieldFormat, &fileToSave);
            AddXlsData(currentProfile.Lastname, currentColumn, currentRow, fieldFormat, &fileToSave);
            AddXlsData(currentProfile.Patronym, currentColumn, currentRow, fieldFormat, &fileToSave);
            AddXlsData(currentProfile.Birthday, currentColumn, currentRow, fieldFormat, &fileToSave);
            AddXlsData(currentProfile.Document, currentColumn, currentRow, fieldFormat, &fileToSave);
            AddXlsData(currentProfile.Addres, currentColumn, currentRow, fieldFormat, &fileToSave);
            AddXlsData(currentProfile.Telephone, currentColumn, currentRow, fieldFormat, &fileToSave);
            AddXlsData(sexString, currentColumn, currentRow, fieldFormat, &fileToSave);
            AddXlsData(currentProfile.Sensei, currentColumn, currentRow, fieldFormat, &fileToSave);
            AddXlsData(lastGrade.GradeString, currentColumn, currentRow, fieldFormat, &fileToSave);
            AddXlsData(lastGrade.Date, currentColumn, currentRow, fieldFormat, &fileToSave);
            currentRow++;
            currentColumn = 1;
        }
        if(!fileToSave.saveAs(fileName))
            qDebug("failed to save xlsx");
    }
}

void MainWindow::on_actionAdd_new_profile_triggered()
{
    on_buttonAdd_clicked();
}

void MainWindow::on_actionSearch_triggered()
{
    on_buttonSearch_clicked();
}

void MainWindow::on_actionExport_triggered()
{
    on_buttonExport_clicked();
}

void MainWindow::on_action_About_program_triggered()
{
    QMessageBox::about(this, tr("About program"), tr("This program is developed by Syjgin aka Oleg Maximov and distributed under the GPLv3. For xls saving <a target=\"_blank\" href=\"http://qtxlsx.debao.me/\">QtXlsx</a> library was used."));
}

void MainWindow::on_action_About_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionDelete_DB_triggered()
{
    if(QMessageBox::question(this, tr("Confirmation"), tr("Are you sure to delete database? This action can't be cancelled!")) == QMessageBox::Yes)
    {
        Database::GetInstance()->RemoveDatabase();
        RefreshProfileList();
    }
}
