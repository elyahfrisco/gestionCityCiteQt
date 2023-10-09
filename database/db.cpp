#include "db.h"
#include <QSqlError>
Db::Db()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QMYSQL");
    mydb.setHostName("localhost");
    mydb.setUserName("root");
    mydb.setPassword("");
    mydb.setPort(3306);
    mydb.setDatabaseName("citeuniv");
}

void Db::open(){
    if(!mydb.open()){
        qDebug() << "Error, not connected";
    } else {
        qDebug() << "connected";
    }
}

void Db::close(){
    mydb.close();
    qDebug() << "Closed";
}

QSqlDatabase Db::getDb(){
    return mydb;
}

void Db::update(QString table, QStringList columns, QStringList values, QStringList id, QStringList idVal)
{
    QSqlQuery qry;
    QString qryStr = "UPDATE " + table + " SET ";

    for(int i = 0; i< columns.length(); i++){
        qryStr += columns.at(i) + "='" + values.at(i) + "'";
        if(i+1 != columns.length()) qryStr += ", ";
    }

    qryStr += " WHERE ";

    for(int i = 0; i <id.length(); i++){
        qryStr += id.at(i) + "='" + idVal.at(i) + "'";
        if(i + 1 != id.length()) qryStr += " AND ";
    }

    qry.prepare(qryStr);

    if (!qry.exec()) {
        qDebug() << "Query execution failed!";
    } else {
        qDebug() << "Updated Successfully";
    }
}

void Db::del(QStringList tables, QStringList id, QStringList idVal)
{
    QSqlQuery qry;

    QString qryStr;

    foreach (QString table, tables) {
        qryStr = "DELETE FROM " + table + " WHERE ";
        for(int i = 0; i< id.length(); i++){
            qryStr += id.at(i) + "='" + idVal.at(i) + "'";
            if(i + 1 != id.length()) qryStr += " AND ";
        }

        qry.prepare(qryStr);

        if (!qry.exec()) {
            qDebug() << "Query execution failed!";
            return;
        }
    }

    qDebug() << "Deleted Successfully";
}

void Db::add(QString table, QStringList values)
{
    QSqlQuery qry;

    QString qryStr = "INSERT INTO " + table + " VALUES(";

    for (int i = 0; i < values.length(); i++) {
        qryStr += "'" + values.at(i) + "'";
        if(i+1 != values.length()) qryStr += ",";
    }

    qryStr += ")";
    qDebug()<<qryStr;

    qry.prepare(qryStr);

    if (!qry.exec()) {
        qDebug() << "Query execution failed!";
    } else {
        qDebug() << "Added Successfully";
    }
}

// etudiant
bool Db::numEtudiantExist(QString numEt){
    QSqlQuery qry;
    qry.prepare("SELECT numet FROM etudiant WHERE numEt=:numEt");

    qry.bindValue(":numEt", numEt);

    if (qry.exec() & qry.next()) {
        return true;
    }
    return false;
}

// batiment
bool Db::refBatExist(QString refBat)
{
    QSqlQuery qry;
    qry.prepare("SELECT refbat FROM batiment WHERE refbat=:refbat");

    qry.bindValue(":refbat", refBat);

    if (qry.exec() & qry.next()) {
        return true;
    }
    return false;
}

// calendrier
bool Db::dateDebLocExist(QDate dateDebLoc)
{
    QSqlQuery qry;
    qry.prepare("SELECT datedebutlocation FROM calendrier WHERE datedebutlocation=:datedebutlocation");

    qry.bindValue(":datedebutlocation", dateDebLoc);

    if (qry.exec() & qry.next()) {
        return true;
    }
    return false;
}

bool Db::chambreExist(QString refbat, QString numchambre)
{
    QSqlQuery qry;
    qry.prepare("SELECT numchambre FROM chambre WHERE refbat=:refbat AND numchambre=:numchambre");

    qry.bindValue(":refbat", refbat);
    qry.bindValue(":numchambre", numchambre);

    if (qry.exec() & qry.next()) {
        return true;
    }
    return false;
}

bool Db::locationExist(QString numEt, QString refBat, QString numChambre, QString dateDebutLoc)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM louer WHERE numet=:numet AND refbat=:refbat AND numchambre=:numchambre AND datedebutlocation=:datedebloc");

    qry.bindValue(":numet", numEt);
    qry.bindValue(":refbat", refBat);
    qry.bindValue(":numchambre", numChambre);
    qry.bindValue(":datedebloc", dateDebutLoc);

    if (qry.exec() & qry.next()) {
        return true;
    }
    return false;
}

QSqlQuery Db::getAll(QString table, QString column){
    QSqlQuery qry;
    QString query = "SELECT " + column + " FROM " + table + " ORDER BY " + column + " ASC";
    qry.prepare(query);

    if(!qry.exec()){
        qDebug() << "Query execution failed!";
    }

    return qry;
}

QSqlQuery Db::getChambre(QString bat){
    QSqlQuery qry;
    QString query = "SELECT numchambre FROM chambre WHERE refbat='" + bat + "' GROUP BY numchambre ORDER BY numchambre ASC";
    qry.prepare(query);

    if(!qry.exec()){
        qDebug() << "Query execution failed!";
    }

    return qry;
}

bool Db::VerifierDisponibiliteChambre(const QString& refBat, const QString& numChambre, const QDate& dateDebut)
{
    QSqlQuery qry;
    qry.prepare("SELECT COUNT(*) FROM louer WHERE REFBAT = :refBat AND NUMCHAMBRE = :numChambre "
                  "AND DATEDEBUTLOCATION <= :dateFin AND DATEFINLOCATION >= :dateDebut");
    qry.bindValue(":refBat", refBat);
    qry.bindValue(":numChambre", numChambre);
    qry.bindValue(":dateDebut", dateDebut);
    qry.bindValue(":dateFin", dateDebut); // Vous devrez ajuster la date de fin selon vos besoins

    if (qry.exec() && qry.next())
    {
        int count = qry.value(0).toInt();
        return (count == 0); // Si count est égal à zéro, la chambre est disponible
    }
    else
    {
        qDebug() << "Erreur lors de la vérification de la disponibilité de la chambre : " << qry.lastError();
        return false;
    }
}
