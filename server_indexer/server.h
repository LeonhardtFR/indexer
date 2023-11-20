#ifndef SERVER_H
#define SERVER_H

#include "fileindexer_worker.h"
#include "qthread.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class server : public QObject {
    Q_OBJECT

public:
    server();
    enum Command { Start, Pause, Stop };

    static void create_database();

signals:


private:
    void newConnection();
    void handleSocketData();
    void handleSocketError(QAbstractSocket::SocketError error);

    QTcpServer *tcpServer;
    fileindexer_worker *indexerWorker;
    QThread workerThread;
    QString directory;

private slots:

};

#endif // SERVER_H
