#include "fileindexer.h"
#include "QSqlDatabase"
#include "QTcpSocket"
#include "QSqlQuery"
#include "QDirIterator"
#include "QSqlError"
#include "QElapsedTimer"

// Indexes the files in the database.
fileindexer::fileindexer() {
    // Utilisez le même nom de connexion pour accéder à la base de données créée précédemment
    QString connectionName = "indexerConnection";
    QSqlDatabase db = QSqlDatabase::database(connectionName);

    int indexedFiles = 0;

    QElapsedTimer timer;
    timer.start();

    indexFile("C:\\Qt", connectionName, db, indexedFiles);

    double rate = 0;
    double iElapsed = double(timer.elapsed()) / 1000;
    if (iElapsed) {
        rate = indexedFiles / iElapsed;
    }
    qDebug() << "Info: Indexing completed in" << iElapsed << "seconds -" << rate << "files/s";
}

void fileindexer::indexFile(QString directory, QString connectionName, QSqlDatabase db, int& indexedFiles) {
    qDebug() << "Info: Indexing started" << directory;

    QSqlQuery query(db);
    query.prepare(QLatin1String("INSERT OR REPLACE INTO files (filePath, fileSize, fileMTime, fileLastCheck) VALUES (?, ?, ?, ?)"));

    QDirIterator it(directory, QDirIterator::Subdirectories);
    indexedFiles = 0;  // Réinitialisez le compteur de fichiers indexés

    db.transaction();  // Begin a transaction for bulk insertion
    while (it.hasNext()) {
        QString filePath = it.next();
        QFileInfo fileInfo(filePath);

        // Only index if it's a file
        if (fileInfo.isFile()) {
            query.addBindValue(fileInfo.absoluteFilePath());
            query.addBindValue(fileInfo.size());
            query.addBindValue(fileInfo.lastModified().toSecsSinceEpoch());
            query.addBindValue(QDateTime::currentDateTime().toSecsSinceEpoch());

            if (!query.exec()) {
                qWarning("Error: Failed to insert file: %s", qPrintable(query.lastError().text()));
            }

            indexedFiles++;
        }
    }
    db.commit();  // Commit the transaction
    qDebug() << "Info: Finished indexing" << indexedFiles << "files";

    db.close();
    QSqlDatabase::removeDatabase(connectionName);
}

