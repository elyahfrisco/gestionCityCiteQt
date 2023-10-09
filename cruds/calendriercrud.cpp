#include "calendriercrud.h"
#include "ui_calendriercrud.h"

CalendrierCrud::CalendrierCrud(QWidget *parent, Db* database) :
    QWidget(parent),
    ui(new Ui::CalendrierCrud)
{
    ui->setupUi(this);

    this->mydb = database;

    displayTable();

    ui->modifierBox->hide();

}

CalendrierCrud::~CalendrierCrud()
{
    delete ui;
}

void CalendrierCrud::displayTable(){
    QSqlRelationalTableModel* model = new QSqlRelationalTableModel();

    model->setTable("calendrier");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Date de Début de Location"));

    model->sort(0, Qt::AscendingOrder);
    model->select();


    ui->tableCalendrier->setModel(model);


    ui->tableCalendrier->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableCalendrier->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->tableCalendrier->selectionModel(), &QItemSelectionModel::selectionChanged, this, &CalendrierCrud::on_row_selected);
}

void CalendrierCrud::resetTable(){
    QSqlRelationalTableModel* model = static_cast<QSqlRelationalTableModel*>(ui->tableCalendrier->model());
    model->select();
    ui->tableCalendrier->repaint();
    ui->modifierBox->hide();
}

void CalendrierCrud::fillInputChange(QTableView* qv, QModelIndexList indexes){
    ui->dateDebLoc->setDate(qv->model()->data(indexes.at(0)).toDate());
}

bool CalendrierCrud::addNewCalendrier(QDate dateDebLoc){
    if(!mydb->dateDebLocExist(dateDebLoc)){
        mydb->add("calendrier", {dateDebLoc.toString("yyyy-MM-dd")});
        return true;
    }
    QMessageBox::critical(this, "Erreur de doublon", "La date existe déjà\nVeuillez entrez un nouveau");
    return false;
}


// slots
void CalendrierCrud::on_row_selected(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);
    QTableView* qv = ui->tableCalendrier;
    if(!selected.indexes().isEmpty())
    {
        fillInputChange(qv, selected.indexes());
        ui->modifierBox->show();
    } else {
        ui->modifierBox->hide();
    }
}


//void CalendrierCrud::on_modifierButton_clicked()
//{
//    QDate dateDebLoc = ui->dateDebLoc->date();

//    mydb->update("calendrier", {"datedebutlocation"}, {dateDebLoc.toString()}, {"datedebutlocation"}, {dateDebLoc.toString()});

//    resetTable();
//}

void CalendrierCrud::on_supprimerButton_clicked()
{
    QModelIndex ind = ui->tableCalendrier->selectionModel()->currentIndex();
    ind = ui->tableCalendrier->model()->index(ind.row(), 0);
    QString DateDebLoc = ui->tableCalendrier->model()->data(ind).toString();

    mydb->del({"louer", "calendrier"}, {"datedebutlocation"}, {DateDebLoc});

    resetTable();
    ui->modifierBox->hide();
}


void CalendrierCrud::on_ajoutButton_clicked()
{
    AddCalendrier* addcal = new AddCalendrier(this);
    addcal->show();
}

void CalendrierCrud::on_resetButton_clicked()
{
    ui->DateSearchDeb->setDate(QDate(2000, 1, 1));
    ui->dateSearchFin->setDate(QDate(2000, 1, 1));

    ui->modifierBox->hide();

    QSqlRelationalTableModel* model = static_cast<QSqlRelationalTableModel*>(ui->tableCalendrier->model());
    model->setFilter("");
    model->select();
}


void CalendrierCrud::on_searchButton_clicked()
{
    ui->modifierBox->hide();

    QSqlRelationalTableModel* model = static_cast<QSqlRelationalTableModel*>(ui->tableCalendrier->model());
    QDate dateDeb, dateFin;
    dateDeb = ui->DateSearchDeb->date();
    dateFin = ui->dateSearchFin->date();

    QString filter;

    if(dateDeb >= dateFin) {
        filter = "datedebutlocation >= '"+ dateFin.toString() + "' AND datedebutlocation <= '" + dateDeb.toString() + "'";
    } else {
        filter = "datedebutlocation >= '" + dateDeb.toString() + "' AND datedebutlocation <= '" + dateFin.toString() + "'";
    }

    model->setFilter(filter);
}

