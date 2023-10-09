#include "louercrud.h"
#include "ui_louercrud.h"

LouerCrud::LouerCrud(QWidget *parent, Db* database) :
    QWidget(parent),
    ui(new Ui::LouerCrud)
{
    ui->setupUi(this);

    this->mydb = database;

    displayTable();

    ui->modifierBox->hide();

    ui->numEt->setupUI("etudiant", "numet", mydb);
    ui->refBat->setupUI("batiment", "refbat", mydb);
    ui->dateDebLoc->setupUI("calendrier", "datedebutlocation", mydb);
}

LouerCrud::~LouerCrud()
{
    delete ui;
}

void LouerCrud::displayTable(){
    QSqlRelationalTableModel* model = new QSqlRelationalTableModel();

    model->setTable("louer");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Numéro Etudiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Référence Batiment"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Numéro chambre"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Debut Location"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date Fin Location"));



    model->select();

    ui->tableLouer->setItemDelegate(new QSqlRelationalDelegate(ui->tableLouer));


    ui->tableLouer->setModel(model);

    ui->tableLouer->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableLouer->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->tableLouer->selectionModel(), &QItemSelectionModel::selectionChanged, this, &LouerCrud::on_row_selected);

}

void LouerCrud::resetTable(){
    QSqlRelationalTableModel* model = static_cast<QSqlRelationalTableModel*>(ui->tableLouer->model());
    model->select();
    ui->tableLouer->repaint();
    ui->modifierBox->hide();
}

void LouerCrud::fillInputChange(QTableView* qv, QModelIndexList indexes){
    ui->numEt->setCurrentText(qv->model()->data(indexes.at(0)).toString());
    ui->refBat->setCurrentText(qv->model()->data(indexes.at(1)).toString());
    ui->numChambre->setCurrentText(qv->model()->data(indexes.at(2)).toString());
    ui->dateDebLoc->setCurrentText(qv->model()->data(indexes.at(3)).toString());
    ui->dateFinLoc->setDate(qv->model()->data(indexes.at(4)).toDate());
}

bool LouerCrud::addNewLocation(QString numEt, QString refBat, QString numChambre, QString dateDebLocation, QDate dateFinLocation){
    if(!mydb->locationExist(numEt, refBat, numChambre, dateDebLocation)){

        mydb->add("louer" ,{numEt, refBat, numChambre, dateDebLocation, dateFinLocation.toString("yyyy-MM-dd")});
        return true;
    } else {
        QMessageBox::critical(this, "Erreur de doublon", "La location existe déjà\nVeuillez entrez un nouveau");
        return false;
    }
}

QStringList LouerCrud::getIds(){
    QModelIndex ind = ui->tableLouer->selectionModel()->currentIndex();
    QStringList idVals;
    for(int i = 0; i<  ui->tableLouer->model()->columnCount() - 1; ++i){
        ind = ui->tableLouer->model()->index(ind.row(), i);
        idVals.append(ui->tableLouer->model()->data(ind).toString());
    }
    return idVals;
}

Db* LouerCrud::getDb(){
    return mydb;
}

bool LouerCrud::isDateSup(){
    QDate datefin = ui->dateFinLoc->date();
    QDate datedeb = QDate::fromString(ui->dateDebLoc->currentText(), "yyyy-MM-dd");
    qDebug() << datedeb;
    if(datefin >= datedeb) {
        qDebug() << datedeb;
        return true;
    }
    QMessageBox::critical(this, "La date de debut est plus recent que la date de fin", "La date de debut est plus recent que la date de fin\nVeuillez reesayer");
    return false;
}

// slots

void LouerCrud::on_row_selected(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);
    QTableView* qv = ui->tableLouer;
    if(!selected.indexes().isEmpty())
    {
        fillInputChange(qv, selected.indexes());
        ui->modifierBox->show();
        ui->numChambre->setupUI(ui->refBat->currentText(), mydb, ui->tableLouer->model()->data(selected.indexes().at(2)).toString());
    } else {
        ui->modifierBox->hide();
    }
}


void LouerCrud::on_modifierButton_clicked()
{
    QString numEt, refBat, numChambre, dateDebLoc;
    QDate dateFinLoc = ui->dateFinLoc->date();

    numEt = ui->numEt->currentText();
    refBat = ui->refBat->currentText();
    numChambre = ui->numChambre->currentText();
    dateDebLoc = ui->dateDebLoc->currentText();
        if(isDateSup()){
            QStringList columns = {"numet", "refbat", "numchambre", "datedebutlocation", "datefinlocation"};
            QStringList values = {numEt, refBat, numChambre, dateDebLoc, dateFinLoc.toString("yyyy-MM-dd")};
            QStringList ids = {"numet", "refbat", "numchambre", "datedebutlocation"};

            QStringList idVals = getIds();

            mydb->update("louer", columns, values, ids, idVals);

            resetTable();
        }

}

void LouerCrud::on_supprimerButton_clicked()
{
    QStringList idVals = getIds();

    mydb->del({"louer"}, {"numet", "refbat", "numchambre", "datedebutlocation"}, idVals);
    resetTable();
    ui->modifierBox->hide();
}


void LouerCrud::on_ajoutButton_clicked()
{
    addLouer* addlouer = new addLouer(this);
    addlouer->show();
}


void LouerCrud::on_searchInput_textEdited(const QString &arg1)
{
    QSqlRelationalTableModel* model = static_cast<QSqlRelationalTableModel*>(ui->tableLouer->model());
    if(arg1 != ""){
        QString arg = arg1.toLower();
        QString filter = "LOWER(numet) LIKE '%" + arg + "%' OR LOWER(refbat) LIKE '%" + arg + "%' OR LOWER(numchambre) LIKE '%" + arg + "%'";
        model->setFilter(filter);
        model->select();
    } else {
        model->setFilter("");
        model->select();
    }

}

void LouerCrud::on_refBat_currentTextChanged(const QString &arg1)
{
    ui->numChambre->setupUI(arg1, mydb, "");
}

