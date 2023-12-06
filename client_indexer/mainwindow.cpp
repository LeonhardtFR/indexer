#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connect_server.h"

mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);

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

    connect(socket, &QTcpSocket::readyRead, this, &mainwindow::readServerResponse); // read server response


    // double clic sur un fichier pour l'ouvrir
    connect(ui->tableWidget_results, &QTableWidget::itemDoubleClicked, this, &mainwindow::openFileFromTable);



}

mainwindow::~mainwindow() {
    delete ui;
}

// double clic sur un fichier pour l'ouvrir
void mainwindow::openFileFromTable(QTableWidgetItem *item) {
    int row = item->row();
    QString fullPath = ui->tableWidget_results->item(row, 1)->data(Qt::UserRole).toString();
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

void mainwindow::stop_indexing() {
    // get directory path
    QString directory = get_directory();

    // send event to the server
    emit event_stop();
}


void mainwindow::readServerResponse() {
    QByteArray data = socket->readAll();
    QStringList messages = QString(data).split("\n", Qt::SkipEmptyParts);

    QList<FileInfo> fileResults;

    // reponse séparer en 2 par "/", 1ere partie fichier traité, 2eme partie nombre de fichier total
    // QString response = messages[0];
    // QStringList responseList = response.split("/", Qt::SkipEmptyParts);
    // QString totalFiles = responseList[1];
    // QString fileProcessed = responseList[0];

    // qDebug() << "totalFiles : " << totalFiles.toInt();



    // ui->progressBar_indexing->setMaximum(totalFiles.toInt());
    // ui->progressBar_indexing->setValue(fileProcessed.toInt());

    for (const QString &response : messages) {
        if (response.startsWith("TOTAL_FILES:")) {
            int totalFiles = response.mid(QString("TOTAL_FILES:").length()).toInt();
            ui->progressBar_indexing->setMaximum(totalFiles);
            ui->progressBar_indexing->setValue(0);
        } else if (response.startsWith("PROGRESS_UPDATE:")) {
            int progress = response.mid(QString("PROGRESS_UPDATE:").length()).toInt();
            ui->progressBar_indexing->setValue(progress);
        } else {
            // Supposons que tout ce qui ne commence pas par TOTAL_FILES ou PROGRESS_UPDATE est un chemin de fichier.
            FileInfo fileInfo = FileInfo::fromPath(response);
            fileResults.append(fileInfo);
        }
    }





    qDebug() << "messages.size() : " << messages.size();

    // for (const QString &response : messages) {
    //         FileInfo fileInfo = FileInfo::fromPath(response);
    //         fileResults.append(fileInfo);
    // }

    if (!fileResults.isEmpty()) {
            qDebug() << "fileResults not empty";
        // Si résultats de fichiers, réinitialise la table et ajoute de nouveaux résultats.
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

            itemChemin->setData(Qt::UserRole, fileInfo.fullPath); // stocke chemin complet en tant que donnée

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


