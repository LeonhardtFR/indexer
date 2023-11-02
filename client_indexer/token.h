#ifndef TOKEN_H
#define TOKEN_H

#include <QObject>
#include <QString>

class Token
{

public:
    Token(const QString &value, QString type);

    QString value() const;
    QString type() const;

private:
    QString _value;
    QString _type;

};

#endif // TOKEN_H
