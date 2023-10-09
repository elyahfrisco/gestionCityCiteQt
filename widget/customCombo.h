#ifndef CUSTOMCOMBO_H
#define CUSTOMCOMBO_H

#include <QObject>
#include <QWidget>
#include <QComboBox>
#include "database/db.h"

class CustomCombo: public QComboBox
{
public:
    CustomCombo(QWidget* parent);
    void getItems(Db* database, QString table, QString column);
    void getChambre(Db *database, QString refbat, QString numchambre);
    void setupUI(QString table, QString column, Db *database);
    void setupUI(QString refbat, Db *database, QString numchambre);
};

#endif // CUSTOMCOMBO_H
