#include <QLabel>
#include <QBoxLayout>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QListView>
#include <QFileInfo>

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

    addAction = new QAction(this);
    connect(addAction, &QAction::triggered, this, &MainWindow::onAdd); //TODO: This isn't working

    /*Find all game board QListWidgets on the central widget.
     * NOTE: Bugs may appear here if QListWidgets are added
     * that don't represent gameboard pieces.
     */
    QRegularExpression re("listWidget(\\d)_(\\d)");
    QList<QListWidget*> allSquares = centralWidget()->findChildren<QListWidget*>(re);
    std::cout << "GAME BOARD SIZE : " << allSquares.size() << std::endl; //Debugging purposes -- TODO: Delete
    for(QListWidget* currWidgetPtr : allSquares){
        currWidgetPtr->setAcceptDrops(true);
        currWidgetPtr->setDragEnabled(true);
        currWidgetPtr->setDefaultDropAction(Qt::MoveAction);
        currWidgetPtr->addAction(addAction);
        //currWidgetPtr->setStyleSheet("QListWidget{background: transparent;}QListWidget::item:selected{background: transparent;}");
    }

    for(int i = 0; i < SPRITE_COUNT; i++){
        QPixmap imgPix;
        imgPix.convertFromImage(QImage(QString(QString::fromStdString(images.at(i)))));
        QListWidgetItem *itm = new QListWidgetItem;
        itm->setBackground(imgPix);
        itm->setSizeHint(QSize(0, 100));
        QString buildingType = QFileInfo(QString(QString::fromStdString(images.at(i)))).baseName();
        itm->setToolTip(buildingType);
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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAdd()
{
    std::cout << "ADDED" << std::endl;
    /*I want this slot to set dropEnabled to false. This should be called
     * once the user drops an image into a gameboard piece
     */
}

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
