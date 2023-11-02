#include "fileindexer.h"
#include "QSqlDatabase"
#include "QTcpSocket"
#include "QSqlQuery"
#include "QDirIterator"
#include "QSqlError"

// Indexes the files in the database.
fileindexer::fileindexer() {
    // Utilisez le même nom de connexion pour accéder à la base de données créée précédemment
    QString connectionName = "indexerConnection";
    QSqlDatabase db = QSqlDatabase::database(connectionName);

    indexFile("C:\\Users\\maxim\\Documents\\QT", connectionName, db);
}

// pas de server encore mais juste le dossier/base de donnée
void fileindexer::indexFile(QString directory, QString connectionName, QSqlDatabase db) {
    // Start indexing the file
    qDebug() << "Info: Indexing started" << directory;


    QSqlQuery query(db);
    query.prepare(QLatin1String("INSERT OR REPLACE INTO files (filePath, fileSize, fileMTime) VALUES (?, ?, ?)"));

    QDirIterator it(directory, QDirIterator::Subdirectories);
    int indexedFiles = 0;

    db.transaction();  // Begin a transaction for bulk insertion
    while (it.hasNext()) {
        QString filePath = it.next();
        QFileInfo fileInfo(filePath);

        query.addBindValue(indexedFiles);
        query.addBindValue(fileInfo.absoluteFilePath());
        query.addBindValue(fileInfo.size());
        query.addBindValue(fileInfo.lastModified().toString());
        query.addBindValue(1);

        if (!query.exec()) {
            qWarning("Error: Failed to insert file: %s", qPrintable(query.lastError().text()));
        }

        indexedFiles++;
        qDebug() << "Info: Indexed" << indexedFiles << "files";
    }
    db.commit();  // Commit the transaction
    qDebug() << "Info: Indexing completed";
    db.close();
    QSqlDatabase::removeDatabase(connectionName);
}
