#ifndef ADDNEWPROFILEDIALOG_H
#define ADDNEWPROFILEDIALOG_H

#include <QDialog>

namespace Ui {
class AddNewProfileDialog;
}

class AddNewProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewProfileDialog(QWidget *parent = 0);
    ~AddNewProfileDialog();

private:
    Ui::AddNewProfileDialog *ui;
};

#endif // ADDNEWPROFILEDIALOG_H
