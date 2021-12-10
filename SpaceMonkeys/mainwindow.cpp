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
#include <QGridLayout>

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

    energyImages.push_back(":/resources/coalplant.png");
    energyImages.push_back(":/resources/nuclear.png");
    energyImages.push_back(":/resources/solar.png");
    energyImages.push_back(":/resources/windfarm.png");

    amenitiesImages.push_back(":/resources/theater.png");
    amenitiesImages.push_back(":/resources/drivein.png");

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

    ui->selectStructureListWidget->setStyleSheet("QListView::item:selected{background-image: url(:resources/nuclear.png);}");

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

    ui->graphicsView->setScene(&particleManager.getScene());
    ui->graphicsView->setSceneRect(0, 0, 1200, 1000);
    particleManager.getScene().setSceneRect(0, 0, 1200, 1000);
    ui->graphicsView->setStyleSheet("background: transparent; border: 0px;");
    ui->graphicsView->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    connect(&gameOverPop, &gameOverPopup::restartClicked, this, &MainWindow::resetGame);

    connect(&particleManager, &ParticleManager::particlesReached, this, [this](std::vector<float> percentages){
        // Only do gradual fill up until a given amount of time, then the bars fill fully
        // To prevent stragglers from messing up the bars
        if(!animLimitReached){
            ui->energyProgressBar->setValue(city.getEnergyGenerated() * percentages[data::Demands::ENERGY]);
            ui->amenitiesProgressBar->setValue(city.getAmenitiesGenerated() * percentages[data::Demands::AMMENITIES]);
            ui->housingProgressBar->setValue(city.getHousingGenerated() * percentages[data::Demands::HOUSING]);
            ui->foodProgressBar->setValue(city.getFoodGenerated() * percentages[data::Demands::FOOD]);
            ui->environmentalImpactProgressBar->setValue(city.getEnvironmentEffect() * percentages[data::Demands::CLIMATE]);
        }
    });
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

    orderedGridTiles = {ui->listWidget1_1,
                        ui->listWidget1_2,
                        ui->listWidget1_3,
                        ui->listWidget1_4,
                        ui->listWidget1_5,
                        ui->listWidget1_6,
                        ui->listWidget1_7,
                        ui->listWidget2_1,
                        ui->listWidget2_2,
                        ui->listWidget2_3,
                        ui->listWidget2_4,
                        ui->listWidget2_5,
                        ui->listWidget2_6,
                        ui->listWidget2_7,
                        ui->listWidget3_1,
                        ui->listWidget3_2,
                        ui->listWidget3_3,
                        ui->listWidget3_4,
                        ui->listWidget3_5,
                        ui->listWidget3_6,
                        ui->listWidget3_7,
                        ui->listWidget4_1,
                        ui->listWidget4_2,
                        ui->listWidget4_3,
                        ui->listWidget4_4,
                        ui->listWidget4_5,
                        ui->listWidget4_6,
                        ui->listWidget4_7,
                        ui->listWidget5_1,
                        ui->listWidget5_2,
                        ui->listWidget5_3,
                        ui->listWidget5_4,
                        ui->listWidget5_5,
                        ui->listWidget5_6,
                        ui->listWidget5_7};
}


void MainWindow::initParticleManager()
{
    int horizontalOffset = 220;
    int vertOffset = 110;
    particleManager.setAttractionBound(data::Demands::CLIMATE,
                                       ui->environmentalImpactProgressBar->pos().x(), ui->environmentalImpactProgressBar->pos().y(),
                                       ui->environmentalImpactProgressBar->width(), ui->environmentalImpactProgressBar->height());
    particleManager.setAttractionBound(data::Demands::FOOD,
                                       ui->foodProgressBar->pos().x()+horizontalOffset, ui->foodProgressBar->pos().y()+vertOffset,
                                       ui->foodProgressBar->width(), ui->foodProgressBar->height());
    particleManager.setAttractionBound(data::Demands::HOUSING,
                                       ui->housingProgressBar->pos().x()+horizontalOffset, ui->housingProgressBar->pos().y()+vertOffset,
                                       ui->housingProgressBar->width(), ui->housingProgressBar->height());
    particleManager.setAttractionBound(data::Demands::AMMENITIES,
                                       ui->amenitiesProgressBar->pos().x()+horizontalOffset, ui->amenitiesProgressBar->pos().y()+vertOffset,
                                       ui->amenitiesProgressBar->width(), ui->amenitiesProgressBar->height());
    particleManager.setAttractionBound(data::Demands::ENERGY,
                                       ui->energyProgressBar->pos().x()+horizontalOffset, ui->energyProgressBar->pos().y()+vertOffset,
                                       ui->energyProgressBar->width(), ui->energyProgressBar->height());
    particleManager.gridParams(140, 350, ui->listWidget1_1->width(), ui->gameBoardGrid->horizontalSpacing());
}

void MainWindow::on_nextRoundButton_clicked()
{
    city.resetGeneratedValues();
    if(gameRound == 0){
        // Init particle manager bar attractors
        // Must do this here as in constructor positions not yet initialized
        initParticleManager();
    }

    gameRound += 1;
    for (auto iter = allGridTiles.begin(); iter != allGridTiles.end(); ++iter)
    {
        if(iter->first->itemAt(0,0) && iter->second)
        {
            iter->first->setSelectionMode(QAbstractItemView::NoSelection);
            std::string currBlockName = iter->first->itemAt(0,0)->toolTip().toStdString();
            if(currBlockName == "drivein")
                city.addDriveIn();
            else if(currBlockName == "coalplant")
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
            else if(currBlockName == "plantFarm")
                city.addPlantFarm();
            else if(currBlockName == "cowfactory")
                city.addCowFactory();
        }
    }

    // Config particle manager
    particleManager.resetSim();
    // to allow gradual bar fill again
    animLimitReached = false;

    for(size_t tile = 0; tile < orderedGridTiles.size(); tile++){
        if(orderedGridTiles[tile]->itemAt(0,0) && allGridTiles[orderedGridTiles[tile]]){
            std::string currBlockName = orderedGridTiles[tile]->itemAt(0,0)->toolTip().toStdString();
            int gridX = tile % 7 + 1;
            int gridY = tile / 7 + 1;
            particleManager.addTile(currBlockName, gridX, gridY);
            // There needs to be some way to get what the values added by each thing are, if they are modified
            // by adjacency for instance
            //ex: TileMod m = city.addCityBlock();
            //then: addSpawner(int x, int y, m); //can now setup spawner quantites properly
        }
    }

    particleManager.simulate();

    //Disable game widgets for 5 seconds so we can "play" progressbar animations
    QRegularExpression re("listWidget(\\d)_(\\d)");
    QList<GridTile*> allSquares = centralWidget()->findChildren<GridTile*>(re);
    for(GridTile* currWidgetPtr : allSquares){
        currWidgetPtr->setEnabled(false);
        QTimer::singleShot(5000,currWidgetPtr,std::bind(&QWidget::setEnabled,currWidgetPtr,true));

        ui->nextRoundButton->setEnabled(false);
        QTimer::singleShot(5000,ui->nextRoundButton,std::bind(&QWidget::setEnabled,ui->nextRoundButton,true));

        ui->resetGameButton->setEnabled(false);
        QTimer::singleShot(5000,ui->resetGameButton,std::bind(&QWidget::setEnabled,ui->resetGameButton,true));
    }

    ui->nextRoundButton->setEnabled(false);
    QTimer::singleShot(5000,ui->nextRoundButton,std::bind(&QWidget::setEnabled,ui->nextRoundButton,true));

    // Ensure that after 5 seconds the bars are completely full regardless of whether the animation is still goin
    QTimer::singleShot(5000, this, [this](){
        this->animLimitReached = true;
        ui->energyProgressBar->setValue(city.getEnergyGenerated());
        ui->amenitiesProgressBar->setValue(city.getAmenitiesGenerated());
        ui->housingProgressBar->setValue(city.getHousingGenerated());
        ui->foodProgressBar->setValue(city.getFoodGenerated());
        ui->environmentalImpactProgressBar->setValue(city.getEnvironmentEffect());
        checkImpactBounds();
    });
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
    particleManager.resetSim();
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
    QRegularExpression re2("textBrowser_(\\d)");
    QList<QTextBrowser*> allTrees = centralWidget()->findChildren<QTextBrowser*>(re2);
    for(QTextBrowser* currBrowser : allTrees){
         currBrowser->setStyleSheet("QTextBrowser{border-image: url(:resources/trees.png);}");
    }
}

void MainWindow::checkImpactBounds()
{
    if(ui->environmentalImpactProgressBar->value() > 50 && ui->environmentalImpactProgressBar->value() < 80){
        this->setStyleSheet("QWidget#MainWindow{background-image: url(:/resources/smogbackground1.png);background-position: center;}");
        ui->environmentalImpactProgressBar->setStyleSheet("QProgressBar {border-color: white;border-radius: 5px;border-width: 2px;color: white;}QProgressBar::chunk {background-color: rgb(255, 237, 109);}");
        int trees = 0;
        QRegularExpression re("textBrowser_(\\d)");
        QList<QTextBrowser*> allSquares = centralWidget()->findChildren<QTextBrowser*>(re);
        for(QTextBrowser* currBrowser : allSquares){
            trees++;
            if(trees % 3){
                currBrowser->setStyleSheet("QTextBrowser{background: transparent;}");
           }
        }
    }else if(ui->environmentalImpactProgressBar->value() >= 80 && ui->environmentalImpactProgressBar->value() < 99){
        this->setStyleSheet("QWidget#MainWindow{background-image: url(:/resources/smogbackground2.png);background-position: center;}");
        ui->environmentalImpactProgressBar->setStyleSheet("QProgressBar {border-color: white;border-radius: 5px;border-width: 2px;color: white;}QProgressBar::chunk {background-color: rgb(255, 23, 11);}");
        int trees = 0;
        QRegularExpression re("textBrowser_(\\d)");
        QList<QTextBrowser*> allSquares = centralWidget()->findChildren<QTextBrowser*>(re);
        for(QTextBrowser* currBrowser : allSquares){
            trees++;
            if(trees % 5){
                currBrowser->setStyleSheet("QTextBrowser{background: transparent;}");
           }
        }
    }else if(ui->environmentalImpactProgressBar->value()  >= 100){
        this->setStyleSheet("QWidget#MainWindow{background-image: url(:/resources/smogbackground2.png);background-position: center;}");
        ui->environmentalImpactProgressBar->setStyleSheet("QProgressBar {border-color: white;border-radius: 5px;border-width: 2px;color: white;}QProgressBar::chunk {background-color: rgb(255, 23, 11);}");
        gameOverPop.show();
        gameOverPop.exec();
    }
}


void MainWindow::on_resetGameButton_clicked()
{
    if(gameOverPop.isActiveWindow())
    {
        gameOverPop.close();
    }
    resetGame();
}
