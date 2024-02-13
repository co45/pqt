#include "mainwindow.h"
#include "gestionRec/report.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

void MainWindow::on_pushButton_ajouter_clicked()
{
    QString title = ui->titleLineEdit->text();
    QString description = ui->descriptionLineEdit->text();

    Report report(title, description);
    bool test = report.addReport();

    if (test)
    {
        QMessageBox::information(this, "Success", "Report added successfully!");
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to add report!");
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}


