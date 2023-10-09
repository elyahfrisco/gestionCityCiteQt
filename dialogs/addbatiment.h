#ifndef ADDBATIMENT_H
#define ADDBATIMENT_H

#include <QDialog>
#include <QMessageBox>
#include <cruds/batimentcrud.h>


namespace Ui {
class addBatiment;
}

class addBatiment : public QDialog
{
    Q_OBJECT

public:
    explicit addBatiment(QWidget *parent = nullptr);
    ~addBatiment();

    bool checkRef(QString refBat);
private slots:
    void on_OkButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::addBatiment *ui;
};

#endif // ADDBATIMENT_H
