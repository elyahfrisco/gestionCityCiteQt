#ifndef ADDCALENDRIER_H
#define ADDCALENDRIER_H

#include <QDialog>
#include <QMessageBox>
#include <cruds/calendriercrud.h>

namespace Ui {
class AddCalendrier;
}

class AddCalendrier : public QDialog
{
    Q_OBJECT

public:
    explicit AddCalendrier(QWidget *parent = nullptr);
    ~AddCalendrier();

private slots:
    void on_OkButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::AddCalendrier *ui;
};

#endif // ADDCALENDRIER_H
