#include "addbatiment.h"
#include "ui_addbatiment.h"

addBatiment::addBatiment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addBatiment)
{
    ui->setupUi(this);

    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Ajouter Batiment");
    this->setFixedSize(405,300);

    ui->refBat->setupUI("^.{1,11}$", "La reference du batiment ne peut pas avoir plus de caractères");
}

addBatiment::~addBatiment()
{
    delete ui;
}

bool addBatiment::checkRef(QString refBat){
    if(refBat == ""){
        QMessageBox::critical(this, "Référence de batiment vide", "La référence du batiment ne doit pas être vide");
        return false;
    }
    return true;
}

void addBatiment::on_OkButton_clicked()
{
    QString refBat = ui->refBat->text();
    int location = ui->location->value();

    if(checkRef(refBat)) {

        BatimentCrud* parent = static_cast<BatimentCrud*>(this->parent());
        if(parent->addNewBatiment(refBat, location)){
            parent->resetTable();
            this->close();
        }

    }
}


void addBatiment::on_CancelButton_clicked()
{
    this->close();
}

