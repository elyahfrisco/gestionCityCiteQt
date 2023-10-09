    #include "etudiantcrud.h"
    #include "ui_etudiantcrud.h"
    #include "dialogs/addetudiant.h"

    EtudiantCrud::EtudiantCrud(QWidget *parent, Db* database) :
        QWidget(parent),
        ui(new Ui::CrudEtudiant)
    {
        ui->setupUi(this);

        this->mydb = database;

        displayTable();

        ui->modifierBox->hide();

        ui->InputNumTel->setupUI("^(032|033|034|038)\\d{7}$", "Le numero de téléphone doit être de la forme\n03XXXXXXXX");
    }

    EtudiantCrud::~EtudiantCrud()
    {
        delete ui;
    }

    void EtudiantCrud::displayTable(){
        QSqlRelationalTableModel* model = new QSqlRelationalTableModel();

        model->setTable("etudiant");
        model->setEditStrategy(QSqlTableModel::OnFieldChange);

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Numéro Etudiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom Etudiant"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom Etudiant"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numéro Téléphone"));

        model->sort(0, Qt::AscendingOrder);
        model->select();

        ui->tableEtudiant->setModel(model);


        ui->tableEtudiant->setEditTriggers(QAbstractItemView::NoEditTriggers);

        ui->tableEtudiant->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        connect(ui->tableEtudiant->selectionModel(), &QItemSelectionModel::selectionChanged, this, &EtudiantCrud::on_row_selected);
    }

    void EtudiantCrud::resetTable(){
        QSqlRelationalTableModel* model = static_cast<QSqlRelationalTableModel*>(ui->tableEtudiant->model());
        model->select();
        ui->tableEtudiant->repaint();
        ui->modifierBox->hide();
    }

    void EtudiantCrud::fillInputChange(QTableView* qv, QModelIndexList indexes){
        ui->numEtudiant->setText(qv->model()->data(indexes.at(0)).toString());
        ui->InputNom->setText(qv->model()->data(indexes.at(1)).toString());
        ui->InputPrenom->setText(qv->model()->data(indexes.at(2)).toString());
        ui->InputNumTel->setText(qv->model()->data(indexes.at(3)).toString());
    }

    bool EtudiantCrud::addNewEtudiant(QString numEt, QString nomEt, QString prenomEt, QString numTel){
        if(!mydb->numEtudiantExist(numEt)){

            mydb->add("etudiant" ,{numEt, nomEt, prenomEt, numTel});
            return true;
        } else {
            QMessageBox::critical(this, "Erreur de doublon de numéro", "Le numéro de l'étudiant est déjà pris\nVeuillez entrez un nouveau");
            return false;
        }
    }

    // slots
    void EtudiantCrud::on_row_selected(const QItemSelection &selected, const QItemSelection &deselected)
    {
        Q_UNUSED(deselected);
        QTableView* qv = ui->tableEtudiant;
        if(!selected.indexes().isEmpty())
        {
            fillInputChange(qv, selected.indexes());
            ui->modifierBox->show();
        } else {
            ui->modifierBox->hide();
        }
    }


    void EtudiantCrud::on_modifierButton_clicked()
    {
        QString nomEt, prenomEt, numTel, numEt;
        nomEt = ui->InputNom->text();
        prenomEt = ui->InputPrenom->text();
        numTel = ui->InputNumTel->text();
        numEt = ui->numEtudiant->text();

        if(nomEt != ""){
            QRegularExpression* regex = new QRegularExpression("^(032|033|034|038)\\d{7}$");
            QRegularExpressionMatch match = regex->match(numTel);


            if(match.hasMatch()){
                QStringList column = {"nomet", "prenomet", "numtel"};
                QStringList values = {nomEt, prenomEt, numTel};
                QStringList id = {"numet"};
                QStringList idVal = {numEt};
                mydb->update("etudiant", column, values, id, idVal);
                resetTable();
            } else{
                QMessageBox::critical(this, "Erreur de saisie", "Le numero de Téléphone doit etre de la forme 03XXXXXXXX");
            }
        } else {
            QMessageBox::critical(this, "Erreur de saisie", "Le nom ne doit pas être vide");
        }

    }

    void EtudiantCrud::on_supprimerButton_clicked()
    {
        QModelIndex ind = ui->tableEtudiant->selectionModel()->currentIndex();
        ind = ui->tableEtudiant->model()->index(ind.row(), 0);
        QString numEt = ui->tableEtudiant->model()->data(ind).toString();

        mydb->del({"louer", "etudiant"}, {"numet"}, {numEt});
        resetTable();
        ui->modifierBox->hide();
    }


    void EtudiantCrud::on_ajoutButton_clicked()
    {
        addEtudiant* addEt = new addEtudiant(this);
        addEt->show();
    }


    void EtudiantCrud::on_searchInput_textEdited(const QString &arg1)
    {
        QSqlRelationalTableModel* model = static_cast<QSqlRelationalTableModel*>(ui->tableEtudiant->model());
        if(arg1 != ""){
            QString arg = arg1.toLower();
            QString filter = "LOWER(numet) LIKE '%" + arg + "%' OR LOWER(nomet) LIKE '%" + arg + "%' OR LOWER(prenomet) LIKE '%" + arg + "%' OR LOWER(numtel) LIKE '%" + arg + "%'";
            model->setFilter(filter);
            model->select();
        } else {
            model->setFilter("");
            model->select();
        }

    }
