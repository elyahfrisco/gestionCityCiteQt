#include "customCombo.h"

CustomCombo::CustomCombo(QWidget *parent)
    :QComboBox(parent)
{
}

void CustomCombo::getItems(Db* database, QString table, QString column)
{
    QSqlQuery qry = database->getAll(table, column);
    while(qry.next()){
        this->addItem(qry.value(0).toString(), qry.value(0).toString());
    }
}

void CustomCombo::getChambre(Db* database, QString refbat, QString numChambre){
    QSqlQuery qry = database->getChambre(refbat);
    this->clear();
    while(qry.next()){
        this->addItem(qry.value(0).toString(), qry.value(0).toString());
    }
    if(numChambre != ""){
        this->setCurrentText(numChambre);
    } else {
        this->setCurrentIndex(0);
    }
}

void CustomCombo::setupUI(QString table, QString column, Db* database){
    getItems(database, table, column);
}

void CustomCombo::setupUI(QString refbat, Db* database, QString numchambre){
    getChambre(database, refbat, numchambre);
}
