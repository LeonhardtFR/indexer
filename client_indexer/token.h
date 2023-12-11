#ifndef TOKEN_H
#define TOKEN_H

#include <QString>

enum TokenType {
    TOKEN_UNKNOWN,
    TOKEN_FINISH
};

class Token {
public:
    Token(const QString &value, QString type);

    friend QDebug operator<<(QDebug debug, const Token &token);

    const QString &value() const;
    TokenType type() const;

private:
    QString _value;
    TokenType _type;
};

#endif // TOKEN_H
