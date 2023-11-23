#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connect_server.h"

mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);

//    socket = new QTcpSocket(this); // create socket

//    socket = serverConnection->getSocket();


    // set title
    this->setWindowTitle("Indexation de fichiers");

    // UI elements
    pushButton_browse = ui->pushButton_browse;
    pushButton_start = ui->pushButton_startIndexing;
    pushButton_stopIndexing = ui->pushButton_stopIndexing;
    pushButton_pause = ui->pushButton_pause;
    lineEdit_directory = ui->lineEdit_directory;
    progressBar_indexing = ui->progressBar_indexing;
    pushButton_search = ui->pushButton_search;
    lineEdit_query = ui->lineEdit_query;

    // create a connection with the server
    serverConnection = new connect_server();

    socket = serverConnection->getSocket();

    // connect
    connect(pushButton_browse, &QPushButton::clicked, this, &mainwindow::set_directory); // set directory
    connect(pushButton_start, &QPushButton::clicked, this, &mainwindow::start_indexing);
    connect(pushButton_stopIndexing, &QPushButton::clicked, this, &mainwindow::stop_indexing);
    connect(pushButton_search, &QPushButton::clicked, this, &mainwindow::search);

    connect(this, &mainwindow::event_start, serverConnection, &connect_server::sendStartCommand); // send event to the server for start indexation
    connect(this, &mainwindow::event_stop, serverConnection, &connect_server::sendStopCommand); // send event to the server for stop indexation
    connect(this, &mainwindow::event_search, serverConnection, &connect_server::sendSearchCommand); // send event to the server for search

    connect(socket, &QTcpSocket::readyRead, this, &mainwindow::readServerResponse);



}

mainwindow::~mainwindow() {
    delete ui;
}


QString mainwindow::get_query() {
    return lineEdit_query->text();
}

void mainwindow::search() {
    // get query
    QString query = get_query();

    // send event to the server
    emit event_search(query);
}


void mainwindow::set_directory() {
    QString directoryPath = QFileDialog::getExistingDirectory(this, "Choisir un dossier", "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    lineEdit_directory->setText(directoryPath);
}

QString mainwindow::get_directory() {
    return lineEdit_directory->text();
}

// send event to the server for start indexation
void mainwindow::start_indexing() {
    // get directory path
    QString directory = get_directory();

    // send event to the server
    emit event_start(directory);
}

void mainwindow::stop_indexing() {
    // get directory path
    QString directory = get_directory();

    // send event to the server
    emit event_stop();
}



void mainwindow::readServerResponse() {
    qDebug() << "readServerResponse()";
    QByteArray data = socket->readAll();
    QStringList messages = QString(data).split("\n", Qt::SkipEmptyParts);

    QList<FileInfo> fileResults;

    qDebug() << "messages.size() : " << messages.size();

    for (const QString &response : messages) {
            FileInfo fileInfo = FileInfo::fromPath(response);
            fileResults.append(fileInfo);
    }

    if (!fileResults.isEmpty()) {
            qDebug() << "fileResults not empty";
        // Si nous avons des résultats de fichiers, réinitialisons la table et ajoutons les nouveaux résultats.
        ui->tableWidget_results->setRowCount(0);
        ui->tableWidget_results->setRowCount(fileResults.size());

        for (int i = 0; i < fileResults.size(); ++i) {
            qDebug() << fileResults[i].name;
            const FileInfo &fileInfo = fileResults[i];
            QTableWidgetItem *itemNom = new QTableWidgetItem(fileInfo.name);
            QTableWidgetItem *itemChemin = new QTableWidgetItem(fileInfo.parentDir);
            QTableWidgetItem *itemDate = new QTableWidgetItem(fileInfo.date);
            QTableWidgetItem *itemType = new QTableWidgetItem(fileInfo.type);
            QTableWidgetItem *itemSize = new QTableWidgetItem(fileInfo.sizeInMb);

            itemChemin->setData(Qt::UserRole, fileInfo.fullPath); // stocker le chemin complet en tant que donnée

            ui->tableWidget_results->setItem(i, 0, itemNom); // Colonne "Nom"
            ui->tableWidget_results->setItem(i, 1, itemChemin); // Colonne "Chemin"
            ui->tableWidget_results->setItem(i, 2, itemDate);
            ui->tableWidget_results->setItem(i, 3, itemType);
            ui->tableWidget_results->setItem(i, 4, itemSize);
        }
    }
}

//structure pour les informations du fichier
mainwindow::FileInfo mainwindow::FileInfo::fromPath(const QString& filePath) {
    QFileInfo qFileInfo(filePath);

    FileInfo info;
    info.name = qFileInfo.fileName();
    info.parentDir = qFileInfo.dir().dirName();
    info.fullPath = filePath;
    info.date = qFileInfo.lastModified().toString("dd/MM/yyyy HH:mm:ss");
    info.type = qFileInfo.suffix();
    qint64 sizeInBytes = qFileInfo.size();

    double sizeInMb = sizeInBytes / (1024.0 * 1024.0);
    if (sizeInMb < 0.01) { // Si c'est très petit, affiche en Ko
        double sizeInKb = sizeInBytes / 1024.0;
        info.sizeInMb = QString::number(sizeInKb, 'f', 2) + " Ko";
    } else {
        info.sizeInMb = QString::number(sizeInMb, 'f', 2) + " Mo";
    }

    return info;
}

