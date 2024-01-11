#ifndef CMD_FACTORY_H
#define CMD_FACTORY_H

#include <QDebug>
#include <QCoreApplication>
#include <QMap>
#include <QString>
#include <token.h>

#define STR_PTR(ptr) QString("0x%1").arg(reinterpret_cast<quintptr>(ptr), QT_POINTER_SIZE * 2, 16, QChar('0'))

class Cmd {
    QString _type;

public:
    virtual ~Cmd() {
        qDebug() << __FUNCTION__;
    }

    virtual void parse(QList<Token *> tokens) = 0;
    virtual void run() = 0;

};

// alias 'CreateCmdFn' pour un pointeur de fonction de type 'Cmd* ma_fonction()'
typedef Cmd *(*CreateCmdFn)();

/**
 * Ce template ou modèle de classe permet de rajouter la méthode statique Create à n'importe quelle classe Cmd
 */
template <class T>
class TCmdFactory : public Cmd {
public:
    static Cmd *create() {
        qDebug() << __FUNCTION__ << "constructs";
        return new T;
    }
};

//#define CREATE_CMD_CLASS(cmd)                                                                                    \
//class cmd : public TCmdFactory<cmd> {}

class CmdSearch : public TCmdFactory<CmdSearch> {

    QString filename;
    QString lastModified;
    QString created;
    QString maxSize;
    QString minSize;
    QString size;
    QString ext;
    QString type;

    public:
    CmdSearch();
    // Attributes


    // Implement virtual method
    void parse(QList<Token *> tokens);
    void run();

};

// CmdGet : on declare la classe et on lui rajoute une méthode 'myFunc'
class CmdGet : public TCmdFactory<CmdGet> {
    QString folderType;
    public:
    CmdGet();
    void get() {
        qDebug() << __FUNCTION__;
    }

    // Implement virtual method
    void parse(QList<Token *> tokens);
    void run();
};

class CmdAdd: public TCmdFactory<CmdAdd> {
    QString folderType;
    QString folderPath;

    public:
    CmdAdd();

    // Implement virtual method
    void parse(QList<Token *> tokens);
    void run();
};

class CmdClear : public TCmdFactory<CmdClear> {
    QString folderType;
public:
    CmdClear();
    void get() {
        qDebug() << __FUNCTION__;
    }

    // Implement virtual method
    void parse(QList<Token *> tokens);
    void run();
};

class CmdFactory {
    QMap<QString, CreateCmdFn> m_factoryMap;

    public:
    QList<Cmd *>               cmdList;
    /**
     * le destructeur doit aussi detruire tous les animaux que la factory a créé
     */
    ~CmdFactory() {
        foreach (auto cmd, cmdList) { delete cmd; }
    }


    /**
     * @brief Register
     * @param cmdName
     * @param fn
     * La fonction register ssocie le nom de la clases Cmd à l'action a effectuer pour la creer
     */
    void Register(QString cmdName, CreateCmdFn fn) {
        qDebug() << __FUNCTION__ << cmdName << fn;
        m_factoryMap[cmdName] = fn;
    }

    /**
     * @brief CmdFactory
     * le constructeur inscrit les classes de command connues
     */
    CmdFactory() {
        qDebug() << __FUNCTION__;
        Register("CmdSearch", &CmdSearch::create);
        Register("CmdGet", &CmdGet::create);
        Register("CmdAdd", &CmdAdd::create);
        Register("CmdClear", &CmdClear::create);
    }

    Cmd *create(QString cmdName) {
        qDebug() << __FUNCTION__ << cmdName;

        // on recupere le pointeur sur fonction de la Map
        CreateCmdFn fn = m_factoryMap[cmdName];
        if (fn == nullptr) {
            //throw AnimalException("Unable to create " + cmdName);
        }
        // on appel la fonction désignée par le pointeur 'fn'
        Cmd *cmd = fn();

        // on le rajoute à la liste des objets de la Factory
        cmdList.append(cmd);
        return cmd;
    }

};

#endif // CMD_FACTORY_H
