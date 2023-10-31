#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class server : public QObject {
    Q_OBJECT

public:
    server();

private:
    void create_database();
    void newConnection();

    QTcpServer *tcpServer;

private slots:

};

#endif // SERVER_H
