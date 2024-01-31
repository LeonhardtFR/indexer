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
    void sendIndexingProgress(int totalFiles, int indexedFiles);

    QTcpServer *tcpServer=nullptr;
    fileindexer_worker *indexerWorker;
    QThread workerThread;
    QString directory;
    QList<QTcpSocket*> clientSockets; // Liste des clients connectés

    QStringList executeSearchQuery(const QString &sqlQuery);

signals:
    void commandReceived(fileindexer_worker::Command command);
};

#endif // SERVER_H
