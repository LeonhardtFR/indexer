#ifndef FILEINDEXER_H
#define FILEINDEXER_H

#include <QObject>
#include "QSqlDatabase"

class fileindexer : public QObject {
    Q_OBJECT

public:
    fileindexer();
    static void indexFile(QString filePath, QString connectionName, QSqlDatabase db);

private:
    void insertFile(QString filePath);


};

#endif // FILEINDEXER_H
