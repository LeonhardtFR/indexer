#include "cmd_factory.h"
#include "db_indexer.h"
#include <QCoreApplication>
#include <QDebug>
#include <QMap>
#include <QString>
#include "QSqlDatabase"
#include "QSqlQuery"
#include <QSqlError>

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

    // Test if values are insert
    /*if(query.exec("SELECT * FROM " + this->folderType)) {
        while (query.next()) {
            qDebug() << query.value("folderPath");
        }
    }*/

    db.close();
}

/** CmdSearch class **/
CmdSearch::CmdSearch() {}

void CmdSearch::parse(QList<Token *> tokens) {
    qDebug() << __FUNCTION__ << "on SEARCH";

    QString currentKey;
    QString currentValue;
    bool isValue = false;

    for (Token* token : tokens) {
        QString tokenText = token->text();

        // Vérifier si le token est une clé connue
        if (tokenText == "LAST_MODIFIED" || tokenText == "CREATED" || tokenText == "MAX_SIZE" || tokenText == "MIN_SIZE" || tokenText == "SIZE" || tokenText == "EXT" || tokenText == "TYPE") {
            if (!currentKey.isEmpty() && !currentValue.isEmpty()) {
                // Traiter la paire clé-valeur précédente
                processKeyValue(currentKey, currentValue);

                // Réinitialiser pour la prochaine paire clé-valeur
                currentKey = "";
                currentValue = "";
            }
            currentKey = tokenText;
            isValue = false;
        } else if (tokenText == ":") {
            // Si le token est un deux-points, le prochain token sera une valeur
            isValue = true;
        } else if (isValue) {
            // Accumuler la valeur (pour gérer les valeurs avec espaces)
            if (!currentValue.isEmpty()) {
                currentValue += " ";
            }
            currentValue += tokenText;
        }
    }

    // Traiter la dernière paire clé-valeur si nécessaire
    if (!currentKey.isEmpty() && !currentValue.isEmpty()) {
        processKeyValue(currentKey, currentValue);
    }
}

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



// Gestion des erreurs et des exceptions
void CmdSearch::run() {
    QString sqlQuery = buildSQLQuery();
    if (sqlQuery.isEmpty()) {
        qDebug() << "Requête SQL vide ou invalide";
        return;
    }

    // Exécution de la requête SQL
    executeCommand(sqlQuery);
}

void CmdSearch::parseDateSpec(const QString& key, const QString& value) {
    if (key == "LAST_MODIFIED") {
        lastModified = value;
    } else if (key == "CREATED") {
        created = value;
    }
    // Valider le format de la date
    if (!validateDateFormat(value)) {
        qDebug() << "Invalid date format for" << key;
        return;
    }

    // Ajouter la logique pour traiter différentes spécifications de date
    if (value.contains("BETWEEN")) {
        // Traitement des dates dans une plage
        QStringList dateRange = value.split(" AND ");
        // Vous devez ajouter votre propre logique pour gérer cette plage de dates
    } else if (value.contains("SINCE LAST") || value.contains("AGO")) {
        // Traitement des expressions relatives au temps
        // Vous devez ajouter votre propre logique pour convertir ces expressions en dates concrètes
    }
}

void CmdSearch::parseSizeSpec(const QString& key, const QString& value) {
    if (key == "MAX_SIZE") {
        maxSize = value;
    } else if (key == "MIN_SIZE") {
        minSize = value;
    } else if (key == "SIZE") {
        sizeRange = value;
    }
    // Valider le format de la taille
    if (!validateSizeFormat(value)) {
        qDebug() << "Invalid size format for" << key;
        return;
    }
}

void CmdSearch::parseListSpec(const QString& key, const QString& value) {
    QString modifiedValue = value;
    if (key == "EXT") {
        extList = modifiedValue.replace(" OR ", ", ");
    } else if (key == "TYPE") {
        typeList = modifiedValue.replace(" OR ", ", ");
    }
}

// Fonction pour analyser la condition de taille
QString CmdSearch::parseSizeCondition(const QString& maxSize, const QString& minSize, const QString& sizeRange) {
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

// Fonction pour analyser la condition de date
QString CmdSearch::parseDateCondition(const QString& field, const QString& dateSpec) {
    // Logique pour convertir la spécification de date en condition SQL
    // Exemple de traitement d'une plage de dates
    if (dateSpec.contains("BETWEEN")) {
        QStringList dateRange = dateSpec.split(" AND ");
        if (dateRange.size() == 2) {
            return field + " BETWEEN '" + dateRange[0] + "' AND '" + dateRange[1] + "'";
        }
    }
    // Exemple de traitement des spécifications relatives au temps
    else if (dateSpec.contains("SINCE LAST") || dateSpec.contains("AGO")) {
        // Vous devez ajouter votre propre logique pour convertir ces expressions en dates concrètes
    }
    return field + " = '" + dateSpec + "'"; // Ceci est un exemple simplifié
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
    QRegularExpression sizeRegex("^(\\d+(K|M|G)|BETWEEN \\d+(K|M|G) AND \\d+(K|M|G))$", QRegularExpression::CaseInsensitiveOption);
    return sizeRegex.match(size).hasMatch();
}

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
        conditions << parseDateCondition("created", created);
    }
    if (!maxSize.isEmpty() || !minSize.isEmpty() || !sizeRange.isEmpty()) {
        conditions << parseSizeCondition(maxSize, minSize, sizeRange);
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


// CmdSearch::CmdSearch() {}

// void CmdSearch::parse(QList<Token *> tokens) {
//     qDebug() << __FUNCTION__ << "on SEARCH";
//     // TODO call state chart like this -> stateChart(this)

//     this->fsm_indexer = new FSM_indexer();


//     this->fsm_indexer->connectToState("LAST_MODIFIED", [this](bool active) {
//         qDebug() << "TEST2";
//     });

// }

// void CmdSearch::run() {
//     qDebug() << __FUNCTION__ << "on SEARCH";



// }

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
