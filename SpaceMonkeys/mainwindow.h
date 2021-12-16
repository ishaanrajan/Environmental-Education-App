#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QStringListModel>
#include <box2d/box2d.h>
#include <QListWidget>
#include "particlemanager.h"
#include "gameblock.h"
#include "gridtile.h"
#include "City.h"
#include "gameoverpopup.h"
#include "logbook.h"
#include "newgamepopup.h"
#include "winnerpopup.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void initParticleManager();

private slots:
    void on_nextRoundButton_clicked();
    void resetGame();
    void on_buildingSelectionComboBox_currentIndexChanged(int index);
    void on_resetGameButton_clicked();

signals:
    //void nextRoundBuildingsAdded();

private:
    Ui::MainWindow *ui;
    QListView* category1View = nullptr;
    QListView* category2View = nullptr;
    City city;
    gameOverPopup gameOverPop;
    NewGamePopUp newGamePopUp;
    winnerPopUp winnerPopUp;
    Logbook logbook;

    int gameRound;;

    QAction* addAction = nullptr;
    QAction* removeAction = nullptr;

    int SPRITE_COUNT = 10;
    std::vector<std::string> images;
    std::vector<std::string> energyImages;
    std::vector<std::string> amenitiesImages;
    std::vector<std::string> housingImages;
    std::vector<std::string> foodImages;

    void redrawListWidget(std::vector<std::string> imageVec);


    std::map<GridTile *, bool> allGridTiles;
    std::vector<GridTile *> orderedGridTiles;

    ParticleManager particleManager;
    bool animLimitReached = false;
    QTimer * animTimer;
    int priorEnergyGenerated = 0;
    int priorEnergyNeeded = 0;
    int priorAmmenitiesGenerated = 0;
    int priorAmmenitiesNeeded = 0;
    int priorHousingGenerated = 0;
    int priorHousingNeeded = 0;
    int priorFoodGenerated = 0;
    int priorFoodNeeded = 0;
    int priorClimateGenerated = 0;

    QString actionsFormatString = "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">Actions: %1</span></p></body></html>";

    void createListOfGameSquares();
    void checkImpactBounds();
    void fillBarsToMax();
    void setBarMaximums();
    void fillLabelsToMax();
};
#endif // MAINWINDOW_H
