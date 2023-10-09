#ifndef ADDCHAMBRE_H
#define ADDCHAMBRE_H

#include <QDialog>
#include <QMessageBox>
#include <cruds/chambrecrud.h>

namespace Ui {
class addChambre;
}

class addChambre : public QDialog
{
    Q_OBJECT

public:
    explicit addChambre(QWidget *parent = nullptr);
    ~addChambre();

    bool checkRef(QString refBat);
    bool checkNum(QString numchambre);

    void getRefs();

private slots:
    void on_OkButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::addChambre *ui;
};

#endif // ADDCHAMBRE_H
