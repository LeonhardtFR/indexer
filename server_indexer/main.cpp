#include <QCoreApplication>
#include <server.h>
#include "lexer.h"
#include "token.h"
#include <fileindexer.h>
#include "db_indexer.h"
#include "cmd_factory.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    Lexer olex;
    // changer le chemin
    olex.loadDialect("C:/Users/Sandr/Documents/GitHub/indexer/server_indexer/dico.json");
    // test for search
    //QString input = QLatin1String("SEARCH \"testme please\" LAST_MODIFIED:2 days CREATED:31/12/2020 MAX_SIZE:1M EXT:txt,doc,xlsx TYPE:image OR ");
    // test for get
    //QString input = QLatin1String("GET WHITELIST");
    // test for add
    QString input = QLatin1String("ADD BLACKLIST myster");
    olex.setSource(input);
    foreach (auto token, olex.tokens())
    {
        auto tok = &token;
        qDebug() << "donne moi le token :" << tok;
        qDebug() << "donne moi le texte :" << token->text();
        qDebug() << "donne moi le type :" <<token->type();
    }

    // test factory
    // on cree la Factory
    CmdFactory *factory = new CmdFactory;

    // Ces classes d'animaux sont déja enregistrés par le constructeur de la factory
    //Cmd *poule = factory->create("CmdSearch");
    //Cmd *tigre = factory->create("CmdGet");

    //qDebug() << "create command search" << poule->type();
    //qDebug() << "create command get" << tigre->type();

    QString s = olex.tokens()[0]->text();

    if(s == "ADD")
    {
        Cmd *command = factory->create("CmdAdd");
        command->parse(olex.tokens()[1]->text());
    }
    else if(s == "GET")
    {
        Cmd *command = factory->create("CmdGet");
        command->parse(olex.tokens()[1]->text());
    }
    else if(s == "SEARCH")
    {
        Cmd *command = factory->create("CmdSearch");
        command->parse(olex.tokens()[1]->text());
    }

    /*if(olex.tokens()[0]->text() == "GET")
    {
        //Create factory CMDGet
        if(olex.tokens()[1]->type() == "TYPE_FILES")
        {

            // getFilesByType(olex.tokens()[1]->text()) (bl)
        }
        qDebug() << "start indexer :" << olex.tokens()[0]->type();
    }*/
    // decoder SEARCH command : SEARCH \"testme please\" LAST_MODIFIED:2 days CREATED:31/12/2020 MAX_SIZE:1M EXT:txt,doc,xlsx TYPE:image OR
    /*if(olex.nextToken().text() == "SEARCH")
    {



        qDebug() << "next :" << olex.tokens()[olex.current_token_index()]->text();
        // check type
        (olex.nextToken().type() == "STRING")
        {
            qDebug() << "start search first :" << olex.tokens()[olex.current_token_index()]->text();
            // rempli factory
            // getFilesByType(olex.tokens()[1]->text()) (bl)
            if(olex.nextToken().text() == "LAST_MODIFIED")
            {
                qDebug() << "start search second :" << olex.tokens()[olex.current_token_index()]->text();
                if(olex.nextToken().type() == "NUMBER")
                {
                    qDebug() << "start search second :" << olex.tokens()[olex.current_token_index()]->text();
                    if(olex.nextToken().type() == "DURATION")
                    {
                        qDebug() << "start search second :" << olex.tokens()[olex.current_token_index()]->text();

                    }
                }
            }

        }
        else
        {
            qDebug() << "NON";
        }
        if(olex.tokens()[2]->type() == "SEARCH_OPTIONS")
        {

        }
        qDebug() << "start indexer :" << olex.tokens()[0]->type();
    }*/


    // Initialize the database indexer
    db_indexer::create_database();
    server server;

    return a.exec();
}
