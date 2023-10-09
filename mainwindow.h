#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include <QtSql>
#include<QSqlDatabase>
#include <QMessageBox>

#include "cruds/etudiantcrud.h"
#include "cruds/batimentcrud.h"
#include "cruds/calendriercrud.h"
#include "cruds/chambrecrud.h"
#include "cruds/louercrud.h"

#include "database/db.h"
#include "tableDelegate/customDelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionEtudiant_triggered();

    void on_actionBatiment_triggered();

    void on_actionCalendrier_triggered();

    void on_actionChambre_triggered();

    void on_actionLouer_triggered();

private:
    Db* mydb = new Db;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
