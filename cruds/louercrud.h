#ifndef LOUERCRUD_H
#define LOUERCRUD_H

#include <QWidget>
#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QTableView>
#include <QMessageBox>

#include "database/db.h"
#include "tableDelegate/customDelegate.h"
#include "dialogs/addlouer.h"

namespace Ui {
class LouerCrud;
}

class LouerCrud : public QWidget
{
    Q_OBJECT

public:
    explicit LouerCrud(QWidget *parent = nullptr, Db* database = new Db());
    ~LouerCrud();
    void displayTable();
    void resetTable();
    void fillInputChange(QTableView* qv, QModelIndexList indexes);
    Db* getDb();
    bool addNewLocation(QString numEt, QString refBat, QString numchambre, QString dateDebLoc, QDate dateFinLoc);

    QStringList getIds();
    bool isDateSup();
private slots:

    void on_modifierButton_clicked();

    void on_supprimerButton_clicked();

    void on_ajoutButton_clicked();

    void on_searchInput_textEdited(const QString &arg1);

    void on_refBat_currentTextChanged(const QString &arg1);

private:
    Db* mydb;
    Ui::LouerCrud *ui;

    void on_row_selected(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif // LOUERCRUD_H
