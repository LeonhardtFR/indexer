#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class server : public QObject {
    Q_OBJECT

public:
    server();

    static void create_database();

private:
//    void newConnection();
//    void handleSocketData();
//    void handleSocketError(QAbstractSocket::SocketError error);

//    QTcpServer *tcpServer;

private slots:

};

#endif // SERVER_H
