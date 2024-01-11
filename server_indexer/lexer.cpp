
#include "lexer.h"
#include "token.h"

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include <iostream>


QDebug operator<<(QDebug debug, const Token &token) {
    QDebugStateSaver saver(debug);
    qDebug() << "** Token **" << token;
    return debug.space();
}

QDebug operator<<(QDebug debug, const Lexer &lexer) {
    QDebugStateSaver saver(debug);
    qDebug() << "** LEXER **";
    foreach (auto token, lexer.tokens()) { qDebug() << *token; }
    return debug;
}



Lexer *Lexer::_instance = new Lexer();

// region Constructor

Lexer::Lexer(QObject *parent) : QObject{parent} {
}

// endregion constructor


const QString &Lexer::source() const {
    return _source;
}



void Lexer::setSource(const QString &newSource) {
    qDebug() << __FUNCTION__;
    if (_source == newSource)
    {
        qDebug() << "source is same as newSource";
        return;
    }
    _source = newSource;
    tokenize();
    emit sourceChanged();
}



const QList<Token *> &Lexer::tokens() const {
    return _tokens;
}



void Lexer::setTokens(QList<Token *>newTokens) {
    if (_tokens == newTokens)
        return;
    _tokens = newTokens;
    emit tokensChanged();
}



void Lexer::resetTokens() {
    setTokens({}); // TODO: Adapt to use your actual default value
    _tokens.clear();
}




int Lexer::current_token_index() const {
    return _current_token_index;
}




void Lexer::tokenize() {
    qDebug() << __FUNCTION__;
    resetTokens();
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

    foreach (QString s, tmpList) {
        if (s.isEmpty())
            continue;
        if (inside) {          // If 's' is inside quotes ...
            addTokenString(s); // ... get the whole string
        } else {               // If 's' is outside quotes ...
            s.replace(re_addSpaceAround, " \\1 ");
            s = s.trimmed();
            // removes comments
            s.replace(re_replaceComments, "");
            //qDebug() << __FUNCTION__ << __LINE__ << s;
            addToken(s.split(re_splitSpaces, Qt::SkipEmptyParts)); // ... get the splitted string
        }
        inside = !inside;
    }


    emit tokenized(_tokens.count());
}

Lexer *Lexer::instance() {
    return _instance;
}

const Token &Lexer::nextToken() {
    qDebug() << __FUNCTION__ << _current_token_index << _tokens.count();
    if (_current_token_index < _tokens.count() - 1) {
        qDebug() << "index ok" << _current_token_index;
        _current_token_index++;
        emit current_token_indexChanged(_current_token_index);
    } else {
        emit last_token();
        return *new Token("", QStringLiteral("TOKEN_FINISH"));
    }
    return *_tokens.at(_current_token_index);
}



void Lexer::resetToken() {
    _current_token_index = -1;
    emit token_not_ready();
}



const Token &Lexer::getCurrentToken() {
    std::cout << "getCurrentToken" << std::endl;

    // Token *ret = nullptr;
    if (_current_token_index == -1) {
        emit token_not_ready();
        // ret = new Token("", TOKEN_NONE);
        // ret = _tokens.at(_current_token_index);
    }
    return *_tokens.at(_current_token_index);
}


QString Lexer::getType(QString token) {
    qDebug() << __FUNCTION__ << token << _dictionary.keys();

    foreach (QString category, _dictionary.keys()) {
        if (_dictionary[category].contains(token.toUpper())) {
            return category;
        }
    }
    qDebug() << __FUNCTION__ << token << TOKEN_UNKNOWN;
    static QRegularExpression re;

    //
    re.setPattern("\\d{2}/\\d{2}/?");
    if (re.match(token).hasMatch()) {
        return "DATE";
    }

    //
    re.setPattern("\\d+[KMG]+");
    if (re.match(token).hasMatch()) {
        return "SIZE";
    }

    //
    re.setPattern("\\d+\\.\\d+");
    if (re.match(token).hasMatch()) {
        return "DOUBLE";
    }

    //
    re.setPattern("^[a-zA-Z_]{1}[0-9a-zA-Z_]+");
    if (re.match(token).hasMatch()) {
        return "IDENTIFIER";
    }
    re.setPattern("^\\d+$");
    if (re.match(token).hasMatch()) {
        return "NUMBER";
    }



    return QStringLiteral("TOKEN_UNKNOWN");
}



void Lexer::addToken(QString token) {
    static QString lasttype;
    // dont add multiple final tokens
    QString type = getType(token);
    if (lasttype == "FINAL" && type == "FINAL") {
        lasttype = type;
        return;
    }



    Token *tokenObj = new Token(token, type);
    _tokens.append(tokenObj);
    lasttype = type;
}



void Lexer::addTokenString(QString token) {
    Token *tokenObj = new Token(token.trimmed(), "STRING");
    _tokens.append(tokenObj);
}



void Lexer::addToken(QStringList tokens) {
    qDebug() << tokens;
    foreach (auto token, tokens) { addToken(token); }
}




void Lexer::loadDialect(QString filename) {
    qDebug() << __FUNCTION__;
    // load the file
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qWarning() << "Dialect file missing !!";
    QString dialect = file.readAll();
    file.close();

    // parse json
    QJsonParseError jsonError;
    QJsonDocument   doc = QJsonDocument::fromJson(dialect.toUtf8(), &jsonError);
    if (doc.isNull()) {
        qDebug() << "Parse failed";
    }
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << QString("Error while parsing dialect (%1): %2").arg(filename, jsonError.errorString());
        return;
    }



    // load the json into the qmap
    if (doc.isObject()) {
        QJsonObject jsonObj = doc.object();
        foreach (auto topic, jsonObj.keys()) {
            foreach (auto word, jsonObj[topic].toArray().toVariantList()) {
                _dictionary[topic] << word.toString();
            }
        }
    }
}
