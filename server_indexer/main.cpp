#include <QCoreApplication>
#include <server.h>
#include "lexer.h"
#include "token.h"
#include <fileindexer.h>
#include "db_indexer.h"
#include "cmd_factory.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Initialize the database indexer
    db_indexer::create_database();
    server server;
    // bool test = false;
    // bool in = true;
    // Lexer olex;
    // // changer le chemin
    // olex.loadDialect("D:/YNOV/MASTER_2/SEMESTRE_1/indexer/dico.json");

    // // on cree la Factory
    // CmdFactory *factory = new CmdFactory;

    // // test plusieurs
    // while(!test)
    // {    // test for search
    //     //QString input = QLatin1String("SEARCH \"testme please\" LAST_MODIFIED:2 days CREATED:31/12/2020 MAX_SIZE:1M EXT:txt,doc,xlsx TYPE:image OR ");
    //     // test for clear
    //     //QString input = QLatin1String("CLEAR WHITELIST");
    //     QString input = in ? QLatin1String("ADD WHITELIST myster") : QLatin1String("SEARCH \"testme please\" LAST_MODIFIED:2 days CREATED:31/12/2020 MAX_SIZE:1M EXT:txt,doc,xlsx TYPE:image OR ");

    //     olex.setSource(input);
    //     foreach (auto token, olex.tokens())
    //     {
    //         auto tok = &token;
    //         qDebug() << "donne moi le token :" << tok;
    //         qDebug() << "donne moi le texte :" << token->text();
    //         qDebug() << "donne moi le type :" <<token->type();
    //     }

    //     // test factory

    //     QString s = olex.tokens()[0]->text();

    //     if(s == "ADD")
    //     {
    //         Cmd *command = factory->create("CmdAdd");
    //         command->parse(olex.tokens());
    //         in = false;
    //     }
    //     else if(s == "GET")
    //     {
    //         Cmd *command = factory->create("CmdGet");
    //         command->parse(olex.tokens());
    //         test = true;
    //     }
    //     else if(s == "CLEAR")
    //     {
    //         Cmd *command = factory->create("CmdClear");
    //         command->parse(olex.tokens());
    //         test = true;
    //     }
    //     else if(s == "SEARCH")
    //     {
    //         Cmd *command = factory->create("CmdSearch");
    //         command->parse(olex.tokens());
    //         test = true;
    //     }
    // }



    return a.exec();
}
