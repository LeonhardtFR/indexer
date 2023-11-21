#ifndef LEXER_H
#define LEXER_H

#include <QObject>
#include <QList>
#include <QString>
#include <QMap>
#include <QRegularExpression>
#include "token.h"
#include <QObject>

class Lexer : public QObject {
    Q_OBJECT

public:
    static Lexer *instance();
    void setSource(const QString &newSource);
    const QList<Token *> &tokens() const;
    const Token &nextToken();
    const Token &currentToken() const;
    void loadDialect(QString filename);


private:
    explicit Lexer(QObject *parent = nullptr);
    void tokenize();
    QString getType(QString token);
    void addToken(QString token);
    void addTokenString(QString token);
    void addToken(QStringList tokens);
    void resetTokens();

    static Lexer *_instance;
    QString _source;
    QList<Token *> _tokens;
    int _current_token_index = -1;
    QMap<QString, QStringList> _dictionary;

signals:
    void sourceChanged();
    void tokenized(int count);
    void current_token_indexChanged(int index);
    void last_token();
    void token_not_ready();
};

#endif // LEXER_H
