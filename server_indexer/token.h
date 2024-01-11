#ifndef TOKEN_H
#define TOKEN_H

#include <QString>
#include <QObject>

enum TokenType {
    TOKEN_UNKNOWN,
    TOKEN_FINISH
};

class Token {
public:
    Token(const QString &text, QString type);

    friend QDebug operator<<(QDebug debug, const Token &token);

    const QString &text() const;
    //TokenType type() const;
    const QString type() const;
    const QList<Token> &getTokens() const;

private:
    QString _text;
    QString _type;
    QList<Token> _tokens;
};

#endif // TOKEN_H
