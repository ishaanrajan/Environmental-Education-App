#include <QLabel>
#include <QBoxLayout>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QListView>
#include <QFileInfo>
#include "gameblock.h"

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

    ui->statusBarTextBrowser->lower();
    ui->selectStructureListWidget->setAcceptDrops(true);
    ui->selectStructureListWidget->setDragEnabled(true);
    ui->selectStructureListWidget->setDefaultDropAction(Qt::MoveAction);
    ui->selectStructureListWidget->setMaximumWidth(109);
    ui->selectStructureListWidget->setMinimumHeight(300);
    ui->selectStructureListWidget->setStyleSheet("QListWidget{background: rgb(189, 187, 190);border-style: outset;border-width: 2px;border-color: white;color: white;border-radius: 15px;}");

    //TODO: This isn't working

    /*Find all game board QListWidgets on the central widget.
     * NOTE: Bugs may appear here if QListWidgets are added
     * that don't represent gameboard pieces.
     */
    QRegularExpression re("listWidget(\\d)_(\\d)");
    QList<QListWidget*> allSquares = centralWidget()->findChildren<QListWidget*>(re);
    for(QListWidget* currWidgetPtr : allSquares){
        currWidgetPtr->setAcceptDrops(true);
        currWidgetPtr->setDragEnabled(true);
        currWidgetPtr->setDefaultDropAction(Qt::MoveAction);
        //connect(currWidgetPtr->model(), &QAbstractListModel::rowsInserted, this, &MainWindow::onAdd);
        currWidgetPtr->setStyleSheet("QListWidget{background: transparent;border-style: dotted;border-width: 2px;border-color: rgb(77, 172, 63);color: white;border-radius: 1px;}QListWidget::item:selected{background: transparent;}");
    }


//    for(int i = 0; i < SPRITE_COUNT; i++){
//        QPixmap imgPix;
//        imgPix.convertFromImage(QImage(QString(QString::fromStdString(images.at(i)))).scaled(109,109));
//        QListWidgetItem *itm = new QListWidgetItem;
//        itm->setBackground(imgPix);
//        itm->setSizeHint(QSize(0, 108));
//        QString buildingType = QFileInfo(QString(QString::fromStdString(images.at(i)))).baseName();
//        itm->setToolTip(buildingType);
//        ui->selectStructureListWidget->insertItem(i, itm);
//    }


    for (int i = 0; i < SPRITE_COUNT; i++)
    {
        QPixmap imgPix;
        imgPix.convertFromImage(QImage(QString::fromStdString(images.at(i))).scaled(109,109));
        GameBlock *itm = new GameBlock;
        itm->setBackground(imgPix);
        itm->setSizeHint(QSize(0, 108));
        QString buildingName = QString::fromStdString(images.at(i));
        QString buildingType = QFileInfo(buildingName).baseName();
        itm->setToolTip(buildingType);
        itm->setType(buildingType.toStdString());
        ui->selectStructureListWidget->insertItem(i, itm);
    }

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


    // TEMP: this is bullshit just to show smoke working
//    connect(ui->genSmokeBtn, &QPushButton::clicked, this, [this](){
//        particleManager.simulate();
//    });

//    particleManager.addSpawner(data::Demands::CLIMATE, 100, 100, 10);
//    particleManager.addSpawner(data::Demands::CLIMATE, 200, 250, 30);
//    particleManager.setAttractionPoint(data::Demands::CLIMATE, 0, 0);
//    particleManager.setWindVec(10.0f, -20.0f);

    ui->graphicsView->setScene(&particleManager.getScene());
    ui->graphicsView->setSceneRect(0, 0, 461, 381);
    ui->graphicsView->setStyleSheet("background: transparent; border: 0px;");
    ui->graphicsView->setAttribute(Qt::WA_TransparentForMouseEvents, true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::onAdd(GameBlock* currGameBlock)
//{
//    //if(currGameBlock->type() == )

//}

void MainWindow::onRemove()
{
    //Not being used at the moment, leaving this here for when we likely do
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

