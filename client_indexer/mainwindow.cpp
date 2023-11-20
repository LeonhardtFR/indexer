#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connect_server.h"

mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);

    // set the window title
    this->setWindowTitle("Indexation de fichiers");

    // UI elements
    pushButton_browse = ui->pushButton_browse;
    pushButton_start = ui->pushButton_startIndexing;
    pushButton_stopIndexing = ui->pushButton_stopIndexing;
    pushButton_pause = ui->pushButton_pause;
    lineEdit_directory = ui->lineEdit_directory;
    progressBar_indexing = ui->progressBar_indexing;

    // create a connection with the server
    serverConnection = new connect_server();


    // connect
    connect(pushButton_browse, &QPushButton::clicked, this, &mainwindow::set_directory); // set directory
    connect(pushButton_start, &QPushButton::clicked, this, &mainwindow::start_indexing);
    connect(pushButton_stopIndexing, &QPushButton::clicked, this, &mainwindow::stop_indexing);

    connect(this, &mainwindow::event_start, serverConnection, &connect_server::sendStartCommand); // send event to the server for start indexation
    connect(this, &mainwindow::event_stop, serverConnection, &connect_server::sendStopCommand); // send event to the server for stop indexation

}

mainwindow::~mainwindow() {
    delete ui;
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

