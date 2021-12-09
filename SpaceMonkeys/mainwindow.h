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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_nextRoundButton_clicked();
    void resetGame();
    void on_buildingSelectionComboBox_currentIndexChanged(int index);

signals:
    //void nextRoundBuildingsAdded();

private:
    Ui::MainWindow *ui;
    QListView* category1View = nullptr;
    QListView* category2View = nullptr;
    City city;
    gameOverPopup gameOverPop;

    int gameRound;;

    QAction* addAction = nullptr;
    QAction* removeAction = nullptr;

    int SPRITE_COUNT = 10;
    std::vector<std::string> images;
    std::vector<std::string> energyImages;
    std::vector<std::string> amenitiesImages;
    std::vector<std::string> housingImages;

    void redrawListWidget(std::vector<std::string> imageVec);


    std::map<GridTile *, bool> allGridTiles;


    ParticleManager particleManager;

    void createListOfGameSquares();
};
#endif // MAINWINDOW_H
