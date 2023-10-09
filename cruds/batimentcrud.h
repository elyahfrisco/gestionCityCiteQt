#ifndef BATIMENTCRUD_H
#define BATIMENTCRUD_H

#include <QWidget>
#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QTableView>
#include <QMessageBox>

#include "database/db.h"
#include "tableDelegate/customDelegate.h"
#include "dialogs/addbatiment.h"

namespace Ui {
class BatimentCrud;
}

class BatimentCrud : public QWidget
{
    Q_OBJECT

public:
    explicit BatimentCrud(QWidget *parent = nullptr, Db* database = new Db());
    ~BatimentCrud();
    void displayTable();
    void resetTable();
    void fillInputChange(QTableView* qv, QModelIndexList indexes);
    bool addNewBatiment(QString refBat, int nbLocation);

private slots:

    void on_modifierButton_clicked();

    void on_supprimerButton_clicked();

    void on_ajoutButton_clicked();

    void on_searchInput_textEdited(const QString &arg1);

private:
    Db* mydb;
    Ui::BatimentCrud *ui;

    void on_row_selected(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif // BATIMENTCRUD_H
