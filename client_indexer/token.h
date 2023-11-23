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

    const QString &value() const;
    TokenType type() const;

private:
    QString _value;
    TokenType _type;
};

QDebug operator<<(QDebug debug, const Token &token);

#endif // TOKEN_H
