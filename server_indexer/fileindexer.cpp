#include "fileindexer.h"
#include "QSqlDatabase"
#include "QTcpSocket"
#include "QSqlQuery"
#include "QDirIterator"
#include "QSqlError"
#include "QElapsedTimer"
#include "fileindexer_worker.h"

fileindexer::fileindexer() {

    indexerWorker = new fileindexer_worker(); // Create worker
    indexerWorker->moveToThread(&workerThread); // Move worker to the thread
    connect(&workerThread, &QThread::finished, indexerWorker, &QObject::deleteLater); // Delete worker when thread is finished

}

