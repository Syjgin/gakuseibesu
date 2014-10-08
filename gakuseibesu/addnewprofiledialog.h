#ifndef ADDNEWPROFILEDIALOG_H
#define ADDNEWPROFILEDIALOG_H
#include "profile.h"
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
    void LoadProfile(Profile profile);
    Profile GetUpdatedProfile();
private slots:
    void on_buttonBox_accepted();

private:
    Profile profileToEdit;
    Ui::AddNewProfileDialog *ui;
};

#endif // ADDNEWPROFILEDIALOG_H
