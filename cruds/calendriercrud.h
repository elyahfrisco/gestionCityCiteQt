#ifndef CALENDRIERCRUD_H
#define CALENDRIERCRUD_H


#include <QWidget>
#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QTableView>
#include <QMessageBox>

#include "database/db.h"
#include "tableDelegate/customDelegate.h"
#include "dialogs/addcalendrier.h"

namespace Ui {
class CalendrierCrud;
}

class CalendrierCrud : public QWidget
{
    Q_OBJECT

public:
    explicit CalendrierCrud(QWidget *parent = nullptr, Db* database = new Db());
    ~CalendrierCrud();

    void displayTable();
    void resetTable();
    void fillInputChange(QTableView *qv, QModelIndexList indexes);
    bool addNewCalendrier(QDate dateDebLoc);

private slots:
//    void on_modifierButton_clicked();
    void on_supprimerButton_clicked();
    void on_ajoutButton_clicked();
    void on_resetButton_clicked();

    void on_searchButton_clicked();

private:
    Ui::CalendrierCrud *ui;
    Db *mydb;

    void on_row_selected(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif // CALENDRIERCRUD_H
