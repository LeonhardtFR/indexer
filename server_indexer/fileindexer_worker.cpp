#include "fileindexer_worker.h"
#include "qthread.h"
#include "db_indexer.h"

// Indexes the files in the database.
fileindexer_worker::fileindexer_worker() : isRunning(false) {
    QElapsedTimer timer;
    timer.start();
}

void fileindexer_worker::run() {
    int indexedFiles = 0;

    QSqlDatabase db = db_indexer::getDatabaseConnection();

    qDebug() << "Info: Indexing started" << directory;

    // Préparer la requête une seule fois
    QSqlQuery query(db);
    query.prepare(QLatin1String("INSERT OR REPLACE INTO files (filePath, fileSize, fileMTime, fileLastCheck) VALUES (?, ?, ?, ?)"));

    QDirIterator it(directory, QDirIterator::Subdirectories);
    indexedFiles = 0;

    db.transaction();

    // Utilisez une mémoire tampon pour stocker les informations actuelles
    qint64 currentSecs = QDateTime::currentDateTime().toSecsSinceEpoch();

    while (it.hasNext()) {
        qDebug() << "Info: Indexing file" << it.next();

        if (!isRunning) {
            qDebug("Info: Stopping indexing");
            break;
        }

//        while (isPaused) {
//            pauseCondition.wait(&mutex);
//        }

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
    qDebug() << "Info: Finished indexing" << indexedFiles << "files";

    db.commit();
    db.close();
//    QSqlDatabase::removeDatabase(connectionName);
}

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
        break;
    }
}


void fileindexer_worker::setDirectory(const QString &directory) {
    this->directory = directory;
}
