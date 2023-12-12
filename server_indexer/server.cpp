#include "server.h"
#include "lexer.h"
#include "db_indexer.h"

Lexer lex;

server::server() {

    // Initialisation de la DB
    db_indexer::create_database();

    Lexer Lexer;

    tcpServer = new QTcpServer(this); // Création du serveur

    //    Lorsque l'objet tcpServer émet le signal newConnection, appelle la
    //    méthode newConnection de l'objet this (qui est une instance de la classe server).
    connect(tcpServer, &QTcpServer::newConnection, this, &server::newConnection);


    // On écoute sur toutes les adresses IP au PORT '12345'
    if(!tcpServer->listen(QHostAddress::Any, 12345)) {
        qCritical() << "ERROR : Server could not start";
    } else {
        qDebug() << "Info : Server started and listening...";
    }

    // création du thread pour l'indexation
    indexerWorker = new fileindexer_worker();

    // communication entre le serveur et le thread d'indexation
    connect(this, &server::commandReceived, indexerWorker, &fileindexer_worker::handleCommand);
    connect(indexerWorker, &fileindexer_worker::indexingProgress, this, &server::sendIndexingProgress);

}

// Méthode appelée lorsqu'une nouvelle connexion est établie
void server::newConnection() {
    // On récupere le socket client grâce à nextPendingConnection
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    clientSockets.append(clientSocket);


    // Lecture des données
    connect(clientSocket, &QTcpSocket::readyRead, this, &server::handleSocketData);

    // Déconnexion
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);

    // Erreur
    connect(clientSocket, &QTcpSocket::errorOccurred, this, &server::handleSocketError);

}

// Méthode pour gérer les données reçues d'un client
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

// Méthode pour gérer la recherche de fichiers
void server::handleSearchFiles(const QString &query, QTcpSocket *socket) {
    QStringList results = searchFiles(query);
    lex.tokenize();
    qDebug() << "Info: Found" << results.size() << "results for" << query;
    for (const QString &result : results) {

        socket->write(result.toUtf8() + "\n");
    }
}

// Méthode pour gérer les erreurs de socket
void server::handleSocketError(QAbstractSocket::SocketError error) {
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket) {
        qWarning() << "Socket error:" << error << socket->errorString();
    }
}

// Méthode pour rechercher des fichiers dans la BD
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

// Méthode pour envoyer la progression de l'indexation aux clients
void server::sendIndexingProgress(int totalFiles, int indexedFiles) {
        qDebug() << "Info: Sending indexing progress" << indexedFiles << "/" << totalFiles;

    // QString progressData = QString::number(indexedFiles) + "/" + QString::number(totalFiles);
    // QByteArray dataToSend = progressData.toUtf8() + "\n";

        QString TotalFiles = QString("TOTAL_FILES:") + QString::number(totalFiles);
        QString ProgressUpdate = QString("PROGRESS_UPDATE:") + QString::number(indexedFiles);

        QByteArray totalFilesData = TotalFiles.toUtf8() + "\n";
        QByteArray progressUpdateData = ProgressUpdate.toUtf8() + "\n";

        // QByteArray dataToSend = TotalFiles.toUtf8() + "\n" + ProgressUpdate.toUtf8() + "\n";

    // Envoyer les données à tous les clients connectés
    for(QTcpSocket* socket : clientSockets) {
        socket->write(totalFilesData);
        socket->write(progressUpdateData);
        socket->flush();
    }
}



