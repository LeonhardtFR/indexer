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

    bool isRunning; // thread is running

private:
    void insertFile(QString filePath); // insert a file in the database
    bool isPaused;
    QString directory;

signals:
    void startIndexing(const QString &directory);
    void stopIndexing();

public slots:
};

#endif // FILEINDEXER_WORKER_H
