#include "chambrecrud.h"
#include "ui_chambrecrud.h"

ChambreCrud::ChambreCrud(QWidget *parent, Db* database) :
    QWidget(parent),
    ui(new Ui::ChambreCrud)
{
    ui->setupUi(this);

    this->mydb = database;

    displayTable();

    ui->modifierBox->hide();

    connect(ui->verifierButton, &QPushButton::clicked, this, &ChambreCrud::verifierDisponibiliteChambre);

}

ChambreCrud::~ChambreCrud()
{
    delete ui;
}

void ChambreCrud::displayTable(){
    QSqlRelationalTableModel* model = new QSqlRelationalTableModel();

    model->setTable("chambre");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Réference Batiment"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numéro de chambre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Catégorie"));

    model->sort(0, Qt::AscendingOrder);
    model->sort(1, Qt::AscendingOrder);
    model->select();

    ui->tableChambre->setItemDelegate(new QSqlRelationalDelegate(ui->tableChambre));

    ui->tableChambre->setModel(model);


    ui->tableChambre->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableChambre->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->tableChambre->selectionModel(), &QItemSelectionModel::selectionChanged, this, &ChambreCrud::on_row_selected);
}

void ChambreCrud::resetTable(){
    QSqlRelationalTableModel* model = static_cast<QSqlRelationalTableModel*>(ui->tableChambre->model());
    model->select();
    ui->tableChambre->repaint();
    ui->modifierBox->hide();
}

void ChambreCrud::fillInputChange(QTableView* qv, QModelIndexList indexes){
    ui->RefBat->setText(qv->model()->data(indexes.at(0)).toString());
    ui->NumChambre->setText(qv->model()->data(indexes.at(1)).toString());
    ui->Categorie->setText(qv->model()->data(indexes.at(2)).toString());
}

bool ChambreCrud::addNewChambre(QString refBat, QString numchambre, QString categorie){
    if(!mydb->chambreExist(refBat, numchambre)){
        mydb->add("chambre", {refBat, numchambre, categorie});
        return true;
    }
    QMessageBox::critical(this, "Erreur de doublon", "La chambre existe déjà\nVeuillez entrez un nouveau");
    return false;
}

Db *ChambreCrud::getDb()
{
    return mydb;
}


// slots

void ChambreCrud::on_row_selected(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);
    QTableView* qv = ui->tableChambre;
    if(!selected.indexes().isEmpty())
    {
        fillInputChange(qv, selected.indexes());
        ui->modifierBox->show();
    } else {
        ui->modifierBox->hide();
    }
}


void ChambreCrud::on_modifierButton_clicked()
{
    QString refBat, numChambre, categorie;
    refBat = ui->RefBat->text();
    numChambre = ui->NumChambre->text();
    categorie = ui->Categorie->text();

    mydb->update("chambre", {"categorie"}, {categorie}, {"refbat", "numchambre"}, {refBat, numChambre});

    resetTable();
}

void ChambreCrud::on_supprimerButton_clicked()
{
    QModelIndex ind = ui->tableChambre->selectionModel()->currentIndex();
    ind = ui->tableChambre->model()->index(ind.row(), 0);
    QString refBat, numChambre;
    refBat = ui->tableChambre->model()->data(ind).toString();
    ind = ui->tableChambre->model()->index(ind.row(), 1);
    numChambre = ui->tableChambre->model()->data(ind).toString();

    mydb->del({"louer", "chambre"}, {"refbat", "numchambre"}, {refBat, numChambre});

    resetTable();
    ui->modifierBox->hide();
}


void ChambreCrud::on_ajoutButton_clicked()
{
    addChambre* addchambre = new addChambre(this);
    addchambre->show();
}


void ChambreCrud::on_searchInput_textEdited(const QString &arg1)
{
    QSqlRelationalTableModel* model = static_cast<QSqlRelationalTableModel*>(ui->tableChambre->model());
    if(arg1 != ""){
        QString arg = arg1.toLower();
        QString filter = "LOWER(refbat) LIKE '%" + arg + "%' OR LOWER(numchambre) LIKE '%" + arg + "%' OR LOWER(categorie) LIKE '%" + arg + "%'";

        model->setFilter(filter);
        model->select();
    } else {
        model->setFilter("");
        model->select();
    }

}



void ChambreCrud::on_pushButton_clicked()
{

}

void ChambreCrud::verifierDisponibiliteChambre()
{

    QString refBat = ui->RefBat->text();
    QString numChambre = ui->NumChambre->text();


    QString query = "SELECT chambre.REFBAT, chambre.NUMCHAMBRE FROM chambre "
                    "LEFT JOIN louer ON chambre.REFBAT = louer.REFBAT AND chambre.NUMCHAMBRE = louer.NUMCHAMBRE "
                    "WHERE louer.NUMET IS NULL "
                    "AND chambre.REFBAT = :refBat "
                    "AND chambre.NUMCHAMBRE = :numChambre";

    QSqlQuery qry;
    qry.prepare(query);
    qry.bindValue(":refBat", refBat);
    qry.bindValue(":numChambre", numChambre);


    if (qry.exec() && qry.next())
    {

        ui->resultatLabel->setText("La chambre est disponible.");
    }
    else
    {

        ui->resultatLabel->setText("La chambre n'est pas disponible.");
    }
}



