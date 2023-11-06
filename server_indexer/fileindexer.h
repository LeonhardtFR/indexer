#ifndef FILEINDEXER_H
#define FILEINDEXER_H

#include <QObject>
#include "QSqlDatabase"

class fileindexer : public QObject {
    Q_OBJECT

public:
    fileindexer();
    static void indexFile(const QString &directory, QSqlDatabase &db, int &indexedFiles);

private:
    void insertFile(QString filePath);

};

#endif // FILEINDEXER_H
