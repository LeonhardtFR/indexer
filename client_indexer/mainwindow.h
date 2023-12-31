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
#include <QKeyEvent>
#include <QMessageBox>


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
    void event_pause();
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

    QComboBox *comboBox_fileTypeFilter; // filtre par type de fichier

    QKeyEvent *event;

    struct FileInfo {
        QString name;
        QString parentDir;
        QString fullPath;
        QString date;
        QString type;
        QString sizeInMb;

        static FileInfo fromPath(const QString& filePath);
    };

    QStringList musicExtensions = {"mp3", "wav", "aac", "flac", "ogg", "wma", "m4a", "aiff", "ape", "alac", "opus", "m4b"};
    QStringList imageExtensions = {"jpg", "jpeg", "png", "gif", "bmp", "webp", "svg", "psd", "ai", "eps", "tif", "tiff", "indd", "raw"};
    QStringList videoExtensions = {"mp4", "avi", "mkv", "mov", "wmv", "flv", "f4v", "f4p", "f4a", "f4b", "webm", "mpeg", "3gp", "3g2", "mxf", "roq", "nsv", "gifv", "qt", "vob", "rm", "rmvb", "ogv", "drc", "mng", "avi", "mts", "m2ts", "ts"};
    QStringList textExtensions = {"txt", "doc", "docx", "pdf", "odt", "rtf", "tex", "wks", "wps", "wpd", "md"};


    QString get_query();
    void search();
    void set_directory();
    QString get_directory();
    void start_indexing();
    void stop_indexing();
    void pause_indexing();

    connect_server *serverConnection;



    void initializeUIElements();
    void initializeConnections();
    void readServerResponse();
    void keyPressEvent(QKeyEvent *event);
    void handleProgressUpdate(const QString &message);
    void handleTotalFilesUpdate(const QString &message);
    void updateFileResultsTable(const QList<FileInfo> &fileResults);

    void filterResults(QString type);

    void openFileFromTable(QTableWidgetItem *item);

private slots:


};
#endif // MAINWINDOW_H
