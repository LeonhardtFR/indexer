#include "cmd_factory.h"
#include "db_indexer.h"
#include <QCoreApplication>
#include <QDebug>
#include <QMap>
#include <QString>
#include "QSqlDatabase"
#include "QSqlQuery"
#include <QSqlError>
#include "QDateTime"

/** Util class **/

static QString checkAndGetFolderType(Token token)
{
    if(token.type() == "TYPE_FILES")
    {
        return token.text().toLower();
    }
    else // error
    {
        qWarning() << __FUNCTION__ << "Bad type file";
        // throw exception
        return NULL;
    }
}

static void executeCommand(QString request)
{
    QSqlDatabase db = db_indexer::getDatabaseConnection();

    QSqlQuery query(db);

    qDebug() << request;

    if (!query.exec(request)) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
    }

    db.close();
}

/** CmdSearch class **/
CmdSearch::CmdSearch() {}

// Méthode pour analyser les tokens et construire les critères de recherche
void CmdSearch::parse(QList<Token *> tokens) {
    qDebug() << __FUNCTION__ << "on SEARCH";

    QString currentKey;
    QString currentValue;
    bool isValue = false;

    if (tokens.size() > 1) {
        if (tokens[0]->text().toUpper() == "SEARCH") {
            tokens.removeFirst();
        }

        // Le prochain token est supposé être le terme de recherche
        if (!tokens.isEmpty()) {
            filename = QString(tokens[0]->text()).remove('\"');
            tokens.removeFirst();
        }
    }


    for (Token* token : tokens) {
        QString tokenText = token->text();

        // Vérifie si le token est une clé connue
        if (tokenText == "LAST_MODIFIED" || tokenText == "CREATED" || tokenText == "MAX_SIZE" || tokenText == "MIN_SIZE" || tokenText == "SIZE" || tokenText == "EXT" || tokenText == "TYPE") {
            if (!currentKey.isEmpty() && !currentValue.isEmpty()) {
                // Traiter la paire clé-valeur précédente
                processKeyValue(currentKey, currentValue);

                // réinitialise pour la prochaine paire clé-valeur
                currentKey = "";
                currentValue = "";
            }
            currentKey = tokenText;
            isValue = false;
        } else if (tokenText == ":") {
            // Si le token est un deux-points, le prochain token sera une valeur
            isValue = true;
        } else if (isValue) {
            // gérer les valeurs avec espaces
            if (!currentValue.isEmpty()) {
                currentValue += " ";
            }
            currentValue += tokenText;
        }
    }

    // traite la dernière paire clé-valeur
    if (!currentKey.isEmpty() && !currentValue.isEmpty()) {
        processKeyValue(currentKey, currentValue);
    }
    this->run();
}

// Méthode pour traiter une paire clé-valeur de critères de recherche
void CmdSearch::processKeyValue(const QString& key, const QString& value) {
    qDebug() << "Clé:" << key << "Valeur:" << value;

    if (key == "LAST_MODIFIED" || key == "CREATED") {
        parseDateSpec(key, value);
    } else if (key == "MAX_SIZE" || key == "MIN_SIZE" || key == "SIZE") {
        parseSizeSpec(key, value);
    } else if (key == "EXT" || key == "TYPE") {
        parseListSpec(key, value);
    }
}



// Méthode exécutée pour lancer la recherche
void CmdSearch::run() {
    qDebug() << __FUNCTION__ << "on Search class";

    QString sqlQuery = buildSQLQuery();
    if (sqlQuery.isEmpty()) {
        qDebug() << "Requête SQL vide ou invalide";
        return;
    }

    // exécution de la requête SQL
    executeCommand(sqlQuery);
}

void CmdSearch::parseDateSpec(const QString& key, const QString& value) {
    QDateTime date;
    if (value.contains("BETWEEN", Qt::CaseInsensitive) && key.toUpper() == "LAST_MODIFIED") {
        QStringList dateParts = value.split(" AND ", Qt::SkipEmptyParts, Qt::CaseInsensitive);
        if (dateParts.size() == 2) {
            int daysStart = dateParts[0].split(" ")[1].toInt(); // Extrait le nombre de jours (début)
            int daysEnd = dateParts[1].split(" ")[0].toInt(); // Extrait le nombre de jours (fin)

            QDateTime now = QDateTime::currentDateTime();
            QString dateStart = now.addDays(-daysStart).toString("yyyy-MM-dd");
            QString dateEnd = now.addDays(-daysEnd).toString("yyyy-MM-dd");

            lastModified = "BETWEEN '" + dateStart + "' AND '" + dateEnd + "'";
        }
    } else if (value.contains("SINCE LAST") || value.contains("AGO")) {
        // TODO: traiter les dates depuis la dernière période

    } else if (key == "LAST_MODIFIED" && value.contains(" DAYS")) {
        qDebug() << "TEST5";
        int days = value.split(" ")[0].toInt();
        QDateTime now = QDateTime::currentDateTime();
        QDateTime modifiedDate = now.addDays(-days);
        QString formattedDate = modifiedDate.toString("yyyy-MM-dd");
        lastModified = formattedDate;
    } else {
        // Traitement des dates au format dd/MM/yyyy
        date = QDateTime::fromString(value, "dd/MM/yyyy");
        if (!date.isValid()) {
            qDebug() << "Invalid date format for" << key;
            return;
        }

        QString formattedDate = date.toString("yyyy-MM-dd");
        if (key == "CREATED") {
            created = formattedDate;
        } else if (key == "LAST_MODIFIED") {
            lastModified = formattedDate;
        }
    }
}



void CmdSearch::parseSizeSpec(const QString& key, const QString& value) {
    qint64 sizeInBytes = convertSizeToBytes(value);

    if (sizeInBytes == -1) {
        qDebug() << "Invalid size format for" << key;
        return;
    }

    if (key == "MAX_SIZE") {
        maxSize = QString::number(sizeInBytes);
    } else if (key == "MIN_SIZE") {
        minSize = QString::number(sizeInBytes);
    } else if (key == "SIZE") {
        sizeRange = value; // La gestion de SIZE nécessitera des modifications supplémentaires
    }
}


void CmdSearch::parseListSpec(const QString& key, const QString& value) {
    QStringList values = value.split(",", Qt::SkipEmptyParts);
    QStringList quotedValues;
    for (const QString &val : values) {
        quotedValues << "'" + val.trimmed() + "'";
    }
    if (key == "EXT") {
        extList = quotedValues.join(", ");
    } else if (key == "TYPE") {
        typeList = quotedValues.join(", ");
    }
}



// Fonction pour analyser la condition de taille
QString CmdSearch::parseSizeCondition() {
    QStringList sizeConditions;
    if (!maxSize.isEmpty()) {
        sizeConditions << "file_size <= " + maxSize;
    }
    if (!minSize.isEmpty()) {
        sizeConditions << "file_size >= " + minSize;
    }
    if (!sizeRange.isEmpty()) {
        QStringList range = sizeRange.split(" AND ");
        if (range.size() == 2) {
            sizeConditions << "file_size BETWEEN " + range[0] + " AND " + range[1];
        }
    }
    return sizeConditions.join(" AND ");
}

qint64 CmdSearch::convertSizeToBytes(const QString& size) {
    QRegularExpression regex("^(\\d+)([KMG])$", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = regex.match(size);

    if (!match.hasMatch()) {
        return -1;
    }

    qint64 value = match.captured(1).toLongLong();
    QString unit = match.captured(2).toUpper();

    if (unit == "K") {
        return value * 1024;
    } else if (unit == "M") {
        return value * 1024 * 1024;
    } else if (unit == "G") {
        return value * 1024 * 1024 * 1024;
    }

    return value;
}


// Fonction pour analyser la condition de date
QString CmdSearch::parseDateCondition(const QString& field, const QString& dateSpec) {
    // logique pour convertir la spécification de date en condition SQL
    if (dateSpec.contains("BETWEEN", Qt::CaseInsensitive)) {
        return field + " " + dateSpec;
    }
    // traitement des spécifications relatives au temps
    else if (dateSpec.contains("SINCE LAST") || dateSpec.contains("AGO")) {
    }
    return field + " = '" + dateSpec + "'";
}

bool CmdSearch::validateDateFormat(const QString& date) {
    qDebug() << "Validating date format:" << date;
    QRegularExpression dateRegex(
        "^(\\d{2}/\\d{2}/\\d{4}|\\d{2}/\\d{4}|\\d{4}|\\d{2}|"
        "SINCE LAST \\d+ (MINUTES|HOURS|DAYS|MONTHS|YEARS)|"
        "\\d+ (MINUTES|HOURS|DAYS|MONTHS|YEARS) AGO|"
        "\\d+\\s+(MINUTES|HOURS|DAYS|MONTHS|YEARS))$",
        QRegularExpression::CaseInsensitiveOption
        );
    return dateRegex.match(date).hasMatch();
}


bool CmdSearch::validateSizeFormat(const QString& size) {
    QRegularExpression sizeRegex("^(\\d+(K|M|G)|BETWEEN \\d+(K|M|G) AND \\d+(K|M|G))$",
                                 QRegularExpression::CaseInsensitiveOption);
    return sizeRegex.match(size).hasMatch();
}

// Méthode pour construire la requête SQL basée sur les critères de recherche
QString CmdSearch::buildSQLQuery() {
    QString query = "SELECT * FROM files";
    QStringList conditions;

    if (!filename.isEmpty()) {
        conditions << "filename LIKE '%" + filename + "%'";
    }
    if (!lastModified.isEmpty()) {
        conditions << parseDateCondition("last_modified", lastModified);
    }
    if (!created.isEmpty()) {
        conditions << "created = '" + created + "'";
    }
    if (!maxSize.isEmpty() || !minSize.isEmpty() || !sizeRange.isEmpty()) {
        conditions << parseSizeCondition();
    }
    if (!extList.isEmpty()) {
        conditions << "file_extension IN (" + extList + ")";
    }
    if (!typeList.isEmpty()) {
        conditions << "file_type IN (" + typeList + ")";
    }

    if (!conditions.isEmpty()) {
        query += " WHERE " + conditions.join(" AND ");
    }
    return query;
}

/** END CmdSearch **/

/** CmdGet class **/

CmdGet::CmdGet() {}

void CmdGet::parse(QList<Token *> tokens) {
    qDebug() << __FUNCTION__ << "on GET" << tokens[1]->text();

    // complete the data
    this->folderType = checkAndGetFolderType(*tokens[1]);

    // then run
    this->run();
}

void CmdGet::run() {
    qDebug() << __FUNCTION__ << "on GET ";
    // create request
    QString command = "SELECT * FROM " + this->folderType;

    executeCommand(command);

}

/** END CmdGet **/

/** CmdAdd class **/

CmdAdd::CmdAdd() {}

void CmdAdd::parse(QList<Token *> tokens) {
    //qDebug() << __FUNCTION__ << "on ADD";

    // complete the data
    this->folderType = checkAndGetFolderType(*tokens[1]);
    this->folderPath = tokens[2]->text();

    // then run
    this->run();
}


void CmdAdd::run() {
    qDebug() << __FUNCTION__ << "on ADD class";

    // create request
    QString command = "INSERT INTO " + this->folderType + " (folderPath) VALUES ('" + this->folderPath + "')";

    executeCommand(command);
}

/** END CmdAdd **/

/** CmdClear class **/

CmdClear::CmdClear() {}

void CmdClear::parse(QList<Token *> tokens) {
    qDebug() << __FUNCTION__ << "on CLEAR" << tokens[1]->text();

    // complete the data
    this->folderType = checkAndGetFolderType(*tokens[1]);

    // then run
    this->run();
}

void CmdClear::run() {
    qDebug() << __FUNCTION__ << "on CLEAR ";
    // create request
    QString command = "DELETE FROM " + this->folderType;

    executeCommand(command);

}

/** END CmdGet **/
