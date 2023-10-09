#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mydb->open();

}

MainWindow::~MainWindow()
{
    delete ui;
    mydb->close();
}





void MainWindow::on_actionBatiment_triggered()
{
    BatimentCrud* crudBat = new BatimentCrud(this, mydb);
    this->setCentralWidget(crudBat);
}


void MainWindow::on_actionCalendrier_triggered()
{
    CalendrierCrud* crudCalendrier = new CalendrierCrud(this, mydb);
    this->setCentralWidget(crudCalendrier);
}


void MainWindow::on_actionChambre_triggered()
{
    ChambreCrud* crudChambre = new ChambreCrud(this, mydb);
    this->setCentralWidget(crudChambre);
}

void MainWindow::on_actionEtudiant_triggered()
{
    EtudiantCrud* crudEt = new EtudiantCrud(this, mydb);
    this->setCentralWidget(crudEt);
}

void MainWindow::on_actionLouer_triggered()
{
    LouerCrud* crudLouer = new LouerCrud(this, mydb);
    this->setCentralWidget(crudLouer);
}

