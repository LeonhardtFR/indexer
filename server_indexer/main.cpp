#include <QCoreApplication>
#include <server.h>
#include <fileindexer.h>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Initialize the database indexer
    server::create_database();

    // Start indexer
    fileindexer indexer;

//    server server;
    return a.exec();
}
