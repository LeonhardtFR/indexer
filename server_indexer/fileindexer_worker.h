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
#include "qthread.h"

class fileindexer_worker : public QThread {
    Q_OBJECT

public:
    fileindexer_worker();
    void run() override;
    enum Command { Start, Pause, Stop };

    void setDirectory(const QString &directory);
    void handleCommand(Command command);
    int countFilesInDirectory(const QString &directory);

    bool isRunning; // thread is running

private:
    void insertFile(QString filePath); // insert a file in the database
    bool isPaused; // thread is paused
    QString directory;
    QMutex mutex;
    QWaitCondition pauseCondition;


signals:
    void startIndexing(const QString &directory);
    void stopIndexing();

    void indexingProgress(int totalFiles, int indexedFiles);

public slots:
};

#endif // FILEINDEXER_WORKER_H
