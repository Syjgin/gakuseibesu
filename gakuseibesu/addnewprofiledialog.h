#ifndef ADDNEWPROFILEDIALOG_H
#define ADDNEWPROFILEDIALOG_H
#include <QtWidgets/QDialog>
#include "editgrades.h"

namespace Ui {
class AddNewProfileDialog;
}

class AddNewProfileDialog : public QDialog
{
    Q_OBJECT

public:
    enum Purpose {
        AddNewProfile,
        EditProfile
    };

    explicit AddNewProfileDialog(QWidget *parent = 0);
    ~AddNewProfileDialog();
    void LoadProfile(Profile profile);
    Profile GetUpdatedProfile();
    void SetPurpose(Purpose purpose);
    void SetId(int id);
private slots:
    void on_buttonBox_accepted();

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_editGrades_clicked();

    void on_dateEdit_dateChanged(const QDate &date);

private:
    Profile profileToEdit;
    Ui::AddNewProfileDialog *ui;

    void UpdateAgeLabel(QDate date);
    void UpdateGradeLabel();
    const QString EditTitle = tr("Edit profile");
    const QString AddNewTitle = tr("Add new profile");
    const QString Age = tr("Age: ");
    const qint64 SecsInYear = 31556926;

};

#endif // ADDNEWPROFILEDIALOG_H
