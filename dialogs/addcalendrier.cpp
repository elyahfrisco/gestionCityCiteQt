#include "addcalendrier.h"
#include "ui_addcalendrier.h"

AddCalendrier::AddCalendrier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCalendrier)
{
    ui->setupUi(this);

    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Ajouter Calendrier");
    this->setFixedSize(405,300);

}

AddCalendrier::~AddCalendrier()
{
    delete ui;
}

void AddCalendrier::on_OkButton_clicked()
{
    QDate dateDebLoc = ui->dateDebLoc->date();

    CalendrierCrud* parent = static_cast<CalendrierCrud*>(this->parent());
    if(parent->addNewCalendrier(dateDebLoc)){
        parent->resetTable();
        this->close();
    }

}


void AddCalendrier::on_CancelButton_clicked()
{
    this->close();
}


