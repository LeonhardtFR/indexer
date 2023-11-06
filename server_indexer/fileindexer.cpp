#include "fileindexer.h"
#include "QSqlDatabase"
#include "QTcpSocket"
#include "QSqlQuery"
#include "QDirIterator"
#include "QSqlError"
#include "QElapsedTimer"

// Indexes the files in the database.
fileindexer::fileindexer() {
    QString connectionName = "indexerConnection";
    QSqlDatabase db = QSqlDatabase::database(connectionName);
    int indexedFiles = 0;
    QElapsedTimer timer;
    timer.start();

    indexFile("F:\\Program Files", db, indexedFiles);

    double rate = 0;
    double iElapsed = double(timer.elapsed()) / 1000;
    if (iElapsed) {
        rate = indexedFiles / iElapsed;
    }
    qDebug() << "Info: Indexing completed in" << iElapsed << "seconds -" << rate << "files/s";
}

void fileindexer::indexFile(const QString &directory, QSqlDatabase &db, int &indexedFiles) {
    qDebug() << "Info: Indexing started" << directory;

    // Préparer la requête une seule fois
    QSqlQuery query(db);
    query.prepare(QLatin1String("INSERT OR REPLACE INTO files (filePath, fileSize, fileMTime, fileLastCheck) VALUES (?, ?, ?, ?)"));

    QDirIterator it(directory, QDirIterator::Subdirectories);
    indexedFiles = 0;  // Réinitialisez le compteur de fichiers indexés

    db.transaction();  // Commencez une transaction pour l'insertion en vrac

    // Utilisez une mémoire tampon pour stocker les informations actuelles
    qint64 currentSecs = QDateTime::currentDateTime().toSecsSinceEpoch();

    while (it.hasNext()) {
        QString filePath = it.next();
        QFileInfo fileInfo(filePath);

        if (fileInfo.isFile()) {
            query.addBindValue(fileInfo.absoluteFilePath());
            query.addBindValue(fileInfo.size());
            query.addBindValue(fileInfo.lastModified().toSecsSinceEpoch());
            query.addBindValue(currentSecs);

            if (!query.exec()) {
                qWarning("Error: Failed to insert file: %s", qPrintable(query.lastError().text()));
            }

            indexedFiles++;
        }
    }
    db.commit();  // Validez la transaction
    qDebug() << "Info: Finished indexing" << indexedFiles << "files";
}

