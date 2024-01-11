#include "cmd_factory.h"
#include <QCoreApplication>
#include <QDebug>
#include <QMap>
#include <QString>

/** CmdSearch class **/

CmdSearch::CmdSearch() {}

void CmdSearch::parse(QString secondToken) {
    qDebug() << __FUNCTION__ << "on SEARCH";
    // TODO call state chart like this -> stateChart(this)

}

void CmdSearch::run() {
    qDebug() << __FUNCTION__ << "on SEARCH";
}

/** END CmdSearch **/

/** CmdGet class **/

CmdGet::CmdGet() {}

void CmdGet::parse(QString secondToken) {
    qDebug() << __FUNCTION__ << "on GET" << secondToken;

    // complete the data
    this->folderType = secondToken;

    // check if the command is right

    // then run
    this->run();
}

void CmdGet::run() {
    qDebug() << __FUNCTION__ << "on GET class";
    // do request
}

/** END CmdGet **/

/** CmdAdd class **/

CmdAdd::CmdAdd() {}

void CmdAdd::parse(QString secondToken) {
    qDebug() << __FUNCTION__ << "on ADD" << secondToken;

    // complete the data
    this->folderType = secondToken;
    this->folderName = secondToken;

    // check if the command is right

    // then run
    this->run();
}

void CmdAdd::run() {
    qDebug() << __FUNCTION__ << "on ADD class";
    // do request
}

/** END CmdAdd **/
