#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
#include <QFile>
#include <QtXlsx>
#include "database.h"
#include "addnewprofiledialog.h"
#include "searchdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_buttonAdd_clicked();

    void on_buttonEdit_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_buttonSearch_clicked();

    void on_buttonClear_clicked();

    void on_buttonDelete_clicked();

    void on_buttonExport_clicked();

    void on_actionAdd_new_profile_triggered();

    void on_actionSearch_triggered();

    void on_actionExport_triggered();

    void on_action_About_program_triggered();

    void on_action_About_Qt_triggered();

    void on_actionDelete_DB_triggered();

private:
    Ui::MainWindow *ui;
    Database *base;
    int currentIndex;
    void RefreshProfileList();
    void AddXlsData(QVariant data, int &currentColumn, int row, QXlsx::Format format, QXlsx::Document *fileToSave);
    void ShowEditDialog(int id);
    void FillProfilesList(QList<Profile> profilesList, bool changeCurrentIndex);
    Grade GetLastGrade(int profileId);
};

#endif // MAINWINDOW_H
