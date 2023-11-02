#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <QObject>
#include <QString>
#include <QList>
#include <QHash>

class Lexer
{

public:
    Lexer();
    void setSource(const QString &newSource);

private:
    void tokenize();

    void addToken(QString token);
    void resetTokens();

    QString getType(QString token);

    QString _source;
    QList<Token *> _tokens;
    QHash<QString, QStringList> _dictionary;
};


#endif // LEXER_H
