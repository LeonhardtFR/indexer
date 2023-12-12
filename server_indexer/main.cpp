#include <QCoreApplication>
#include <server.h>
#include "lexer.h"
#include "token.h"
#include <fileindexer.h>
#include "db_indexer.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    Lexer olex;
    // changer le chemin
    olex.loadDialect("C:/Users/Sandr/Documents/GitHub/indexer/server_indexer/dico.json");
    QString input = QLatin1String("SEARCH \"testme please\" LAST_MODIFIED:2 days CREATED:31/12/2020 MAX_SIZE:1M EXT:txt,doc,xlsx TYPE:image OR ");
    olex.setSource(input);
    foreach (auto token, olex.tokens())
    {
        auto tok = &token;
        qDebug() << "donne moi le token :" << tok;
        qDebug() << "donne moi le texte :" << token->text();
        qDebug() << "donne moi le type :" <<token->type();
    }
    // Initialize the database indexer
    db_indexer::create_database();
    server server;

    return a.exec();
}
