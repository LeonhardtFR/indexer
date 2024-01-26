/********************************************************************************
** Form generated from reading UI file 'mainwindow.i'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwindow
{
public:
    QAction *actionA_propos;
    QAction *actionOptions;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_search;
    QLineEdit *lineEdit_query;
    QPushButton *pushButton_search;
    QComboBox *comboBox_filter;
    QTableWidget *tableWidget_results;
    QHBoxLayout *horizontalLayout_directory;
    QLabel *label_directory;
    QLineEdit *lineEdit_directory;
    QPushButton *pushButton_browse;
    QHBoxLayout *horizontalLayout_controls;
    QPushButton *pushButton_startIndexing;
    QPushButton *pushButton_pause;
    QPushButton *pushButton_stopIndexing;
    QProgressBar *progressBar_indexing;
    QMenuBar *menuBar;
    QMenu *menuAide;

    void setupUi(QMainWindow *mainwindow)
    {
        if (mainwindow->objectName().isEmpty())
            mainwindow->setObjectName("mainwindow");
        mainwindow->resize(700, 500);
        actionA_propos = new QAction(mainwindow);
        actionA_propos->setObjectName("actionA_propos");
        actionOptions = new QAction(mainwindow);
        actionOptions->setObjectName("actionOptions");
        centralwidget = new QWidget(mainwindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_search = new QHBoxLayout();
        horizontalLayout_search->setObjectName("horizontalLayout_search");
        lineEdit_query = new QLineEdit(centralwidget);
        lineEdit_query->setObjectName("lineEdit_query");

        horizontalLayout_search->addWidget(lineEdit_query);

        pushButton_search = new QPushButton(centralwidget);
        pushButton_search->setObjectName("pushButton_search");

        horizontalLayout_search->addWidget(pushButton_search);

        comboBox_filter = new QComboBox(centralwidget);
        comboBox_filter->addItem(QString());
        comboBox_filter->addItem(QString());
        comboBox_filter->addItem(QString());
        comboBox_filter->addItem(QString());
        comboBox_filter->addItem(QString());
        comboBox_filter->setObjectName("comboBox_filter");

        horizontalLayout_search->addWidget(comboBox_filter);


        verticalLayout->addLayout(horizontalLayout_search);

        tableWidget_results = new QTableWidget(centralwidget);
        if (tableWidget_results->columnCount() < 5)
            tableWidget_results->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_results->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_results->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_results->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_results->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_results->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget_results->setObjectName("tableWidget_results");
        tableWidget_results->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_results->setColumnCount(5);
        tableWidget_results->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget_results->horizontalHeader()->setMinimumSectionSize(35);
        tableWidget_results->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget_results->verticalHeader()->setCascadingSectionResizes(false);

        verticalLayout->addWidget(tableWidget_results);

        horizontalLayout_directory = new QHBoxLayout();
        horizontalLayout_directory->setObjectName("horizontalLayout_directory");
        label_directory = new QLabel(centralwidget);
        label_directory->setObjectName("label_directory");

        horizontalLayout_directory->addWidget(label_directory);

        lineEdit_directory = new QLineEdit(centralwidget);
        lineEdit_directory->setObjectName("lineEdit_directory");

        horizontalLayout_directory->addWidget(lineEdit_directory);

        pushButton_browse = new QPushButton(centralwidget);
        pushButton_browse->setObjectName("pushButton_browse");

        horizontalLayout_directory->addWidget(pushButton_browse);


        verticalLayout->addLayout(horizontalLayout_directory);

        horizontalLayout_controls = new QHBoxLayout();
        horizontalLayout_controls->setObjectName("horizontalLayout_controls");
        pushButton_startIndexing = new QPushButton(centralwidget);
        pushButton_startIndexing->setObjectName("pushButton_startIndexing");

        horizontalLayout_controls->addWidget(pushButton_startIndexing);

        pushButton_pause = new QPushButton(centralwidget);
        pushButton_pause->setObjectName("pushButton_pause");

        horizontalLayout_controls->addWidget(pushButton_pause);

        pushButton_stopIndexing = new QPushButton(centralwidget);
        pushButton_stopIndexing->setObjectName("pushButton_stopIndexing");

        horizontalLayout_controls->addWidget(pushButton_stopIndexing);

        progressBar_indexing = new QProgressBar(centralwidget);
        progressBar_indexing->setObjectName("progressBar_indexing");

        horizontalLayout_controls->addWidget(progressBar_indexing);


        verticalLayout->addLayout(horizontalLayout_controls);

        mainwindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(mainwindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 700, 21));
        menuAide = new QMenu(menuBar);
        menuAide->setObjectName("menuAide");
        mainwindow->setMenuBar(menuBar);

        menuBar->addAction(menuAide->menuAction());
        menuAide->addAction(actionOptions);
        menuAide->addAction(actionA_propos);

        retranslateUi(mainwindow);

        QMetaObject::connectSlotsByName(mainwindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainwindow)
    {
        mainwindow->setWindowTitle(QCoreApplication::translate("mainwindow", "Indexeur de Fichiers", nullptr));
        actionA_propos->setText(QCoreApplication::translate("mainwindow", "A propos", nullptr));
        actionOptions->setText(QCoreApplication::translate("mainwindow", "Options", nullptr));
        pushButton_search->setText(QCoreApplication::translate("mainwindow", "Rechercher", nullptr));
        comboBox_filter->setItemText(0, QCoreApplication::translate("mainwindow", "Tous les fichiers", nullptr));
        comboBox_filter->setItemText(1, QCoreApplication::translate("mainwindow", "Musiques", nullptr));
        comboBox_filter->setItemText(2, QCoreApplication::translate("mainwindow", "Vid\303\251os", nullptr));
        comboBox_filter->setItemText(3, QCoreApplication::translate("mainwindow", "Images", nullptr));
        comboBox_filter->setItemText(4, QCoreApplication::translate("mainwindow", "Textes", nullptr));

        QTableWidgetItem *___qtablewidgetitem = tableWidget_results->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("mainwindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_results->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("mainwindow", "Chemin", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_results->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("mainwindow", "Modifi\303\251 le", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_results->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("mainwindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_results->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("mainwindow", "Taille", nullptr));
        label_directory->setText(QCoreApplication::translate("mainwindow", "R\303\251pertoire \303\240 indexer :", nullptr));
        pushButton_browse->setText(QCoreApplication::translate("mainwindow", "Parcourir", nullptr));
        pushButton_startIndexing->setText(QCoreApplication::translate("mainwindow", "D\303\251marrer l'indexation", nullptr));
        pushButton_pause->setText(QCoreApplication::translate("mainwindow", "Mettre en pause", nullptr));
        pushButton_stopIndexing->setText(QCoreApplication::translate("mainwindow", "Arr\303\252ter l'indexation", nullptr));
        menuAide->setTitle(QCoreApplication::translate("mainwindow", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainwindow: public Ui_mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
