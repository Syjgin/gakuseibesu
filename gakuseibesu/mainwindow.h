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

    void ShowEditDialog(int id);
private slots:
    void on_buttonAdd_clicked();

    void on_buttonEdit_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Database *base;
    int currentIndex;
    void RefreshProfileList();
};

#endif // MAINWINDOW_H
