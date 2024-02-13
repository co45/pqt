#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    Report report(title, description); // Assuming Report is the class representing a report
    bool test = report.add(); // Assuming you have a method named 'add' to add the report to the database

    if (test)
    {
        // Perform actions after successful addition of the report
        QMessageBox::information(this, "Success", "Report added successfully!");
    }
    else
    {
        // Handle the case where the addition of the report failed
        QMessageBox::critical(this, "Error", "Failed to add report!");
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}


