#ifndef FILEINDEXER_WORKER_H
#define FILEINDEXER_WORKER_H

#include <QObject>
#include <QSqlDatabase>
#include <QMutex>
#include <QWaitCondition>
#include "QElapsedTimer"
#include "QDirIterator"
#include "QSqlError"
#include "QSqlQuery"
#include "QDateTime"
#include "QFileInfo"
#include "QDebug"

class fileindexer_worker : public QObject {
    Q_OBJECT

public:
    fileindexer_worker();
    enum Command { Start, Pause, Stop };

    void indexFile(const QString &directory, QSqlDatabase &db, int &indexedFiles); // Index a file in the database
//    void processCommand(Command command, QString directory); // Start/Pause/Stop
    void processCommand(Command command, const QString &directory);

private:
    void insertFile(QString filePath); // Insert a file in the database


    QMutex mutex;
    QWaitCondition pauseCondition;
    bool isRunning;
    bool isPaused;

signals:
    void startIndexing(const QString &directory);
    void stopIndexing();
};

#endif // FILEINDEXER_WORKER_H
