#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "addnewprofiledialog.h"

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

private:
    Ui::MainWindow *ui;
    Database *base;
    int currentIndex;
    void RefreshProfileList();
    AddNewProfileDialog *profileDialog;
};

#endif // MAINWINDOW_H
