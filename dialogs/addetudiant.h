#ifndef ADDETUDIANT_H
#define ADDETUDIANT_H

#include <QDialog>
#include <QTableView>
#include <QMessageBox>
#include "cruds/etudiantcrud.h"

namespace Ui {
class addEtudiant;
}

class addEtudiant : public QDialog
{
    Q_OBJECT

public:
    explicit addEtudiant(QWidget *parent = nullptr);
    ~addEtudiant();

private slots:
    void on_OkButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::addEtudiant *ui;
    bool checkNumEt(QString numEt);
    bool checkNumTel(QString numTel);
    bool checkNom(QString nomEt);
};

#endif // ADDETUDIANT_H
