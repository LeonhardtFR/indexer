#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connect_server.h"


mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);
    this->setWindowTitle("Indexation de fichiers");
    initializeUIElements();
    initializeConnections();
    keyPressEvent(event);
}

mainwindow::~mainwindow() {
    delete ui;
}

void mainwindow::initializeUIElements() {
    pushButton_browse = ui->pushButton_browse;
    pushButton_start = ui->pushButton_startIndexing;
    pushButton_stopIndexing = ui->pushButton_stopIndexing;
    pushButton_pause = ui->pushButton_pause;
    lineEdit_directory = ui->lineEdit_directory;
    progressBar_indexing = ui->progressBar_indexing;
    pushButton_search = ui->pushButton_search;
    lineEdit_query = ui->lineEdit_query;
}

void mainwindow::initializeConnections() {
    // create a connection with the server
    serverConnection = new connect_server();

    socket = serverConnection->getSocket();

    // connect
    connect(pushButton_browse, &QPushButton::clicked, this, &mainwindow::set_directory); // set directory
    connect(pushButton_start, &QPushButton::clicked, this, &mainwindow::start_indexing);
    connect(pushButton_stopIndexing, &QPushButton::clicked, this, &mainwindow::stop_indexing);
    connect(pushButton_pause, &QPushButton::clicked, this, &mainwindow::pause_indexing);
    connect(pushButton_search, &QPushButton::clicked, this, &mainwindow::search);

    connect(this, &mainwindow::event_start, serverConnection, &connect_server::sendStartCommand); // send event to the server for start indexation
    connect(this, &mainwindow::event_stop, serverConnection, &connect_server::sendStopCommand); // send event to the server for stop indexation
    connect(this, &mainwindow::event_pause, serverConnection, &connect_server::sendPauseCommand); // send event to the server for pause indexation
    connect(this, &mainwindow::event_search, serverConnection, &connect_server::sendSearchCommand); // send event to the server for search

    connect(socket, &QTcpSocket::readyRead, this, &mainwindow::readServerResponse); // read server response

    // double clic sur un fichier pour l'ouvrir
    connect(ui->tableWidget_results, &QTableWidget::itemDoubleClicked, this, &mainwindow::openFileFromTable);

}

// Raccourci clavier pour la recherche (Enter)
void mainwindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        search();
    }
}


// double clic sur un fichier pour l'ouvrir
void mainwindow::openFileFromTable(QTableWidgetItem *item) {
    int row = item->row();
    QTableWidgetItem *nameItem = ui->tableWidget_results->item(row, 0);
    QString fullPath = nameItem->data(Qt::UserRole).toString();
    QDesktopServices::openUrl(QUrl::fromLocalFile(fullPath));
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

// send event to the server for stop indexation
void mainwindow::stop_indexing() {
    // send event to the server
    emit event_stop();
}

// send event to the server for pause indexation
void mainwindow::pause_indexing() {
    // send event to the server
    emit event_pause();
}


void mainwindow::readServerResponse() {
    QByteArray data = socket->readAll();
    QStringList messages = QString(data).split("\n", Qt::SkipEmptyParts);

    QList<FileInfo> fileResults;

    for (const QString &response : messages) {
        if (response.startsWith("TOTAL_FILES:")) {
            handleTotalFilesUpdate(response);
        } else if (response.startsWith("PROGRESS_UPDATE:")) {
            handleProgressUpdate(response);
        } else {
            FileInfo fileInfo = FileInfo::fromPath(response);
            fileResults.append(fileInfo);
        }
    }

    if (!fileResults.isEmpty()) {
        updateFileResultsTable(fileResults);
    }
}

void mainwindow::handleProgressUpdate(const QString &message) {
    bool ok;
    int progress = message.mid(QString("PROGRESS_UPDATE:").length()).toInt(&ok);
    if (ok) {
        ui->progressBar_indexing->setValue(progress);
    } else {
        // Gérer l'erreur de conversion

    }
}

void mainwindow::handleTotalFilesUpdate(const QString& message) {
    bool ok;
    int totalFiles = message.mid(QString("TOTAL_FILES:").length()).toInt(&ok);
    if (ok && totalFiles != totalFilesCount) { // Vérifier si le total a changé
        totalFilesCount = totalFiles;
        ui->progressBar_indexing->setMaximum(totalFiles);
        ui->progressBar_indexing->setValue(0);
    } else {
        // Gérer l'erreur de conversion ou le cas où le total n'a pas changé
    }
}

void mainwindow::updateFileResultsTable(const QList<FileInfo> &fileResults) {
    ui->tableWidget_results->clearContents();
    ui->tableWidget_results->setRowCount(0);
    ui->tableWidget_results->setRowCount(fileResults.size());

    for (int i = 0; i < fileResults.size(); ++i) {
        const FileInfo &fileInfo = fileResults[i];

        QTableWidgetItem *nameItem = new QTableWidgetItem(fileInfo.name);
        nameItem->setData(Qt::UserRole, fileInfo.fullPath);
        ui->tableWidget_results->setItem(i, 0, nameItem);

        QTableWidgetItem *parentDirItem = new QTableWidgetItem(fileInfo.parentDir);
        ui->tableWidget_results->setItem(i, 1, parentDirItem);

        QTableWidgetItem *dateItem = new QTableWidgetItem(fileInfo.date);
        ui->tableWidget_results->setItem(i, 2, dateItem);

        QTableWidgetItem *typeItem = new QTableWidgetItem(fileInfo.type);
        ui->tableWidget_results->setItem(i, 3, typeItem);

        QTableWidgetItem *sizeItem = new QTableWidgetItem(fileInfo.sizeInMb);
        ui->tableWidget_results->setItem(i, 4, sizeItem);
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
    if (sizeInMb < 0.01) { // si taille du fichier est inférieure à 0.01 Mo on convertie taille en kilo-octets
        double sizeInKb = sizeInBytes / 1024.0;
        info.sizeInMb = QString::number(sizeInKb, 'f', 2) + " Ko"; // formate la taille en Ko avec deux décimales
    } else {
        info.sizeInMb = QString::number(sizeInMb, 'f', 2) + " Mo";
    }

    // si le type du fichier est inconnu alors on affiche "Unknown"
    if (info.type.isEmpty()) {
        info.type = "UNKNOWN";
    } else {
        info.type = info.type.toUpper();
    }

    return info;
}


