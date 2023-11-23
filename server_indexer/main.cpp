#include <QCoreApplication>
#include <server.h>
#include <fileindexer.h>
#include "db_indexer.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Initialize the database indexer
    db_indexer::create_database();
    server server;

    return a.exec();
}
