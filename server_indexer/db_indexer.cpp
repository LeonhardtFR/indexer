#include <server.h>
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"
#include "QStandardPaths"
#include "QDir"

void server::create_database() {
    qDebug() << "Info: Initializing the database...";

    // Nom unique de la connection
    QString connectionName = "indexerConnection";

    // Create database with a specific connection name
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    if (db.lastError().isValid()) {
        qFatal() << "Error: Cannot add database" << db.lastError().text();
        return;
    }

    // getting system application data folder
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    // creating the folder if it doesn't exist
    QDir dir(appDataLocation);
    if (!dir.exists()) {
        dir.mkdir(appDataLocation);
        qDebug() << "mkdir" << appDataLocation;
    }

    // setup the db file name and open it
    QString dbPath = appDataLocation + "/indexerFile.db";
    qDebug() << "dbPath" << dbPath;
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qFatal() << "Error: Cannot open database" << db.lastError().text() << dbPath;
        return;
    }

    // Get the database instance with the specific connection name
    QSqlDatabase dbInstance = QSqlDatabase::database(connectionName);
    QSqlQuery query(dbInstance);

    // create a table
    QString tblFileCreate = "CREATE TABLE IF NOT EXISTS files ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                            "filePath STRING,"
                            "fileSize BIGINT,"
                            "fileMTime BIGINT,"
                            "fileLastCheck BIGINT"
                            ")";
    query.exec(tblFileCreate);

    if (query.lastError().isValid()) {
        qWarning() << "CREATE TABLE" << query.lastError().text();
        return;
    }

    const int INSERTS_COUNT = 10;
    for (int i = 0; i <= INSERTS_COUNT; i++) {
        QString sqlInsert = "INSERT INTO files (filePath, fileSize, fileMTime, fileLastCheck) " +
                            QString("VALUES('file%1',%1,%1,%1)").arg(i);
        query.exec(sqlInsert);

        if (query.lastError().isValid()) {
            qWarning() << "INSERT" << query.lastError().text();
            return;
        }
    }

    // query the data
    QString sqlSelect = "SELECT * FROM files";
    query.exec(sqlSelect);

    if (query.lastError().isValid()) {
        qWarning() << "SELECT" << query.lastError().text();
        return;
    }

    while (query.next()) {
        uint    id            = query.value("id").toUInt();
        QString filePath      = query.value("filePath").toString();
        uint    fileSize      = query.value("fileSize").toUInt();
        uint    fileMTime     = query.value("fileMTime").toUInt();
        uint    fileLastCheck = query.value("fileLastCheck").toUInt();
        qDebug() << id << filePath << fileSize << fileMTime << fileLastCheck;
    }

    // update some data
    QString sqlUpdate = "UPDATE files SET filePath='TESTME' WHERE id=1";
    query.exec(sqlUpdate);
    if (query.lastError().isValid()) {
        qWarning() << "UPDATE" << query.lastError().text();
        return;
    }

    // check the update
    sqlSelect = "SELECT * FROM files WHERE id=1";
    query.exec(sqlSelect);

    if (query.lastError().isValid()) {
        qWarning() << "SELECT" << query.lastError().text();
        return;
    }

    while (query.next()) {
        uint    id            = query.value("id").toUInt();
        QString filePath      = query.value("filePath").toString();
        uint    fileSize      = query.value("fileSize").toUInt();
        uint    fileMTime     = query.value("fileMTime").toUInt();
        uint    fileLastCheck = query.value("fileLastCheck").toUInt();
        qDebug() << id << filePath << fileSize << fileMTime << fileLastCheck;
        if (filePath == "TESTME") {
            qDebug() << "UPDATE SUCCESS";
        } else
            qDebug() << "UPDATE FAILS";
    }

    qDebug() << "Info: Database initialized successfully";

    // drop the table
    //    query.exec("DROP TABLE files");
    //    if (query.lastError().isValid()) {
    //        qWarning() << "DROP TABLE" << query.lastError().text();
    //    }
    return;
}
