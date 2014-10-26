#ifndef EDITGRADES_H
#define EDITGRADES_H

#include <QtWidgets/QDialog>
#include "database.h"
#include "addnewgrade.h"

namespace Ui {
class EditGrades;
}

class EditGrades : public QDialog
{
    Q_OBJECT

public:
    explicit EditGrades(int id, QWidget *parent = 0);
    ~EditGrades();
private slots:
    void on_deleteGrade_clicked();

    void on_editGrade_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_addNewGrade_clicked();

private:
    Ui::EditGrades *ui;
    void RefreshGrades();
    void StartEditGrade(int id);
    Database *db;
    int userId;
    static int lastIndex;
    QList<Grade> grades;
};

#endif // EDITGRADES_H
