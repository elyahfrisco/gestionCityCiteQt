#ifndef CHAMBRECRUD_H
#define CHAMBRECRUD_H


#include <QWidget>
#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QTableView>
#include <QMessageBox>

#include "database/db.h"
#include "tableDelegate/customDelegate.h"
#include "dialogs/addchambre.h"

namespace Ui {
class ChambreCrud;
}

class ChambreCrud : public QWidget
{
    Q_OBJECT

public:
    explicit ChambreCrud(QWidget *parent = nullptr, Db* database = new Db());
    ~ChambreCrud();
    void displayTable();
    void resetTable();
    void fillInputChange(QTableView* qv, QModelIndexList indexes);
    Db* getDb();
    bool addNewChambre(QString refBat, QString numchambre, QString categorie);

private slots:

    void on_modifierButton_clicked();

    void on_supprimerButton_clicked();

    void on_ajoutButton_clicked();

    void on_searchInput_textEdited(const QString &arg1);

    void on_pushButton_clicked();

    void verifierDisponibiliteChambre();


    void on_verifierButton_clicked();

private:
    Db* mydb;
    Ui::ChambreCrud *ui;

    void on_row_selected(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif // CHAMBRECRUD_H
