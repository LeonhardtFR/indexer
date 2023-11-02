#include "lexer.h"


#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>

Lexer::Lexer()
{

}

//lexer *lexer::_instance = new lexer();

void Lexer::setSource(const QString &newSource) {
    if (_source == newSource)
        return;
    _source = newSource;
    tokenize();
    qDebug() << "emit sourceChanged()";
}

void Lexer::addToken(QString token) {
    static QString lasttype;
    // dont add multiple final tokens
    QString type = getType(token);
    qDebug() << type;
    if (lasttype == "FINAL" && type == "FINAL") {
        lasttype = type;
        return;
    }

    Token *tokenObj = new Token(token, type);
    _tokens.append(tokenObj);
    lasttype = type;
}


void Lexer::resetTokens() {
    qDebug() << __FUNCTION__;
    // setTokens({}); // TODO: Adapt to use your actual default value
    _tokens.clear();
}



void Lexer::tokenize() {
    qDebug() << __FUNCTION__;

    resetTokens(); //resetTokens();
    if (_source.isEmpty())
    {
        qDebug() << "source empty";
        return;
    }
    _source = _source.trimmed();
    static QRegularExpression re_simpleSpaces("(\\n+)");
    static QRegularExpression re_addSpaceAround("([^a-zA-Z0-9._/]{1})");
    static QRegularExpression re_splitSpaces("[ \\t]");
    static QRegularExpression re_splitQuotes("\"");
    static QRegularExpression re_replaceComments("#.+\\n");
    _source.replace(re_simpleSpaces, "\n");


    QString cmd = _source;

    bool inside = false;

    QStringList tmpList = cmd.split(re_splitQuotes);
    //qDebug() << tmpList;

    foreach (QString s, tmpList) {
        qDebug() << "on foreach";
        if (s.isEmpty())
            continue;
        if (inside) {          // If 's' is inside quotes ...
            qDebug() << "addTokenString(s)"; // ... get the whole string
        } else {               // If 's' is outside quotes ...

            s.replace(re_addSpaceAround, " \\1 ");
            s = s.trimmed();
            // removes comments
            s.replace(re_replaceComments, "");
            // qDebug() << __FUNCTION__ << __LINE__ << s;
            qDebug() << "after replaceComments" << s;
            //addToken(s.split(re_splitSpaces, Qt::SkipEmptyParts)) ; // ... get the splitted string
        }
        inside = !inside;
    }

    qDebug() << "emit tokenized(_tokens.count())";
}

QString Lexer::getType(QString token) {
    qDebug() << __FUNCTION__ << token << _dictionary.keys();

    foreach (QString category, _dictionary.keys()) {
        qDebug() << "Searching in catgory" << category;
        if (_dictionary[category].contains(token.toUpper())) {
            qDebug() << __FUNCTION__ << token << category;
            return category;
        }
    }
    // qDebug() << __FUNCTION__ << token << TOKEN_UNKNOWN;
    static QRegularExpression re;


    re.setPattern("\\d{2}/\\d{2}/?");
    if (re.match(token).hasMatch()) {
        return "DATE";
    }

    re.setPattern("\\d+[KMG]+");
    if (re.match(token).hasMatch()) {
        return "SIZE";
    }

    re.setPattern("\\d+\\.\\d+");
    if (re.match(token).hasMatch()) {
        return "DOUBLE";
    }

    re.setPattern("^[a-zA-Z_]{1}[0-9a-zA-Z_]+");
    if (re.match(token).hasMatch()) {
        return "IDENTIFIER";
    }
    re.setPattern("^\\d+$");
    if (re.match(token).hasMatch()) {
        return "NUMBER";
    }

    return "TOKEN_UNKNOWN";
}

