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

    gameRound = 0;

    ui->statusBarTextBrowser->lower();
    ui->selectStructureListWidget->setAcceptDrops(true);
    ui->selectStructureListWidget->setDragEnabled(true);
    ui->selectStructureListWidget->setDefaultDropAction(Qt::MoveAction);
    ui->selectStructureListWidget->setMaximumWidth(109);
    ui->selectStructureListWidget->setMinimumHeight(300);
    ui->selectStructureListWidget->setStyleSheet("QListWidget{background: rgb(189, 187, 190);border-style: outset;border-width: 2px;border-color: white;color: white;border-radius: 15px;}");
    ui->selectStructureListWidget->raise();

    energyImages.push_back(":/resources/factory1.png");
    energyImages.push_back(":/resources/factory2.png");
    energyImages.push_back(":/resources/nuclear.png");
    energyImages.push_back(":/resources/solar.png");
    energyImages.push_back(":/resources/windfarm.png");

    amenitiesImages.push_back(":/resources/theater.png");
    amenitiesImages.push_back(":/resources/drivein.png");
    amenitiesImages.push_back(":/resources/commercial.png");

    housingImages.push_back(":/resources/highdensityhousing.png");
    housingImages.push_back(":/resources/neighborhood.png");

    foodImages.push_back(":/resources/plantFarm.png");
    foodImages.push_back(":/resources/cowfactory.png");


    for (int i = 0; i < (int)energyImages.size(); i++)
    {
        QPixmap imgPix;
        imgPix.convertFromImage(QImage(QString::fromStdString(energyImages.at(i))).scaled(109,109));
        GameBlock *itm = new GameBlock;
        itm->setBackground(imgPix);
        itm->setSizeHint(QSize(0, 108));
        QString buildingName = QString::fromStdString(energyImages.at(i));
        QString buildingType = QFileInfo(buildingName).baseName();
        itm->setToolTip(buildingType);
        itm->setType(buildingType.toStdString());
        ui->selectStructureListWidget->insertItem(i, itm);
    }

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
        currWidgetPtr->setStyleSheet("QListWidget{background: transparent;border-style: dotted;border-width: 1px;border-color: rgb(77, 172, 63);color: white;border-radius: 1px;}QListWidget::item:selected{background: transparent;}");
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
    ui->environmentalImpactProgressBar->setMaximum(101);


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

    connect(&gameOverPop, &gameOverPopup::restartClicked, this, &MainWindow::resetGame);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createListOfGameSquares(){

    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget1_1, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget1_2, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget1_3, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget1_4, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget1_5, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget1_6, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget1_7, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget2_1, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget2_2, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget2_3, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget2_4, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget2_5, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget2_6, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget2_7, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget3_1, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget3_2, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget3_3, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget3_4, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget3_5, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget3_6, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget3_7, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget4_1, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget4_2, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget4_3, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget4_4, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget4_5, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget4_6, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget4_7, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget5_1, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget5_2, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget5_3, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget5_4, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget5_5, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget5_6, true));
    allGridTiles.insert(std::pair<GridTile *, bool>(ui->listWidget5_7, true));
}


void MainWindow::on_nextRoundButton_clicked()
{
    gameRound += 1;
    for (auto iter = allGridTiles.begin(); iter != allGridTiles.end(); ++iter)
    {
        if(iter->first->itemAt(0,0) && iter->second)
        {
            iter->first->setDragEnabled(false);
            std::string currBlockName = iter->first->itemAt(0,0)->toolTip().toStdString();
            if(currBlockName == "drivein")
                city.addDriveIn();
            else if(currBlockName == "factory1" || currBlockName == "factory2")
                city.addCoalPlant();
            else if(currBlockName == "highdensityhousing")
                city.addHighDensityHousing();
            else if(currBlockName == "neighborhood")
                city.addSuburbanHousing();
            else if(currBlockName == "nuclear")
                city.addNuclear();
            else if(currBlockName == "solar")
                city.addSolar();
            else if(currBlockName == "theater")
                city.addTheater();
            else if(currBlockName == "windfarm")
                city.addWindFarm();
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

    if(ui->environmentalImpactProgressBar->value() > 50 && ui->environmentalImpactProgressBar->value() < 80){
        this->setStyleSheet("QWidget#MainWindow{background-image: url(:/resources/smogbackground1.png);background-position: center;}");
        ui->environmentalImpactProgressBar->setStyleSheet("QProgressBar {border-color: white;border-radius: 5px;border-width: 2px;color: white;}QProgressBar::chunk {background-color: rgb(255, 237, 109);}");
        int trees = 0;
        for(QObject* const currObj : this->children()){
            if(currObj->inherits("QTextBrowser")){
                trees++;
                if(trees % 4){
                    QTextBrowser* currBrowser = (QTextBrowser*)currObj;
                    currBrowser->setStyleSheet("QTextBrowser{background: transparent;}");
                }
            }
        }
    }else if(ui->environmentalImpactProgressBar->value() >= 80 && ui->environmentalImpactProgressBar->value() < 99){
        this->setStyleSheet("QWidget#MainWindow{background-image: url(:/resources/smogbackground2.png);background-position: center;}");
        ui->environmentalImpactProgressBar->setStyleSheet("QProgressBar {border-color: white;border-radius: 5px;border-width: 2px;color: white;}QProgressBar::chunk {background-color: rgb(255, 23, 11);}");
    }else if(ui->environmentalImpactProgressBar->value()  >= 99){
        gameOverPop.show();
        gameOverPop.exec();
    }
    //TODO: add food categories to view
}



void MainWindow::on_buildingSelectionComboBox_currentIndexChanged(int index)
{
    QString currItm =ui->buildingSelectionComboBox->currentText();
    if((currItm.toStdString()) == "Amenities"){
        redrawListWidget(amenitiesImages);
    }else if((currItm.toStdString()) == "Housing"){
        redrawListWidget(housingImages);
    }else if((currItm.toStdString()) == "Energy"){
        redrawListWidget(energyImages);
    } else if((currItm.toStdString()) == "Food"){
        redrawListWidget(foodImages);
    }
}

void MainWindow::redrawListWidget(std::vector<std::string> imageVec){
    ui->selectStructureListWidget->clear();
    for (int i = 0; i < (int)imageVec.size(); i++)
    {
        QPixmap imgPix;
        imgPix.convertFromImage(QImage(QString::fromStdString(imageVec.at(i))).scaled(109,109));
        GameBlock *itm = new GameBlock;
        itm->setBackground(imgPix);
        itm->setSizeHint(QSize(0, 108));
        QString buildingName = QString::fromStdString(imageVec.at(i));
        QString buildingType = QFileInfo(buildingName).baseName();
        itm->setToolTip(buildingType);
        itm->setTextAlignment(Qt::AlignLeft);
        itm->setType(buildingType.toStdString());
        ui->selectStructureListWidget->insertItem(i, itm);
    }
}

void MainWindow::resetGame(){
    City newCity;
    city = newCity;
    this->setStyleSheet("QWidget#MainWindow{background-image: url(:/resources/background.png);background-position: center;}");
    gameRound = 0;
    ui->housingProgressBar->setValue(0);
    ui->foodProgressBar->setValue(0);
    ui->amenitiesProgressBar->setValue(0);
    ui->energyProgressBar->setValue(0);
    ui->environmentalImpactProgressBar->setValue(0);
    ui->environmentalImpactProgressBar->setStyleSheet("QProgressBar {border-color: white;border-radius: 5px;border-width: 2px;color: white;}QProgressBar::chunk {background-color: rgb(89, 163, 72);}");
    ui->housingProgressBar->setStyleSheet("QProgressBar {border-color: white;border-radius: 5px;border-width: 2px;color: white;}QProgressBar::chunk {background-color: rgb(89, 163, 72);}");
    ui->foodProgressBar->setStyleSheet("QProgressBar {border-color: white;border-radius: 5px;border-width: 2px;color: white;}QProgressBar::chunk {background-color: rgb(89, 163, 72);}");
    ui->amenitiesProgressBar->setStyleSheet("QProgressBar {border-color: white;border-radius: 5px;border-width: 2px;color: white;}QProgressBar::chunk {background-color: rgb(89, 163, 72);}");
    ui->energyProgressBar->setStyleSheet("QProgressBar {border-color: white;border-radius: 5px;border-width: 2px;color: white;}QProgressBar::chunk {background-color: rgb(89, 163, 72);}");

    QRegularExpression re("listWidget(\\d)_(\\d)");
    QList<GridTile*> allSquares = centralWidget()->findChildren<GridTile*>(re);
    for(GridTile* currWidgetPtr : allSquares){
        if(currWidgetPtr->itemAt(0,0)){
            currWidgetPtr->clear();
        }
        currWidgetPtr->setAcceptDrops(true);
        currWidgetPtr->setDragEnabled(true);
        currWidgetPtr->setDefaultDropAction(Qt::MoveAction);
        currWidgetPtr->setStyleSheet("QListWidget{background: transparent;border-style: dotted;border-width: 1px;border-color: rgb(77, 172, 63);color: white;border-radius: 1px;}QListWidget::item:selected{background: transparent;}");
    }
}

