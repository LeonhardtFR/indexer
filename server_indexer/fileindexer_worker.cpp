#include "fileindexer.h"
#include "fileindexer_worker.h"

// Indexes the files in the database.
fileindexer_worker::fileindexer_worker() {
    QString connectionName = "indexerConnection";
    QSqlDatabase db = QSqlDatabase::database(connectionName);
    int indexedFiles = 0;
    QElapsedTimer timer;
    timer.start();

    isRunning = true;
    isPaused = false;

//    indexFile("F:\\Program Files", db, indexedFiles);

//    double rate = 0;
//    double iElapsed = double(timer.elapsed()) / 1000;
//    if (iElapsed) {
//        rate = indexedFiles / iElapsed;
//    }
//    qDebug() << "Info: Indexing completed in" << iElapsed << "seconds -" << rate << "files/s";
}

void fileindexer_worker::indexFile(const QString &directory, QSqlDatabase &db, int &indexedFiles) {
    qDebug() << "Info: Indexing started" << directory;

    // Préparer la requête une seule fois
    QSqlQuery query(db);
    query.prepare(QLatin1String("INSERT OR REPLACE INTO files (filePath, fileSize, fileMTime, fileLastCheck) VALUES (?, ?, ?, ?)"));

    QDirIterator it(directory, QDirIterator::Subdirectories);
    indexedFiles = 0;  // Réinitialise le compteur de fichiers indexés

    db.transaction();  // Commencez une transaction pour l'insertion

    // Utilisez une mémoire tampon pour stocker les informations actuelles
    qint64 currentSecs = QDateTime::currentDateTime().toSecsSinceEpoch();

    while (it.hasNext()) {
        qDebug() << "Info: Indexing file" << it.next();

        if (!isRunning) {
            break;
        }

        while (isPaused) {
            pauseCondition.wait(&mutex);
        }

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
    db.commit();  // Valide la transaction
    qDebug() << "Info: Finished indexing" << indexedFiles << "files";
}

void fileindexer_worker::processCommand(Command command, const QString &directory) {
    switch (command) {
    case Start:
        isRunning = true;
        indexFile(directory);
        break;
    case Stop:
        isRunning = false;
        break;
    }
}




// Indexer command (Start/Pause/Stop)
//void fileindexer_worker::processCommand(Command command, QString directory) {
//    QString connectionName = "indexerConnection";
//    QSqlDatabase db = QSqlDatabase::database(connectionName);
//    int indexedFiles = 0;
//    switch (command) {
//    case Start:
//        // Logique de démarrage
//        qDebug() << "Info: Starting indexer : " + directory;
//        isRunning = true;
//        isPaused = false;
//        indexFile(directory, db, indexedFiles);
//        break;
//    case Pause:
//        // Logique de pause
//        break;
//    case Stop:
//        // Logique d'arrêt
//        break;
//    }
//}
