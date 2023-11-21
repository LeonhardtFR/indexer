#ifndef TOKEN_H
#define TOKEN_H

#include <QString>

class Token {
public:
    Token(QString value, QString type);
    QString getValue() const;
    QString getType() const;

private:
    QString _value;
    QString _type;
};

#endif // TOKEN_H
