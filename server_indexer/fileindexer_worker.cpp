#include "fileindexer_worker.h"
#include "qthread.h"
#include "db_indexer.h"

// Indexes the files in the database.
fileindexer_worker::fileindexer_worker() : isRunning(false) {
    QElapsedTimer timer;
    timer.start();
}

// Méthode principale pour l'exécution du thread
void fileindexer_worker::run() {
    int totalFiles = countFilesInDirectory(directory); // Compte le nombre total de fichiers dans le répertoire donné
    qDebug() << "Total files : " << totalFiles;


    int indexedFiles = 0;

    QSqlDatabase db = db_indexer::getDatabaseConnection();

    qDebug() << "Info: Indexing started" << directory;

    // Préparer la requête une seule fois
    QSqlQuery query(db);
    query.prepare(QLatin1String("INSERT OR REPLACE INTO files (filePath, fileSize, fileMTime, fileLastCheck) VALUES (?, ?, ?, ?)"));

    QDirIterator it(directory, QDirIterator::Subdirectories);  // Parcours récursif des fichiers dans le répertoire spécifié

    indexedFiles = 0;

    db.transaction();

    // utilise une mémoire tampon pour stocker les informations actuelles
    qint64 currentSecs = QDateTime::currentDateTime().toSecsSinceEpoch();

    while (it.hasNext()) {
        QString filePath = it.next();
        QFileInfo fileInfo(filePath);

        qDebug() << "Info: Indexing file";

        // Arrête l'indexation si le client envoie la commande d'arrêt
        if (!isRunning) {
            qDebug("Info: Stopping indexing");
            break;
        }

        if (fileInfo.isFile()) {
            query.addBindValue(fileInfo.absoluteFilePath());
            query.addBindValue(fileInfo.size());
            query.addBindValue(fileInfo.lastModified().toSecsSinceEpoch());
            query.addBindValue(currentSecs);

            if (!query.exec()) {
                qWarning("Error: Failed to insert file: %s", qPrintable(query.lastError().text()));
            }

            indexedFiles++;
            emit indexingProgress(totalFiles, indexedFiles); // émettre le signal de progression
        }
    }
    qDebug() << "Info: Finished indexing" << indexedFiles << "files";

    db.commit();
    db.close();
}

// Compte le nombre de fichiers dans un répertoire
int fileindexer_worker::countFilesInDirectory(const QString &directory) {
    int fileCount = 0;
    QDirIterator it(directory, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        fileCount++;
    }
    return fileCount;
}

// Gère les commandes reçues (démarrage, arrêt, pause)
void fileindexer_worker::handleCommand(Command command) {
    switch (command) {

    case Start:
        isRunning = true;
        this->start(); // démarre thread
        break;

    case Stop:
        isRunning = false; // arrêt thread
        break;

    case Pause:
        break; // TODO
    }
}

// Définit le répertoire pour l'indexation
void fileindexer_worker::setDirectory(const QString &directory) {
    this->directory = directory;
}


