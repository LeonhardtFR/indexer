#include "connect_server.h"
#include "mainwindow.h"

connect_server::connect_server() {
    get_connection();

}

QTcpSocket* connect_server::getSocket() const {
    return socket;
}


void connect_server::get_connection() {
    // create a socket
    socket = new QTcpSocket(this);

    // connect the socket
    socket->connectToHost("localhost", 12345);

    // check if the connection is established
    if(socket->waitForConnected(3000)) {
        qDebug() << "Connected";
    } else {
        qDebug() << "Not connected";
    }
}

void connect_server::sendStartCommand(const QString &directory) {
    if (socket->isOpen()) {
        qDebug() << "sendStartCommand";
        socket->write(QString("start:%1").arg(directory).toUtf8());
    }
}

void connect_server::sendStopCommand() {
    if (socket->isOpen()) {
        qDebug() << "sendStopCommand";
        socket->write(QString("stop").toUtf8());
    }
}

void connect_server::sendSearchCommand(const QString &query) {
    if (socket->isOpen()) {
        qDebug() << "sendSearchCommand";
        socket->write(QString("search:%1").arg(query).toUtf8());
    }
}
