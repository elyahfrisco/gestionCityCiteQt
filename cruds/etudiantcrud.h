#ifndef ETUDIANTCRUD_H
#define ETUDIANTCRUD_H

#include <QWidget>
#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QTableView>
#include <QMessageBox>

#include "database/db.h"
#include "tableDelegate/customDelegate.h"


namespace Ui {
class CrudEtudiant;
}

class EtudiantCrud : public QWidget
{
    Q_OBJECT

public:
    explicit EtudiantCrud(QWidget *parent = nullptr, Db* database=new Db());
    ~EtudiantCrud();
    void displayTable();
    void resetTable();
    void fillInputChange(QTableView* qv, QModelIndexList indexes);
    bool addNewEtudiant(QString numEt, QString nomEt, QString prenomEt, QString numTel);

private slots:

    void on_modifierButton_clicked();

    void on_supprimerButton_clicked();

    void on_ajoutButton_clicked();

    void on_searchInput_textEdited(const QString &arg1);

private:
    Db* mydb;
    Ui::CrudEtudiant *ui;

    void on_row_selected(const QItemSelection &selected, const QItemSelection &deselected);


};

#endif // ETUDIANTCRUD_H
