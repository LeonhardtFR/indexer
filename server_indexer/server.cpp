#include "server.h"
#include "db_indexer.h"

server::server() {

    // Initialisation de la DB
    db_indexer::create_database();

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

    indexerWorker = new fileindexer_worker();
    connect(this, &server::commandReceived, indexerWorker, &fileindexer_worker::handleCommand);
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

    qDebug() << "Info: Received" << data;

    if (data.startsWith("start")) {
        directory = data.section(':', 1);
        indexerWorker->setDirectory(directory);
        emit commandReceived(fileindexer_worker::Start); // envoie commande de démarrage
    }

    if(data.startsWith("stop")) {
        emit commandReceived(fileindexer_worker::Stop); // envoie commande d'arrêt
    }

    if(data.startsWith("search")) {
        QString query = data.section(':', 1);
        this->handleSearchFiles(query, clientSocket); // envoie commande de recherche
    }
}

// Gestion de la recherche de fichiers
void server::handleSearchFiles(const QString &query, QTcpSocket *socket) {
    QStringList results = searchFiles(query);
    qDebug() << "Info: Found" << results.size() << "results for" << query;
    for (const QString &result : results) {
        socket->write(result.toUtf8() + "\n");
    }
}

// Gestion des erreurs
void server::handleSocketError(QAbstractSocket::SocketError error) {
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket) {
        qWarning() << "Socket error:" << error << socket->errorString();
    }
}

// Recherche de fichiers
QStringList server::searchFiles(const QString &query) {
    qDebug() << "Info: Searching for" << query;

    QStringList results;

    QSqlDatabase db = db_indexer::getDatabaseConnection();

    QSqlQuery q(db);
    q.prepare("SELECT filePath FROM files WHERE filePath LIKE :query");
    q.bindValue(":query", "%" + query + "%");

    if (q.exec()) {
        while (q.next()) {
            results.append(q.value(0).toString());
        }
    } else {
        qWarning("Error: Failed to search files: %s", qPrintable(q.lastError().text()));
    }

    db.close();
    return results;
}



