QT = core
QT += network
QT += sql
QT += scxml

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        cmd_factory.cpp \
        db_indexer.cpp \
        fileindexer_worker.cpp \
        lexer.cpp \
        main.cpp \
        server.cpp \
        token.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    cmd_factory.h \
    db_indexer.h \
    fileindexer_worker.h \
    lexer.h \
    server.h \
    token.h

DISTFILES += \
    dialect_file.json \
    dico.json

STATECHARTS += \
    FSM_indexer.scxml

RESOURCES += \
    ressource.qrc

