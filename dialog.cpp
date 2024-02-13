#include "dialog.h"
#include "ui_dialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    setupModel();
    setupTable();
    loadData();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setupModel()
{
    model = new QStandardItemModel(0, 3, this);
    model->setHorizontalHeaderLabels(QStringList() << "Title" << "Description" << "Action");
}

void Dialog::setupTable()
{
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

void Dialog::loadData()
{
    QSqlDatabase db = QSqlDatabase::database(); // Assuming you have already established a connection to your database

    QSqlQuery query(db);
    query.prepare("SELECT title, description FROM reports");
    if (query.exec()) {
        while (query.next()) {
            QString title = query.value(0).toString();
            QString description = query.value(1).toString();
            QList<QStandardItem *> row;
            row.append(new QStandardItem(title));
            row.append(new QStandardItem(description));
            row.append(new QStandardItem("Show/Edit/Delete")); // Placeholder for action buttons
            model->appendRow(row);
        }
    } else {
        qDebug() << "Error fetching reports:" << query.lastError().text();
    }
}
