#include "fileindexer_worker.h"
#include "db_indexer.h"

// Indexes the files in the database.
fileindexer_worker::fileindexer_worker() : isRunning(false) {
    QElapsedTimer timer;
    timer.start();
}

// Méthode principale pour l'exécution du thread
void fileindexer_worker::run() {
    int totalFiles = countFilesInDirectory(directory);
    qDebug() << "Total files: " << totalFiles;

    QSqlDatabase db = db_indexer::getDatabaseConnection();
    QSqlQuery query(db);
    query.prepare(QLatin1String("INSERT OR REPLACE INTO files (filename, last_modified, created, file_size, file_extension, file_type) VALUES (?, ?, ?, ?, ?, ?)"));

    QDirIterator it(directory, QDirIterator::Subdirectories);
    int indexedFiles = 0;
    qint64 currentSecs = QDateTime::currentDateTime().toSecsSinceEpoch();
    db.transaction();

    while (isRunning) {
        mutex.lock(); // verrouillage du mutex pour éviter les conflits d'accès
        while (isPaused) {
            pauseCondition.wait(&mutex);
        }
        mutex.unlock();

        if (!it.hasNext()) break;
        QString filename = it.next();
        QFileInfo fileInfo(filename);

        if (fileInfo.isFile()) {
            QString filename = fileInfo.fileName(); // nom du fichier
            QString fileExtension = fileInfo.suffix(); // l'extension du fichier
            QString fileType; // type de fichier

            // Ajout des valeurs liées à la requête
            query.addBindValue(filename); // pour 'filename'
            query.addBindValue(fileInfo.lastModified().toSecsSinceEpoch()); // pour 'last_modified'
            query.addBindValue(currentSecs); // pour 'created', supposé que 'currentSecs' est la valeur correcte
            query.addBindValue(fileInfo.size()); // pour 'filesize'
            query.addBindValue(fileExtension); // pour 'file_extension'
            query.addBindValue(fileType); // pour 'file_type'

            if (!query.exec()) {
                qWarning() << "Error: Failed to insert file: " << query.lastError().text();
            }
            indexedFiles++;
            emit indexingProgress(totalFiles, indexedFiles);
        }
    }

    // réinitialisation des états à la fin de l'exécution
    QMutexLocker locker(&mutex);
    isRunning = false;
    isPaused = false;

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
    QMutexLocker locker(&mutex); // verrouillage du mutex pour éviter les conflits d'accès
    switch (command) {
    case Start:
        if (!isRunning) {
            isRunning = true;
            isPaused = false;
            start();
        }
        break;
    case Stop:
        isRunning = false;
        pauseCondition.wakeAll();
        break;
    case Pause:
        isPaused = !isPaused;
        if (!isPaused) {
            pauseCondition.wakeAll();
        }
        break;
    }
}

// Définit le répertoire pour l'indexation
void fileindexer_worker::setDirectory(const QString &directory) {
    this->directory = directory;
}


