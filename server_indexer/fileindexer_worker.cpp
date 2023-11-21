#include "fileindexer_worker.h"
#include "qstandardpaths.h"
#include "qthread.h"

// Indexes the files in the database.
fileindexer_worker::fileindexer_worker() {
    QElapsedTimer timer;
    timer.start();
}

void fileindexer_worker::indexFile(const QString &directory, int &indexedFiles) {
    QString connectionName = QString("indexerConnection_%1").arg((quintptr)QThread::currentThreadId());
    QSqlDatabase db = QSqlDatabase::database(connectionName);

    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);


    if (!db.isOpen()) {
        // Ouverture de la base de données si elle n'est pas déjà ouverte
        db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        db.setDatabaseName(appDataLocation + "/indexerFile.db");
            if (!db.open()) {
            qWarning() << "Error: Cannot open database" << db.lastError().text();
            return;
        }
    }

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
    qDebug() << "Info: Finished indexing" << indexedFiles << "files";

    db.commit();
    db.close();
    QSqlDatabase::removeDatabase(connectionName);
}

void fileindexer_worker::processCommand(Command command, const QString &directory) {
    int indexedFiles = 0;
    switch (command) {
    case Start:
        isRunning = true;
        indexFile(directory, indexedFiles);
        break;
    case Stop:
        qDebug() << "TEST10";
        isRunning = false;
        break;
    case Pause:
        break;
    }
}
