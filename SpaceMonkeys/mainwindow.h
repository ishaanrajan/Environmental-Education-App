/**
 * This is the MainWindow. This is where all the UI elements
 * and slots are determined.
 * Generated for A9 Educational App in CS 3505, December 2021
 *
 * Authors:
 * Victor Petrov
 * Audrey Miller
 * Ishaan Rajan
 * Mikey Eyer
 * Tanner Watts
*/
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


    /**
     * @brief initParticleManager
     *  Initializes Box2D particle attractors.
     */
    void initParticleManager();

private slots:

    /**
     * @brief on_nextRoundButton_clicked
     * When the NextRound button is clicked, update progress bars, begin particle animation,
     * save buildings placed, and disable the ui.
     */
    void on_nextRoundButton_clicked();

    /**
     * @brief resetGame
     * Reset progress bars, clear City, clear gridblocks.
     */
    void resetGame();

    /**
     * @brief on_buildingSelectionComboBox_currentIndexChanged
     * Display the selected building type.
     */
    void on_buildingSelectionComboBox_currentIndexChanged(int index);

    /**
     * @brief on_resetGameButton_clicked
     * Reset the game.
     */
    void on_resetGameButton_clicked();

private:
    Ui::MainWindow *ui;

    // instance of City -- tracks buildings that have been placed and updates game engine.
    City city;

    // displays when user looses the game
    gameOverPopup gameOverPop;

    // displays instructions when user starts a game
    NewGamePopUp newGamePopUp;

    // displays win popup when player succesfully minimizes environmental impact
    winnerPopUp winnerPopUp;

    // instance of Logbook -- tracks what types of buildings a user has placed, displays environmental impact based on real data
    Logbook logbook;

    // trakcs gameRound
    int gameRound;

    // Contains images from the resources folder used in the game
    std::vector<std::string> images;
    std::vector<std::string> energyImages;
    std::vector<std::string> amenitiesImages;
    std::vector<std::string> housingImages;
    std::vector<std::string> foodImages;

    /**
     * @brief redrawListWidget
     * Redraw the building selector list widget with the images in imageVec
     */
    void redrawListWidget(std::vector<std::string> imageVec);

    // Maps GridTiles to bools to determine if a building has been placed in a given GridTile
    std::map<GridTile *, bool> allGridTiles;

    // A vector of ordered GridTiles
    std::vector<GridTile *> orderedGridTiles;

    // An instance of particleManager
    ParticleManager particleManager;

    // Determines when to stop animating
    bool animLimitReached = false;
    QTimer * animTimer;

    // Prior generated and needed resources
    int priorEnergyGenerated = 0;
    int priorEnergyNeeded = 0;
    int priorAmmenitiesGenerated = 0;
    int priorAmmenitiesNeeded = 0;
    int priorHousingGenerated = 0;
    int priorHousingNeeded = 0;
    int priorFoodGenerated = 0;
    int priorFoodNeeded = 0;
    int priorClimateGenerated = 0;

    // An HTML string that displays and updates the number of actions the user has round to round
    QString actionsFormatString = "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">Actions: %1</span></p></body></html>";

    /**
     * @brief createListOfGameSquares
     * Creates the gameboard.
     */
    void createListOfGameSquares();

    /**
     * @brief checkImpactBounds
     * Checks the current environmental impact and updates the ui background accordingly.
     */
    void checkImpactBounds();

    /**
     * @brief fillBarsToMax
     * Displays the users progress and final state of a round
     */
    void fillBarsToMax();

    /**
     * @brief setBarMaximums
     * Sets maximum values of progress bars based on resources needed to sustain population.
     */
    void setBarMaximums();

    /**
     * @brief fillLabelsToMax
     * Updates text display for progress bar -- magnitude of generated resource / magnitude of resource needed.
     */
    void fillLabelsToMax();
};
#endif // MAINWINDOW_H
