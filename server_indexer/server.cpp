#include "server.h"
#include "lexer.h"
#include "db_indexer.h"
#include "cmd_factory.h"

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
    connect(clientSocket, &QTcpSocket::readyRead, this, &server::handleSocketData); // si le socket client a des données à lire, on appelle handleSocketData

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

    if(data.startsWith("pause")) {
        emit commandReceived(fileindexer_worker::Pause); // envoie commande de pause
    }

    if(data.startsWith("search")) {
        QString query = data.section(':', 1);

        this->handleSearchFiles(query, clientSocket); // envoie commande de recherche
    }
}


void server::handleSearchFiles(const QString &query, QTcpSocket *socket) {
    Lexer olex;

    olex.loadDialect();
    olex.setSource(query);

    // on cree la Factory
    CmdFactory *factory = new CmdFactory;

    QString s = olex.tokens()[0]->text();

    qDebug() << "Info: Found" << s << "for" << query;

    Cmd *command = nullptr;

    if(s == "ADD") {
        command = factory->create("CmdAdd");
    } else if(s == "GET") {
        command = factory->create("CmdGet");
    } else if(s == "CLEAR") {
        command = factory->create("CmdClear");
    } else if(s == "SEARCH") {
        qDebug() << "Info: Searching for" << query;
        command = factory->create("CmdSearch");
    }

    if (command) {
        command->parse(olex.tokens());

        if (CmdSearch* searchCommand = dynamic_cast<CmdSearch*>(command)) {
            QString sqlQuery = searchCommand->buildSQLQuery();
            QStringList results = executeSearchQuery(sqlQuery);
            qDebug() << "Executing SQL query:" << sqlQuery;

            if (!results.isEmpty()) {
                // Envoie les résultats uniquement s'ils ne sont pas vides
                for (const QString &result : results) {
                    socket->write(result.toUtf8() + "\n");
                }
            } else {
                // Envoie un message indiquant qu'aucun résultat n'a été trouvé
                QString noResultMessage = "No results found for the query.";
                socket->write(noResultMessage.toUtf8() + "\n");
            }
        }
    }
}

QStringList server::executeSearchQuery(const QString &sqlQuery) {
    QStringList results;
    QSqlDatabase db = db_indexer::getDatabaseConnection();
    QSqlQuery q(db);
    q.prepare(sqlQuery);

    if (q.exec()) {
        while (q.next()) {
            results.append(q.value(0).toString()); // on ajoute les résultats à la liste de résultats
        }
    } else {
        qWarning("Error: Failed to execute search query: %s", qPrintable(q.lastError().text()));
    }

    db.close();
    return results;
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

        QString TotalFiles = QString("TOTAL_FILES:") + QString::number(totalFiles);
        QString ProgressUpdate = QString("PROGRESS_UPDATE:") + QString::number(indexedFiles);

        QByteArray totalFilesData = TotalFiles.toUtf8() + "\n";
        QByteArray progressUpdateData = ProgressUpdate.toUtf8() + "\n";

    // Envoyer les données à tous les clients connectés
    for(QTcpSocket* socket : clientSockets) {
        socket->write(totalFilesData);
        socket->write(progressUpdateData);
        socket->flush();
    }
}



