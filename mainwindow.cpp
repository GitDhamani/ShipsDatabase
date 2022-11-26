#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Initialise the Database
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("BAE.db3");
    mydb.open();

    //Create an Initial SQL Query
    qry = new QSqlQuery(mydb);
    qry->prepare("Select * from ShipsDB");
    qry->exec();

    //Load Query into Model and Set Model to Table View
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery(*qry);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setFixedWidth(459);

    //Configuring the Add Button to Add a New Entry
    connect(ui->addButton, &QPushButton::clicked, [=](){
            QString name = ui->nameEdit->text();
            QString commission = ui->commEdit->text();
            QString status = ui->statusEdit->text();
            QString classStr = ui->classEdit->text();
            QString typeStr = ui->typeEdit->text();

            //Insert new Entry
            qry->prepare("insert into ShipsDB (Name, Commissioned, Status, Class, Type) values ('"+name+"','"+commission+"','"+status+"','"+classStr+"','"+typeStr+"')");
            qry->exec();

            //Reshow the Table Again
            qry->prepare("Select * from ShipsDB");
            qry->exec();
            model->setQuery(*qry);
            ui->tableView->setModel(model);
        });

    //Configuring the Update Button to Update a Record
    connect(ui->updateButton, &QPushButton::clicked, [=](){
            QString name = ui->nameEdit->text();
            QString commission = ui->commEdit->text();
            QString status = ui->statusEdit->text();
            QString classStr = ui->classEdit->text();
            QString typeStr = ui->typeEdit->text();

            //Update Entry Matching Name
            qry->prepare("update ShipsDB set Name='"+name+"', Commissioned='"+commission+"',Status='"+status+"', Class='"+classStr+"', Type='"+typeStr+"' where Name='"+name+"'");
            qry->exec();

            //Reshow the Table Again
            qry->prepare("Select * from ShipsDB");
            qry->exec();
            model->setQuery(*qry);
            ui->tableView->setModel(model);
        });

    //Configure Clear Button to Clear Fields
    connect(ui->clearButton, &QPushButton::clicked, [=](){
            ui->nameEdit->clear();
            ui->commEdit->clear();
            ui->statusEdit->clear();
            ui->classEdit->clear();
            ui->typeEdit->clear();
    });


    //Configure the Delete Button to delete a Record
    connect(ui->deleteButton, &QPushButton::clicked, [=](){
            QString name = ui->nameEdit->text();
            QString typeStr = ui->typeEdit->text();

            //Delete Entry Matching Name and Type (Just to be Safe)
            qry->prepare("Delete from ShipsDB WHERE (Name='"+name+"' AND Type='"+typeStr+"')");
            qry->exec();

            //Reshow the Table Again
            qry->prepare("Select * from ShipsDB");
            qry->exec();
            model->setQuery(*qry);
            ui->tableView->setModel(model);
        });


    //Populate Fields with Data when Table Model is Clicked
    connect(ui->tableView, &QTableView::clicked, [=] (QModelIndex index) {
            QString Value = ui->tableView->model()->index(index.row(), index.column()).data().toString();

            if(index.column() == 0)
            {
              QString Surname = ui->tableView->model()->index(index.row(), index.column()+1).data().toString();
              qry->prepare("Select * from ShipsDB WHERE Name ='"+Value+"'");
              qry->exec();
              qry->next();
            }

            ui->nameEdit->setText(qry->value(0).toString());
            ui->commEdit->setText(qry->value(1).toString());
            ui->statusEdit->setText(qry->value(2).toString());
            ui->classEdit->setText(qry->value(3).toString());
            ui->typeEdit->setText(qry->value(4).toString());
        });

    //Text Field to Allow Filter by Ship Type
    connect(ui->searchEdit, &QLineEdit::textChanged, [=](){
            QString searchtxt = ui->searchEdit->text();

            //Look for a Match in Jobs
            if (searchtxt.length()!= 0)
            qry->prepare("Select * from ShipsDB WHERE Class LIKE '"+searchtxt+"'");
                else qry->prepare("Select * from ShipsDB");
            qry->exec();

            //Reshow the Table Again
            model->setQuery(*qry);
            ui->tableView->setModel(model);

        });
}

MainWindow::~MainWindow()
{
    delete ui;
    //Close Database Connection Safely
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

