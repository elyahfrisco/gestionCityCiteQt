#include "addetudiant.h"
#include "ui_addetudiant.h"

addEtudiant::addEtudiant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addEtudiant)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Ajouter Etudiant");
    this->setFixedSize(405,300);

    ui->numEtInput->setupUI("^E\\d{4}$", "Le numéro étudiant doit être de la forme E0000");
    ui->numTelInput->setupUI("^(032|033|034|038)\\d{7}$", "Le numero de téléphone doit être de la forme\n03XXXXXXXX");
}

addEtudiant::~addEtudiant()
{
    delete ui;
}


bool addEtudiant::checkNumEt(QString numEt){
    QRegularExpression* regex = new QRegularExpression("^E\\d{4}$");
    QRegularExpressionMatch match = regex->match(numEt);

    if(match.hasMatch()){
        return true;
    }
    QMessageBox::critical(this, "Erreur sur le numéro de l'étudiant", "Le numéro de l'étudiant doit être de la forme E0000");
    return false;
}

bool addEtudiant::checkNumTel(QString numTel){
    QRegularExpression* regex = new QRegularExpression("^(032|033|034|038)\\d{7}$");
    QRegularExpressionMatch match = regex->match(numTel);

    if(match.hasMatch()){
        return true;
    }
    QMessageBox::critical(this, "Erreur sur le numéro de téléphone", "Le numéro de téléphone doit être de la forme 03XXXXXXXX");
    return false;
}

bool addEtudiant::checkNom(QString nomEt){
    if(nomEt=="") {
        QMessageBox::critical(this, "Erreur de nom", "L'étudiant doit avoir au moins un nom");
        return false;
    }
    return true;
}


//slots
void addEtudiant::on_OkButton_clicked()
{
    QString numEt, nomEt, prenomEt, numTel;
    numEt = ui->numEtInput->text();
    nomEt = ui->nomEtInput->text();
    prenomEt = ui->prenomEtInput->text();
    numTel = ui->numTelInput->text();


    if(checkNumEt(numEt)){

        if(checkNom(nomEt)){

            if(checkNumTel(numTel)){

                EtudiantCrud* parent = static_cast<EtudiantCrud*>(this->parent());
                if(parent->addNewEtudiant(numEt, nomEt, prenomEt, numTel)){
                    parent->resetTable();
                    this->close();
                }
            }

        }
    }

}


void addEtudiant::on_CancelButton_clicked()
{
    this->close();
}

