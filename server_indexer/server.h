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

private:
    void newConnection();
    void handleSocketData();
    void handleSocketError(QAbstractSocket::SocketError error);
    void handleSearchFiles(const QString &query, QTcpSocket *socket);
    QStringList searchFiles(const QString &query);

    QTcpServer *tcpServer=nullptr;
    fileindexer_worker *indexerWorker;
    QThread workerThread;
    QString directory;
    QTcpSocket *clientSocket;

signals:
    void commandReceived(fileindexer_worker::Command command);
};

#endif // SERVER_H
