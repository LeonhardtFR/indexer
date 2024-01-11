#ifndef LEXER_H
#define LEXER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QRegularExpression>
#include <QDebug>

#include "token.h"

class Lexer : public QObject {
    Q_OBJECT

public:
    explicit Lexer(QObject *parent = nullptr);

    const QString &source() const;
    void setSource(const QString &newSouSrce);

    const QList<Token *> &tokens() const;

    int current_token_index() const;

    Lexer *instance();

    const Token &nextToken();
    void resetToken();
    const Token &getCurrentToken();

    void loadDialect(QString filename);
    void addToken(QStringList tokens);
    void tokenize();

signals:
    void sourceChanged();
    void tokensChanged();
    void tokenized(int count);
    void current_token_indexChanged(int index);
    void last_token();
    void token_not_ready();

private:
    QString _source;
    QList<Token *> _tokens;
    int _current_token_index = -1;
    static Lexer *_instance;

    // Add other private members as needed
    QRegularExpression re_simpleSpaces;
    QRegularExpression re_addSpaceAround;
    QRegularExpression re_splitSpaces;
    QRegularExpression re_splitQuotes;
    QRegularExpression re_replaceComments;

    void resetTokens();
    void setTokens(QList<Token *> newTokens);
    QString getType(QString token);
    void addToken(QString token);
    void addTokenString(QString token);
    QHash<QString, QStringList> _dictionary;
};

QDebug operator<<(QDebug debug, const Lexer &lexer);

#endif // LEXER_H
