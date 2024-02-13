#ifndef REC_H
#define REC_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QPrinter>
#include <QPainter>
#include <QPaintDevice>
#include <algorithm>



class Report {
private:
    int id;
    int userID;
    QString title;
    QString description;
    QDate createdDate;
    QDate lastModifiedDate;

public:
    Report() {}

    Report(int id, int userID, QString title, QString description, QDate createdDate, QDate lastModifiedDate)
        : id(id), userID(userID), title(title), description(description), createdDate(createdDate), lastModifiedDate(lastModifiedDate) {}

    bool addReport() {
        QSqlQuery query;
        query.prepare("INSERT INTO Reports (UserID, Title, Description) VALUES (:userID, :title, :description)");
        query.bindValue(":userID", userID);
        query.bindValue(":title", title);
        query.bindValue(":description", description);
        return query.exec();
    }

    bool deleteReport(int reportID) {
        QSqlQuery query;
        query.prepare("DELETE FROM Reports WHERE ID = :reportID");
        query.bindValue(":reportID", reportID);
        return query.exec();
    }

    bool updateReport(int reportID, QString newTitle, QString newDescription) {
        QSqlQuery query;
        query.prepare("UPDATE Reports SET Title = :title, Description = :description, LastModifiedDate = SYSDATE WHERE ID = :reportID");
        query.bindValue(":title", newTitle);
        query.bindValue(":description", newDescription);
        query.bindValue(":reportID", reportID);
        return query.exec();
    }

    bool checkReportExists(int reportID) {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM Reports WHERE ID = :reportID");
        query.bindValue(":reportID", reportID);
        if (query.exec() && query.next()) {
            return query.value(0).toInt() > 0;
        }
        return false;
    }

    Report getReportInfo(int reportID) {
        QSqlQuery query;
        query.prepare("SELECT UserID, Title, Description, CreatedDate, LastModifiedDate FROM Reports WHERE ID = :reportID");
        query.bindValue(":reportID", reportID);
        if (query.exec() && query.next()) {
            int userID = query.value(0).toInt();
            QString title = query.value(1).toString();
            QString description = query.value(2).toString();
            QDate createdDate = query.value(3).toDate();
            QDate lastModifiedDate = query.value(4).toDate();
            return Report(reportID, userID, title, description, createdDate, lastModifiedDate);
        }
        return Report(); // Return an empty Report object if report not found
    }

    QList<Report> getAllReports() {
        QList<Report> reportList;
        QSqlQuery query("SELECT ID, UserID, Title, Description, CreatedDate, LastModifiedDate FROM Reports");
        while (query.next()) {
            int id = query.value(0).toInt();
            int userID = query.value(1).toInt();
            QString title = query.value(2).toString();
            QString description = query.value(3).toString();
            QDate createdDate = query.value(4).toDate();
            QDate lastModifiedDate = query.value(5).toDate();
            reportList.append(Report(id, userID, title, description, createdDate, lastModifiedDate));
        }
        return reportList;
    }
};


#endif 
