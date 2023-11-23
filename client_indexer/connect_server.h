#ifndef CONNECT_SERVER_H
#define CONNECT_SERVER_H

#include <QObject>
#include <QTcpSocket>

class mainwindow;

class connect_server : public QObject {
    Q_OBJECT

public:
    connect_server();
    void sendStartCommand(const QString &directory);
    void sendStopCommand();
    void sendSearchCommand(const QString &query);

private:
    QTcpSocket *socket;
    QString directory;

    void get_connection();


signals:
    void start_indexing(QString directory);
};

#endif // CONNECT_SERVER_H
