#ifndef FSM_CHART_H
#define FSM_CHART_H

#include <QObject>

enum class CommandType {
    SEARCH,
    STATUS,
    INDEXER,
    GET,
    ADD,
    PUSH,
    CLEAR
};

enum class TokType{
    COMMAND,
    SEARCH_OPTION,
    UNKNOW
};

class Fsmchart {
public:
    void execFunct(TokType type);
};

#endif // FSM_CHART_H
