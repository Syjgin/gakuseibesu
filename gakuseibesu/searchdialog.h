#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QtWidgets/QDialog>
#include "database.h"

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = 0);
    ~SearchDialog();
    QList<Profile> GetSearchResults();
private slots:

    void on_searchByAge_clicked(bool checked);

    void on_searchBySex_clicked(bool checked);

    void on_buttonBox_accepted();

    void on_checkBox_clicked(bool checked);

private:
    void CollectSearchResults();
    Ui::SearchDialog *ui;
    QList<Database::SearchFields> searchFields;
    QList<Profile> searchResults;
};

#endif // SEARCHDIALOG_H
