#include "server.h"

server::server() {

    // Initialisation de la DB
    create_database();

    tcpServer = new QTcpServer(this);

    //    Lorsque l'objet tcpServer émet le signal newConnection, appelle la
    //    méthode newConnection de l'objet this (qui est une instance de la classe server).
    connect(tcpServer, &QTcpServer::newConnection, this, &server::newConnection);

    // On écoute sur toutes les adresses IP au PORT '12345'
    if(!tcpServer->listen(QHostAddress::Any, 12345)) {
        qCritical() << "ERROR : Server could not start";
    } else {
        qDebug() << "Info : Server started and listening...";
    }

}

// Si un nouveau client se connecte
void server::newConnection() {
    // On récupere le socket client grâce à nextPendingConnection
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();

    connect(clientSocket, &QTcpSocket::readyRead, [clientSocket]() {
        QByteArray data = clientSocket->readAll();
        qDebug() << "Received : " << data;
        clientSocket->write("Message received");
    });

    // Déconnexion
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);

}
