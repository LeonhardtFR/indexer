#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "connect_server.h"
#include <QMainWindow>

#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QProgressBar>
#include <QFileDialog>
#include <QTableWidget>
#include <QDesktopServices>

QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QMainWindow {
    Q_OBJECT

public:
    mainwindow(QWidget *parent = nullptr);
    ~mainwindow();

signals:
    void event_start(QString &directory);
    void event_stop();
    void event_search(QString &query);



private:
    Ui::mainwindow *ui;
    QMetaObject::Connection connectedConnection;
    QTcpSocket *socket;
    int totalFilesCount = -1;

    QTableWidget *tableWidget_results;
    QLineEdit *lineEdit_query;
    QLineEdit *lineEdit_directory;
    QComboBox *comboBox_filter;
    QPushButton *pushButton_search;
    QPushButton *pushButton_browse;
    QPushButton *pushButton_start;
    QPushButton *pushButton_stopIndexing;
    QPushButton *pushButton_pause;
    QProgressBar *progressBar_indexing;

    struct FileInfo {
        QString name;
        QString parentDir;
        QString fullPath;
        QString date;
        QString type;
        QString sizeInMb;

        static FileInfo fromPath(const QString& filePath);
    };

    QString get_query();
    void search();
    void set_directory();
    QString get_directory();
    void start_indexing();
    void stop_indexing();
    connect_server *serverConnection;

    void readServerResponse();
    void handleProgressUpdate(const QString &message);
    void handleTotalFilesUpdate(const QString &message);
    void updateFileResultsTable(const QList<FileInfo> &fileResults);

    void openFileFromTable(QTableWidgetItem *item);


};
#endif // MAINWINDOW_H
