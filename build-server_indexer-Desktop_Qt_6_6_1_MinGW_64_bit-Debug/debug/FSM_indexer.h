//
// Statemachine code from reading SCXML file 'FSM_indexer.scxml'
// Created by: The Qt SCXML Compiler version 2 (Qt 6.6.1)
// WARNING! All changes made in this file will be lost!
//

#ifndef FSM_INDEXER_H
#define FSM_INDEXER_H

#include <QScxmlStateMachine>
#include <QString>
#include <QVariant>

class FSM_indexer: public QScxmlStateMachine
{
    /* qmake ignore Q_OBJECT */
    Q_OBJECT
    Q_PROPERTY(bool SEARCH)
    Q_PROPERTY(bool SaveValue)
    Q_PROPERTY(bool LAST_MODIFIED)
    Q_PROPERTY(bool CREATED)
    Q_PROPERTY(bool MAX_SIZE)
    Q_PROPERTY(bool MIN_SIZE)
    Q_PROPERTY(bool SIZE)
    Q_PROPERTY(bool EXT)
    Q_PROPERTY(bool TYPE)
    Q_PROPERTY(bool date_spec)
    Q_PROPERTY(bool SINCE_LAST)
    Q_PROPERTY(bool BETWEEN)
    Q_PROPERTY(bool size_spec)
    Q_PROPERTY(bool list_extensions)
    Q_PROPERTY(bool type_list_spec)
    Q_PROPERTY(bool NUMBER)
    Q_PROPERTY(bool VERIF)
    Q_PROPERTY(bool DATE_UNIT)
    Q_PROPERTY(bool DATE)
    Q_PROPERTY(bool SIZE_OPERATOR)
    Q_PROPERTY(bool DATE_OPERATOR)
    Q_PROPERTY(bool AGO)
    Q_PROPERTY(bool SIZE_UNIT)


public:
    Q_INVOKABLE FSM_indexer(QObject *parent = 0);
    ~FSM_indexer();



Q_SIGNALS:


private:
    struct Data;
    friend struct Data;
    struct Data *data;
};

Q_DECLARE_METATYPE(::FSM_indexer*)

#endif // FSM_INDEXER_H
