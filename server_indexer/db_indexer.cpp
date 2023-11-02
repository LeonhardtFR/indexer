#include <server.h>
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"
#include "QStandardPaths"
#include "QDir"

void server::create_database() {
    qDebug() << "Info: Initializing the database...";

    QString connectionName = "indexerConnection";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    if (!db.isValid()) {
        qFatal() << "Error: Cannot add database" << db.lastError().text();
        return;
    }

    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appDataLocation);
    if (!dir.exists() && !dir.mkdir(appDataLocation)) {
        qFatal() << "Error: Cannot create directory" << appDataLocation;
        return;
    }

    db.setDatabaseName(appDataLocation + "/indexerFile.db");
    if (!db.open()) {
        qFatal() << "Error: Cannot open database" << db.lastError().text();
        return;
    }

    QSqlQuery dropQuery(db);
    if (!dropQuery.exec("DROP TABLE IF EXISTS files")) {
        qFatal() << "Error: " << dropQuery.lastError().text();
        return;
    }

    QSqlQuery query(db);

    QString tblFileCreate = R"(
        CREATE TABLE IF NOT EXISTS files (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            filePath STRING,
            fileSize BIGINT,
            fileMTime BIGINT,
            fileLastCheck BIGINT
        )
    )";
    if (!query.exec(tblFileCreate)) {
        qFatal() << "Error: " << query.lastError().text();
        return;
    }

    for (int i = 0; i <= 10; i++) {
        if (!query.exec(QString("INSERT INTO files (filePath, fileSize, fileMTime, fileLastCheck) VALUES('file%1',%1,%1,%1)").arg(i))) {
            qFatal() << "Error: " << query.lastError().text();
            return;
        }
    }

    if (query.exec("SELECT * FROM files")) {
        while (query.next()) {
            qDebug() << query.value("id").toUInt() << query.value("filePath").toString()
                     << query.value("fileSize").toUInt() << query.value("fileMTime").toUInt()
                     << query.value("fileLastCheck").toUInt();
        }
    } else {
        qFatal() << "Error: " << query.lastError().text();
        return;
    }

    if (!query.exec("UPDATE files SET filePath='TESTME' WHERE id=1")) {
        qFatal() << "Error: " << query.lastError().text();
        return;
    }

    if (query.exec("SELECT * FROM files WHERE id=1")) {
        while (query.next()) {
            QString filePath = query.value("filePath").toString();
            qDebug() << filePath;
            qDebug() << (filePath == "TESTME" ? "UPDATE SUCCESS" : "UPDATE FAILS");
        }
    } else {
        qFatal() << "Error: " << query.lastError().text();
        return;
    }
    qDebug() << "Info: Database initialized successfully";
}
