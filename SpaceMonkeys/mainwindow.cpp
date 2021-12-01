#include <QLabel>
#include <QToolBar>
#include <QBoxLayout>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->dirtyEnergyListView->setDragEnabled(true);
    ui->dirtyEnergyListView->setAcceptDrops(true);
    ui->dirtyEnergyListView->setDefaultDropAction(Qt::MoveAction);

    ui->cleanEnergyListView->setDragEnabled(true);
    ui->cleanEnergyListView->setAcceptDrops(true);
    ui->cleanEnergyListView->setDefaultDropAction(Qt::MoveAction);

    ui->cleanEnergyListView->setModel(new QStringListModel());
    ui->dirtyEnergyListView->setModel(new QStringListModel());

    ui->dirtyEnergyListView->setStyleSheet
                ("QListView { font-size: 20pt; font-weight: bold; }"
                 "QListView::item { background-color: #E74C3C; padding: 10%;"
                 "border: 1pt solid #C0392B; }"
                 "QListView::item::hover {background-color: #C0392B }");

    ui->cleanEnergyListView->setStyleSheet
            ("QListView { font-size: 20pt; font-weight: bold; }"
                        "QListView::item { background-color: #2ECC71; padding: 10%;"
                        "border: 1pt solid #27AE60; }"
                        "QListView::item::hover {background-color: #27AE60 }");

    QToolBar* toolBar = new QToolBar(this);
    addToolBar(toolBar);

    addAction = new QAction(this);
    addAction->setIcon(QIcon(":/resources/add.png"));
    connect(addAction, &QAction::triggered, this, &MainWindow::onAdd);

    removeAction = new QAction(this);
    removeAction->setIcon(QIcon(":/resources/delete.png"));
    connect(removeAction, &QAction::triggered, this, &MainWindow::onRemove);

    toolBar->addAction(addAction);
    toolBar->addAction(removeAction);

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
    //This is where instances of category sections are added to respective categories
    ui->dirtyEnergyListView->model()->insertRow(ui->dirtyEnergyListView->model()->rowCount());
    QModelIndex indexA = ui->dirtyEnergyListView->model()->
            index(ui->dirtyEnergyListView->model()->rowCount() - 1, 0);
    ui->dirtyEnergyListView->edit(indexA); //this is where 'edit: editing failed' is being thrown
}

void MainWindow::onRemove()
{
    QModelIndex indexR = ui->dirtyEnergyListView->currentIndex();
    ui->dirtyEnergyListView->model()->removeRow(indexR.row());
}

