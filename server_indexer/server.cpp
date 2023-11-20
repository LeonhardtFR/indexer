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

    indexerWorker = new fileindexer_worker(); // Create worker
    indexerWorker->moveToThread(&workerThread); // Move worker to the thread
//    connect(&workerThread, &QThread::finished, indexerWorker, &QObject::deleteLater); // Delete worker when thread is finished
    connect(this, &server::commandReceived, indexerWorker, &fileindexer_worker::processCommand); // Connect signals
    workerThread.start(); // Start the thread

}

// Si un nouveau client se connecte
void server::newConnection() {
    // On récupere le socket client grâce à nextPendingConnection
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();

    // Lecture des données
    connect(clientSocket, &QTcpSocket::readyRead, this, &server::handleSocketData);

    // Déconnexion
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);

    // Erreur
    connect(clientSocket, &QTcpSocket::errorOccurred, this, &server::handleSocketError);

}

void server::handleSocketData() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    QString data = clientSocket->readAll();

    if (data.startsWith("start")) {
        directory = data.section(':', 1);
        qDebug() << "START";
        emit commandReceived(fileindexer_worker::Start, directory);
//        indexerWorker->processCommand(fileindexer_worker::Start, directory);
    }

    if (data.startsWith("stop")) {
        qDebug() << "STOP";
        emit commandReceived(fileindexer_worker::Stop);
//        indexerWorker->processCommand(fileindexer_worker::Stop, directory);
    }

}


// Gestion des erreurs
void server::handleSocketError(QAbstractSocket::SocketError error) {
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket) {
        qWarning() << "Socket error:" << error << socket->errorString();
    }
}


