#include <server.h>
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"

void server::create_database() {
    qDebug() << "Info: Initializing the database...";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("chat.db");

    if (!db.open()) {
        qFatal("Error: Cannot open database");
        return;
    }

    QSqlQuery query;

    if(!query.exec(
            ("CREATE TABLE IF NOT EXISTS files ("
             "id INTEGER PRIMARY KEY AUTOINCREMENT, "
             "name TEXT UNIQUE, "
             "message TEXT, "
             "DATE DATE)")
            )) {
        qFatal("Error: Failed to create table: %s", qPrintable(query.lastError().text()));
    } else {
        qDebug() << "Info: Database initialized successfully";
    }
}
