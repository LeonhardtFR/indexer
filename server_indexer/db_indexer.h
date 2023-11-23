#ifndef DB_INDEXER_H
#define DB_INDEXER_H

#include "qsqldatabase.h"
#include <QObject>


class db_indexer : public QObject {
    Q_OBJECT

public:
    static void create_database();
    static QSqlDatabase getDatabaseConnection();

private:

signals:
};

#endif // DB_INDEXER_H
