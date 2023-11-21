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
    explicit Lexer(QObject *parent = nullptr);
    static Lexer *instance();

    const QString &source() const;
    void setSource(const QString &newSource);
    const QList<Token *> &tokens() const;
    int current_token_index() const;
    void resetTokens();
    void loadDialect(const QString &filename);

    const Token &nextToken();
    const Token &getCurrentToken();
    void resetToken();

signals:
    void sourceChanged();
    void tokenized(int tokenCount);
    void current_token_indexChanged(int index);
    void last_token();
    void token_not_ready();

private:
    static Lexer *_instance;
    QString _source;
    QList<Token *> _tokens;
    QMap<QString, QStringList> _dictionary;
    int _current_token_index = -1;

    void tokenize();
    QString getType(const QString &token);
    void addToken(const QString &token);
    void addTokenString(const QString &token);
    void addToken(const QStringList &tokens);
};

#endif // LEXER_H
