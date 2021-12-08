#include <QLabel>
#include <QBoxLayout>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QListView>
#include <QFileInfo>
#include "gameblock.h"
#include "gridtile.h"
#include <QDebug>
#include <functional>

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

    /*Find all game board QListWidgets on the central widget.
     * NOTE: Bugs may appear here if QListWidgets are added
     * that don't represent gameboard pieces.
     */
    QRegularExpression re("listWidget(\\d)_(\\d)");
    QList<GridTile*> allSquares = centralWidget()->findChildren<GridTile*>(re);
    for(GridTile* currWidgetPtr : allSquares){
        currWidgetPtr->setAcceptDrops(true);
        currWidgetPtr->setDragEnabled(true);
        currWidgetPtr->setDefaultDropAction(Qt::MoveAction);
        currWidgetPtr->setStyleSheet("QListWidget{background: transparent;border-style: dotted;border-width: 2px;border-color: rgb(77, 172, 63);color: white;border-radius: 1px;}QListWidget::item:selected{background: transparent;}");
    }

    //Creating the grid
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

    ui->selectStructureListWidget->setStyleSheet("QListView::item:selected{background-color: rgba(0,0,0,0);}");

    ui->housingProgressBar->setValue(0);
    ui->housingProgressBar->setMinimum(0);
    ui->housingProgressBar->setMaximum(100);
    ui->housingProgressBar->show();

    ui->foodProgressBar->setValue(0);
    ui->foodProgressBar->setMinimum(0);
    ui->foodProgressBar->setMaximum(100);

    ui->amenitiesProgressBar->setValue(0);
    ui->amenitiesProgressBar->setMinimum(0);
    ui->amenitiesProgressBar->setMaximum(100);

    ui->energyProgressBar->setValue(0);
    ui->energyProgressBar->setMinimum(0);
    ui->energyProgressBar->setMaximum(city.getEnergyNeeded());

    ui->environmentalImpactProgressBar->setValue(0);
    ui->environmentalImpactProgressBar->setMinimum(0);
    ui->environmentalImpactProgressBar->setMaximum(100);


    createListOfGameSquares();
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
    gameSquares.push_back(ui->listWidget3_3);
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


void MainWindow::on_nextRoundButton_clicked()
{
    for(GridTile* tile : gameSquares)
    {
        if(tile->itemAt(0,0))
        {
            std::string currBlockName = tile->itemAt(0,0)->toolTip().toStdString();
            if(currBlockName == "drivein")
                city.addDriveIn();
            else if(currBlockName == "factory1" || currBlockName == "factory2")
                city.addCoalPlant();
            else if(currBlockName == "highdensityhousing")
                city.addApartmentHousing();
            else if(currBlockName == "neighborhood")
                city.addSuburbanHousing();
            else if(currBlockName == "powerplant")
                city.addNuclear();
            else if(currBlockName == "solar")
                city.addSolarFarm();
            else if(currBlockName == "theater")
                city.addStadium();
            else if(currBlockName == "windfarm")
                city.addWindMill();
        }

        //Disable game widgets for 5 seconds so we can "play" progressbar animations
        QRegularExpression re("listWidget(\\d)_(\\d)");
        QList<GridTile*> allSquares = centralWidget()->findChildren<GridTile*>(re);
        for(GridTile* currWidgetPtr : allSquares){
            currWidgetPtr->setEnabled(false);
            QTimer::singleShot(5000,currWidgetPtr,std::bind(&QWidget::setEnabled,currWidgetPtr,true));
        }
        ui->genSmokeBtn->setEnabled(false);
        QTimer::singleShot(5000,ui->genSmokeBtn,std::bind(&QWidget::setEnabled,ui->genSmokeBtn,true));

        ui->nextRoundButton->setEnabled(false);
        QTimer::singleShot(5000,ui->nextRoundButton,std::bind(&QWidget::setEnabled,ui->nextRoundButton,true));
    }

    qDebug() << city.getEnergyGenerated();
    ui->energyProgressBar->setValue(city.getEnergyGenerated());
    qDebug() << "FUN GENERATED: " << city.getFunGenerated();
    ui->amenitiesProgressBar->setValue(city.getFunGenerated());
    qDebug() << "HOUSING GENERATED: " << city.getHousingGenerated();
    ui->housingProgressBar->setValue(city.getHousingGenerated());
    qDebug() << "ENVIRONMENTAL IMPACT: " << city.getEnvironmentEffect();
    ui->environmentalImpactProgressBar->setValue(city.getEnvironmentEffect());
    //TODO: add food categories to view
}


