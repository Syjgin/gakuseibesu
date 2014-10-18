#ifndef ADDNEWGRADE_H
#define ADDNEWGRADE_H

#include <QDialog>
#include "grade.h"

namespace Ui {
class addNewGrade;
}

class addNewGrade : public QDialog
{
    Q_OBJECT

public:
    explicit addNewGrade(QWidget *parent = 0);
    ~addNewGrade();
    void SetGrade(Grade grade);
    Grade GetUpdatedGrade();
private:
    Ui::addNewGrade *ui;
    Grade gradeToEdit;
};

#endif // ADDNEWGRADE_H
