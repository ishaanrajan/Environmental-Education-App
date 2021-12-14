#include "logbook.h"
#include "ui_logbook.h"
#include <QFile>
#include <QTextStream>

Logbook::Logbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Logbook)
{
    ui->setupUi(this);

    QFile f(":resources/template.html");
    QString templateString;
    if (f.open(QFile::ReadOnly | QFile::Text)){
        QTextStream in(&f);
        templateString = in.readAll();
    }

    QFile solarFile(":resources/solar.html");
    solarFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream solarIn(&solarFile);
    QListWidgetItem* solarEntry = new QListWidgetItem("*Solar Farm");
    solarEntry->setData(Qt::UserRole, solarIn.readAll());
    logMap["solar"] = solarEntry;
    ui->logList->addItem(solarEntry);

    QFile coalFile(":resources/coalplant.html");
    coalFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream coalIn(&coalFile);
    QListWidgetItem* coalEntry = new QListWidgetItem("*Coal Plant");
    coalEntry->setData(Qt::UserRole, coalIn.readAll());
    logMap["coalplant"] = coalEntry;
    ui->logList->addItem(coalEntry);

    QFile nuclearFile(":resources/nuclear.html");
    nuclearFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream nucelarIn(&nuclearFile);
    QListWidgetItem* nuclearEntry = new QListWidgetItem("*Nuclear Plant");
    nuclearEntry ->setData(Qt::UserRole, nucelarIn.readAll());
    logMap["nuclear"] = nuclearEntry;
    ui->logList->addItem(nuclearEntry);

    QFile windFile(":resources/wind.html");
    windFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream windIn(&windFile);
    QListWidgetItem* windfarmEntry = new QListWidgetItem("*Wind Farm");
    windfarmEntry->setData(Qt::UserRole, windIn.readAll());
    logMap["windfarm"] = windfarmEntry;
    ui->logList->addItem(windfarmEntry);

    QFile plantFile(":resources/plant.html");
    plantFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream plantIn(&plantFile);
    QListWidgetItem* plantFarmEntry = new QListWidgetItem("*Plant Farm");
    plantFarmEntry->setData(Qt::UserRole, plantIn.readAll());
    logMap["plantFarm"] = plantFarmEntry;
    ui->logList->addItem(plantFarmEntry);

    QFile cowFile(":resources/cow.html");
    cowFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream cowIn(&cowFile);
    QListWidgetItem* cowfactoryEntry = new QListWidgetItem("*Cow Farm");
    cowfactoryEntry->setData(Qt::UserRole, cowIn.readAll());
    logMap["cowfactory"] = cowfactoryEntry;
    ui->logList->addItem(cowfactoryEntry);

    QFile driveFile(":resources/drive.html");
    driveFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream driveIn(&driveFile);
    QListWidgetItem* driveinEntry = new QListWidgetItem("*Drive In");
    driveinEntry->setData(Qt::UserRole, driveIn.readAll());
    logMap["drivein"] = driveinEntry;
    ui->logList->addItem(driveinEntry);

    QFile apartmentFile(":resources/apartment.html");
    apartmentFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream apartmentIn(&apartmentFile);
    QListWidgetItem* highdensityhousingEntry = new QListWidgetItem("*High Density Housing");
    highdensityhousingEntry->setData(Qt::UserRole, templateString);
    logMap["highdensityhousing"] = highdensityhousingEntry;
    ui->logList->addItem(highdensityhousingEntry);

    QListWidgetItem* neighborhoodEntry = new QListWidgetItem("*Suburban Neighborhood");
    neighborhoodEntry->setData(Qt::UserRole, templateString);
    logMap["neighborhood"] = neighborhoodEntry;
    ui->logList->addItem(neighborhoodEntry);

    QListWidgetItem* parkEntry = new QListWidgetItem("*Park");
    parkEntry->setData(Qt::UserRole, templateString);
    logMap["park"] = parkEntry;
    ui->logList->addItem(parkEntry);

    QListWidgetItem* stadiumEntry = new QListWidgetItem("*Stadium");
    stadiumEntry->setData(Qt::UserRole, templateString);
    logMap["stadium"] = stadiumEntry;
    ui->logList->addItem(stadiumEntry);




    solarEntry->setHidden(true);
    coalEntry->setHidden(true);
    driveinEntry->setHidden(true);
    highdensityhousingEntry->setHidden(true);
    neighborhoodEntry->setHidden(true);
    nuclearEntry->setHidden(true);
    parkEntry->setHidden(true);
    windfarmEntry->setHidden(true);
    plantFarmEntry->setHidden(true);
    cowfactoryEntry->setHidden(true);
    stadiumEntry->setHidden(true);

    connect(ui->logList, &QListWidget::itemClicked, this, &Logbook::handleLogChanged);
}

Logbook::~Logbook()
{
    delete ui;
}

void Logbook::showEntry(std::string building)
{
    logMap[building]->setHidden(false);
}

void Logbook::handleLogChanged(QListWidgetItem *logEntry)
{
    QString text = logEntry->text();
    if(text[0] == '*'){
        logEntry->setText(text.right(text.length()-1));
    }
    ui->logBrowser->setText(logEntry->data(Qt::UserRole).toString());
}
