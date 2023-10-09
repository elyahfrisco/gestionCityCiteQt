#ifndef ADDLOUER_H
#define ADDLOUER_H

#include <QDialog>
#include <QTableView>
#include <QMessageBox>
#include "cruds/louercrud.h"

namespace Ui {
class addLouer;
}

class addLouer : public QDialog
{
    Q_OBJECT

public:
    explicit addLouer(QWidget *parent = nullptr);
    ~addLouer();

    bool checkNumEt(QString numEt);
    bool checkRef(QString refBat);
    bool checkNumChambre(QString numchambre);
    bool checkDateDebLoc(QString dateDebLoc);
    bool checkDateFinLoc(QString dateFinLoc);


    bool isDateSup();
private slots:
    void on_OkButton_clicked();

    void on_CancelButton_clicked();

    void on_refBat_currentTextChanged(const QString &arg1);

private:
    Ui::addLouer *ui;
};

#endif // ADDLOUER_H
