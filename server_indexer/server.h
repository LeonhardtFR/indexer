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

//    static void create_database();
//    static QSqlDatabase getDatabaseConnection();

private:
    void newConnection();
    void handleSocketData();
    void handleSocketError(QAbstractSocket::SocketError error);
    void searchFile(const QString &query);

    QTcpServer *tcpServer;
    fileindexer_worker *indexerWorker;
    QThread workerThread;
    QString directory;

signals:
    void commandReceived(fileindexer_worker::Command command, QString directory = QString());
    void stopSignal(bool stop);
    void pauseSignal(bool pause);
    void startSignal(const QString &directory);
};

#endif // SERVER_H
