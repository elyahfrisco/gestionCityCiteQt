#include "addchambre.h"
#include "ui_addchambre.h"

addChambre::addChambre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addChambre)
{
    ui->setupUi(this);

    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("Ajouter Chambre");
    this->setFixedSize(405,300);

    ui->numChambre->setupUI("^\\d{3}$", "Le numero de chambre doit etre de la forme 000");
    getRefs();
}

addChambre::~addChambre()
{
    delete ui;
}

bool addChambre::checkRef(QString refBat){
    if(refBat == ""){
        QMessageBox::critical(this, "Référence de batiment vide", "La référence du batiment ne doit pas être vide");
        return false;
    }
    return true;
}

bool addChambre::checkNum(QString numchambre){
    QRegularExpression* reg = new QRegularExpression("^\\d{3}$");
    QRegularExpressionMatch match = reg->match(numchambre);
    if(!match.hasMatch()){
        QMessageBox::critical(this, "Erreur de numéro de chambre", "Le numéro de chambre doit être de la forme 000");
        return false;
    }
    return true;
}

void addChambre::getRefs()
{
    ChambreCrud* parent = static_cast<ChambreCrud*>(this->parent());
    QSqlQuery qry = parent->getDb()->getAll("batiment", "refbat");
    while (qry.next()) {
        QString refbat = qry.value(0).toString();
        ui->refBat->addItem(refbat, refbat);
    }
    ui->refBat->setCurrentIndex(-1);
}

void addChambre::on_OkButton_clicked()
{
    QString refBat = ui->refBat->currentText();
    QString numchambre, category;
    numchambre = ui->numChambre->text();
    category = ui->categorie->text();

    if(checkRef(refBat)) {

        if(checkNum(numchambre)){

            ChambreCrud* parent = static_cast<ChambreCrud*>(this->parent());
            if(parent->addNewChambre(refBat, numchambre, category)){
                parent->resetTable();
                this->close();
            }

        }
    }
}


void addChambre::on_CancelButton_clicked()
{
    this->close();
}

