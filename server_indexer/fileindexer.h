#ifndef FILEINDEXER_H
#define FILEINDEXER_H

#include "fileindexer_worker.h"
#include <QObject>
#include <QThread>

class fileindexer : public QObject {
    Q_OBJECT

public:
    fileindexer();

private:
    fileindexer_worker *indexerWorker;
    QThread workerThread;


};

#endif // FILEINDEXER_H
