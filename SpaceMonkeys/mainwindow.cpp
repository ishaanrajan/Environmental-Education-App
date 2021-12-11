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

    amenitiesImages.push_back(":/resources/stadium.png");
    amenitiesImages.push_back(":/resources/drivein.png");
    amenitiesImages.push_back(":/resources/park.png");

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
    ui->housingProgressBar->show();

    ui->foodProgressBar->setValue(0);
    ui->foodProgressBar->setMinimum(0);

    ui->amenitiesProgressBar->setValue(0);
    ui->amenitiesProgressBar->setMinimum(0);

    ui->energyProgressBar->setValue(0);
    ui->energyProgressBar->setMinimum(0);

    setBarMaximums();

    ui->environmentalImpactProgressBar->setValue(0);
    ui->environmentalImpactProgressBar->setMinimum(0);
    ui->environmentalImpactProgressBar->setMaximum(100);


    createListOfGameSquares();

    ui->graphicsView->setScene(&particleManager.getScene());
    ui->graphicsView->setSceneRect(0, 0, 1200, 1000);
    particleManager.getScene().setSceneRect(0, 0, 1200, 1000);
    ui->graphicsView->setStyleSheet("background: transparent; border: 0px;");
    ui->graphicsView->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    ui->actionsLabel->setText(actionsFormatString.arg(QString::number(ui->selectStructureListWidget->getActionsRemaining())));
    fillLabelsToMax(); // to set them up with default city values


    connect(&gameOverPop, &gameOverPopup::restartClicked, this, &MainWindow::resetGame);

    connect(&particleManager, &ParticleManager::particlesReached, this, [this](std::vector<float> percentages){
        // Only do gradual fill up until a given amount of time, then the bars fill fully
        // To prevent stragglers from messing up the bars
        if(!animLimitReached){
            int energyDif = priorEnergyGenerated + (city.getEnergyGenerated()-priorEnergyGenerated) * percentages[data::Demands::ENERGY];
            int amenityDif = priorAmmenitiesGenerated + (city.getAmenitiesGenerated()-priorAmmenitiesGenerated) * percentages[data::Demands::AMMENITIES];
            int housingDif = priorHousingGenerated + (city.getHousingGenerated()-priorHousingGenerated) * percentages[data::Demands::HOUSING];
            int foodDif = priorFoodGenerated + (city.getFoodGenerated()-priorFoodGenerated) * percentages[data::Demands::FOOD];
            int climateDif = priorClimateGenerated + (city.getEnvironmentEffect()-priorClimateGenerated) * percentages[data::Demands::CLIMATE];;

            ui->energyProgressBar->setValue(energyDif < ui->energyProgressBar->maximum() ? energyDif : ui->energyProgressBar->maximum());
            ui->amenitiesProgressBar->setValue(amenityDif < ui->amenitiesProgressBar->maximum() ? amenityDif : ui->amenitiesProgressBar->maximum());
            ui->housingProgressBar->setValue(housingDif < ui->housingProgressBar->maximum() ? housingDif : ui->housingProgressBar->maximum());
            ui->foodProgressBar->setValue(foodDif < ui->foodProgressBar->maximum() ? foodDif : ui->foodProgressBar->maximum());
            ui->environmentalImpactProgressBar->setValue(climateDif < ui->environmentalImpactProgressBar->maximum() ? climateDif : ui->environmentalImpactProgressBar->maximum());

            ui->energy_label->setText("Energy: " + QString::number(energyDif) + "/" + QString::number(priorEnergyNeeded));
            ui->food_label->setText("Food: " + QString::number(foodDif) + "/" + QString::number(priorFoodNeeded));
            ui->housing_label->setText("Housing: " + QString::number(housingDif) + "/" + QString::number(priorHousingNeeded));
            ui->amenities_label->setText("Amenities: " + QString::number(amenityDif) + "/" + QString::number(priorAmmenitiesNeeded));

            //TODO: diagnose why this is slow to do
            //checkImpactBounds();
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

    for(GridTile * tile : orderedGridTiles){
        connect(tile, &GridTile::addGameBlock, this, [this](){
            // Action succeeded, so decrease how many remain
            // Only do here to avoid issue of consuming actions if placement did not take place after drag
            ui->selectStructureListWidget->mutateActions(-1);

            //TODO: animate?
            ui->actionsLabel->setText(actionsFormatString.arg(QString::number(ui->selectStructureListWidget->getActionsRemaining())));
        });
    }
}

void MainWindow::setBarMaximums()
{
    ui->energyProgressBar->setMaximum(city.getEnergyNeeded());
    ui->housingProgressBar->setMaximum(city.getHousingNeeded());
    ui->foodProgressBar->setMaximum(city.getFoodNeeded());
    ui->amenitiesProgressBar->setMaximum(city.getAmenitiesNeeded());
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

    // Setup animation timer
    animTimer = new QTimer(this);
    animTimer->setInterval(7000);
    animTimer->setSingleShot(true);

    connect(animTimer, &QTimer::timeout, [this](){
        this->animLimitReached = true;
        // This fill to max is to show the final state for this round
        fillBarsToMax();
        ui->energy_label->setText("Energy: " + QString::number(city.getEnergyGenerated()) + "/" + QString::number(priorEnergyNeeded));
        ui->food_label->setText("Food: " + QString::number(city.getFoodGenerated()) + "/" + QString::number(priorFoodNeeded));
        ui->housing_label->setText("Housing: " + QString::number(city.getHousingGenerated()) + "/" + QString::number(priorHousingNeeded));
        ui->amenities_label->setText("Amenities: " + QString::number(city.getAmenitiesGenerated()) + "/" + QString::number(priorAmmenitiesNeeded));


        // Give a delay before using the new maximums
        QTimer::singleShot(1000, this, [this](){
            setBarMaximums();
            // Must fill again so that we use the latest fill values with the new maximums
            fillBarsToMax();
            // Now show proportion for new demands
            fillLabelsToMax();
        });
    });
}

void MainWindow::fillBarsToMax()
{
    ui->energyProgressBar->setValue(city.getDemandEnergyGenerated());
    ui->amenitiesProgressBar->setValue(city.getDemandAmenitiesGenerated());
    ui->housingProgressBar->setValue(city.getDemandHousingGenerated());
    ui->foodProgressBar->setValue(city.getDemandFoodGenerated());
    ui->environmentalImpactProgressBar->setValue(city.getEnvironmentEffect());
    checkImpactBounds();
}

void MainWindow::fillLabelsToMax()
{
    ui->energy_label->setText("Energy: " + QString::number(city.getEnergyGenerated()) + "/" + QString::number(city.getEnergyNeeded()));
    ui->amenities_label->setText("Amenities: " + QString::number(city.getAmenitiesGenerated()) + "/" + QString::number(city.getAmenitiesNeeded()));
    ui->food_label->setText("Food: " + QString::number(city.getFoodGenerated()) + "/" + QString::number(city.getFoodNeeded()));
    ui->housing_label->setText("Housing: " + QString::number(city.getHousingGenerated()) + "/" + QString::number(city.getHousingNeeded()));

    // Also show population update
    ui->populationLabel->setText("Pop: " + QString::number(city.getPopulation()));
}

void MainWindow::on_nextRoundButton_clicked()
{
    //animTimer->stop();
    setBarMaximums();
    fillBarsToMax();
    // Now show proportion for new demands
    fillLabelsToMax();

    // Update prior values before adding new tiles
    priorEnergyGenerated = city.getEnergyGenerated();
    priorEnergyNeeded = city.getEnergyNeeded();
    priorAmmenitiesGenerated = city.getAmenitiesGenerated();
    priorAmmenitiesNeeded = city.getAmenitiesNeeded();
    priorFoodGenerated = city.getFoodGenerated();
    priorFoodNeeded = city.getFoodNeeded();
    priorHousingGenerated = city.getHousingGenerated();
    priorHousingNeeded = city.getHousingNeeded();
    priorClimateGenerated = city.getEnvironmentEffect();

    city.resetGeneratedValues();
    // Need to have a city with the current population so bars are right
    //city.updatePopulation(1 + (0.2 * gameRound));

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
            else if(currBlockName == "park")
                city.addPark();
            else if(currBlockName == "windfarm")
                city.addWindFarm();
            else if(currBlockName == "plantFarm")
                city.addPlantFarm();
            else if(currBlockName == "cowfactory")
                city.addCowFactory();
            else if(currBlockName == "stadium")
                city.addStadium();
        }
    }

    // Tally points
    ui->selectStructureListWidget->setActionsRemaining(city.numberDemandsSatisfied());
    ui->actionsLabel->setText(actionsFormatString.arg(QString::number(ui->selectStructureListWidget->getActionsRemaining())));

    // Config particle manager
    particleManager.resetSim();
    // Done after reset so that the scene is cleared and no particles currently simulating
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
    }

    ui->nextRoundButton->setEnabled(false);
    QTimer::singleShot(5000,ui->nextRoundButton,std::bind(&QWidget::setEnabled,ui->nextRoundButton,true));

    ui->resetGameButton->setEnabled(false);
    QTimer::singleShot(5000,ui->resetGameButton,std::bind(&QWidget::setEnabled,ui->resetGameButton,true));

    ui->nextRoundButton->setEnabled(false);
    QTimer::singleShot(5000,ui->nextRoundButton,std::bind(&QWidget::setEnabled,ui->nextRoundButton,true));

    // This will first stop then restart the timer
    // Necessary to stop so that it doesn't suddenly fill to full from a previous round if player goes too fast
    animTimer->start();

    city.updatePopulation(1 + (0.2 * gameRound));
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
    ui->selectStructureListWidget->setActionsRemaining(4);
    ui->actionsLabel->setText(actionsFormatString.arg(QString::number(ui->selectStructureListWidget->getActionsRemaining())));
    fillLabelsToMax();
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
