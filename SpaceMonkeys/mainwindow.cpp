#include <QLabel>
#include <QToolBar>
#include <QBoxLayout>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QListView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    images.push_back(":/resources/commercial.png");
    images.push_back(":/resources/drivein.png");
    images.push_back(":/resources/factory1.png");
    images.push_back(":/resources/factory2.png");
    images.push_back(":/resources/highdensityhousing.png");
    images.push_back(":/resources/neighborhood.png");
    images.push_back(":/resources/powerplant.png");
    images.push_back(":/resources/solar.png");
    images.push_back(":/resources/theater.png");
    images.push_back(":/resources/windfarm.png");

    ui->selectStructureListWidget->setAcceptDrops(true);
    ui->selectStructureListWidget->setDragEnabled(true);
    ui->selectStructureListWidget->setDefaultDropAction(Qt::MoveAction);
    ui->selectStructureListWidget->setMaximumWidth(100);
    ui->selectStructureListWidget->setMinimumHeight(300);

    for(QListWidget* currWidgetPtr : gameSquares){
        currWidgetPtr->setAcceptDrops(true);
        currWidgetPtr->setDragEnabled(true);
        currWidgetPtr->setDefaultDropAction(Qt::MoveAction);
    }


    ui->structureSpaceListWidget->setAcceptDrops(true);
    ui->structureSpaceListWidget->setDragEnabled(true);
    ui->structureSpaceListWidget->setDefaultDropAction(Qt::MoveAction);
    ui->structureSpaceListWidget->setMaximumWidth(100);
    ui->structureSpaceListWidget->setMinimumHeight(900);

    for(int i = 0; i < SPRITE_COUNT; i++){
        QPixmap imgPix;
        bool converted = imgPix.convertFromImage(QImage(QString(QString::fromStdString(images.at(i)))));
        QListWidgetItem *itm = new QListWidgetItem;
        itm->setBackground(imgPix);
        itm->setSizeHint(QSize(0, 100));
        ui->selectStructureListWidget->insertItem(i, itm);
    }
//    ui->structureSelectionListView->setDragEnabled(true);
//    ui->structureSelectionListView->setAcceptDrops(true);
//    ui->structureSelectionListView->setDefaultDropAction(Qt::MoveAction);

//    ui->cleanEnergyListView->setDragEnabled(true);
//    ui->cleanEnergyListView->setAcceptDrops(true);
//    ui->cleanEnergyListView->setDefaultDropAction(Qt::MoveAction);

//    ui->cleanEnergyListView->setModel(new QStringListModel());
//    ui->structureSelectionListView->setModel(new QStringListModel());

//    ui->structureSelectionListView->setStyleSheet
//                ("QListView { font-size: 20pt; font-weight: bold; }"
//                 "QListView::item { border-image: url(:/resources/commercial.png);; padding: 10%;"
//                 "border: 1pt solid #C0392B; }");

//    ui->cleanEnergyListView->setStyleSheet
//            ("QListView { font-size: 20pt; font-weight: bold; }"
//                        "QListView::item { background-color: #2ECC71; padding: 10%;"
//                        "border: 1pt solid #27AE60; }"
//                        "QListView::item::hover {background-color: #27AE60 }");

//    ui->structureSelectionListView->model()->insertRows(0,SPRITE_COUNT);
//    for(int i = 0; i < SPRITE_COUNT; i++){
//        QPixmap imgPix;
//        bool converted = imgPix.convertFromImage(QImage(QString(":/resources/commercial.png")));
//        ui->structureSelectionListView->model()->setData(ui->structureSelectionListView->model()->index(i,0),imgPix,Qt::DecorationRole);
//    }
//    QToolBar* toolBar = new QToolBar(this);
//    addToolBar(toolBar);

//    addAction = new QAction(this);
//    addAction->setIcon(QIcon(":/resources/add.png"));
//   // connect(addAction, &QAction::triggered, this, &MainWindow::onAdd);

//    removeAction = new QAction(this);
//    removeAction->setIcon(QIcon(":/resources/delete.png"));
//    connect(removeAction, &QAction::triggered, this, &MainWindow::onRemove);

//    toolBar->addAction(addAction);
//    toolBar->addAction(removeAction);

    ui->funProgressBar->setValue(0);
    ui->funProgressBar->setMinimum(0);
    ui->funProgressBar->setMaximum(100);
    ui->funProgressBar->show();

    ui->foodProgressBar->setValue(0);
    ui->foodProgressBar->setMinimum(0);
    ui->foodProgressBar->setMaximum(100);

    ui->amenitiesProgressBar->setValue(0);
    ui->amenitiesProgressBar->setMinimum(0);
    ui->amenitiesProgressBar->setMaximum(100);

    ui->energyProgressBar->setValue(0);
    ui->energyProgressBar->setMinimum(0);
    ui->energyProgressBar->setMaximum(100);

    ui->environmentalImpactProgressBar->setValue(0);
    ui->environmentalImpactProgressBar->setMinimum(0);
    ui->environmentalImpactProgressBar->setMaximum(100);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAdd()
{
//    //This is where instances of category sections are added to respective categories
//    ui->structureSelectionListView->model()->insertRow(ui->structureSelectionListView->model()->rowCount());
//    QModelIndex indexA = ui->structureSelectionListView->model()->
//            index(ui->structureSelectionListView->model()->rowCount() - 1, 0);
//    ui->structureSelectionListView->edit(indexA); //this is where 'edit: editing failed' is being thrown
}

void MainWindow::onRemove()
{
//    QModelIndex indexR = ui->structureSelectionListView->currentIndex();
//    ui->structureSelectionListView->model()->removeRow(indexR.row());
}

void MainWindow::createListOfGameSquares(){
    gameSquares.push_back(ui->listWidget1_1);
    gameSquares.push_back(ui->listWidget1_2);
    gameSquares.push_back(ui->listWidget1_3);
    gameSquares.push_back(ui->listWidget1_4);
    gameSquares.push_back(ui->listWidget1_5);
    gameSquares.push_back(ui->listWidget1_6);
    gameSquares.push_back(ui->listWidget1_7);
    gameSquares.push_back(ui->listWidget2_1);
    gameSquares.push_back(ui->listWidget2_2);
    gameSquares.push_back(ui->listWidget2_3);
    gameSquares.push_back(ui->listWidget2_4);
    gameSquares.push_back(ui->listWidget2_5);
    gameSquares.push_back(ui->listWidget2_6);
    gameSquares.push_back(ui->listWidget2_7);
    gameSquares.push_back(ui->listWidget3_1);
    gameSquares.push_back(ui->listWidget3_2);
    gameSquares.push_back(ui->listWidget3_4);
    gameSquares.push_back(ui->listWidget3_5);
    gameSquares.push_back(ui->listWidget3_6);
    gameSquares.push_back(ui->listWidget3_7);
    gameSquares.push_back(ui->listWidget4_1);
    gameSquares.push_back(ui->listWidget4_2);
    gameSquares.push_back(ui->listWidget4_3);
    gameSquares.push_back(ui->listWidget4_4);
    gameSquares.push_back(ui->listWidget4_5);
    gameSquares.push_back(ui->listWidget4_6);
    gameSquares.push_back(ui->listWidget4_7);
    gameSquares.push_back(ui->listWidget5_1);
    gameSquares.push_back(ui->listWidget5_2);
    gameSquares.push_back(ui->listWidget5_3);
    gameSquares.push_back(ui->listWidget5_4);
    gameSquares.push_back(ui->listWidget5_5);
    gameSquares.push_back(ui->listWidget5_6);
    gameSquares.push_back(ui->listWidget5_7);
}

