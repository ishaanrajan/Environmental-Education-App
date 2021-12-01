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
    QWidget* dragWidget = new QWidget(this);
    dragWidget->setStyleSheet("background-color: #ECF0F1");
    setCentralWidget(dragWidget);

    QVBoxLayout* dragMainLayout = new QVBoxLayout();
    dragWidget->setLayout(dragMainLayout);

    QLabel* title = new QLabel("Build Your Eco City", this);
    dragMainLayout->addWidget(title);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 30pt; margin: 10%;");

    QHBoxLayout* categories = new QHBoxLayout();
    dragMainLayout->addLayout(categories);

    //This is where "category sections" are added to the main window
    QLabel* category1Label = new QLabel("Dirty Energy", this);
    category1Label->setStyleSheet("font-size: 15pt;");
    categories->addWidget(category1Label);

    QLabel* category2Label = new QLabel("Clean Energy", this);
    category2Label->setStyleSheet("font-size: 15pt;");
    categories->addWidget(category2Label);

    QHBoxLayout* layout = new QHBoxLayout();
    dragMainLayout->addLayout(layout);

    category1View = new QListView(this);
    category1View->setDragEnabled(true);
    category1View->setAcceptDrops(true);
    category1View->setDropIndicatorShown(true);
    category1View->setDefaultDropAction(Qt::MoveAction);
    layout->addWidget(category1View);

    category2View = new QListView(this);
    category2View->setDragEnabled(true);
    category2View->setAcceptDrops(true);
    category2View->setDropIndicatorShown(true);
    category2View->setDefaultDropAction(Qt::MoveAction);
    layout->addWidget(category2View);

    category1View->setModel(new QStringListModel());
    category2View->setModel(new QStringListModel());

    category1View->setStyleSheet
            ("QListView { font-size: 20pt; font-weight: bold; }"
             "QListView::item { background-color: #E74C3C; padding: 10%;"
             "border: 1pt solid #C0392B; }"
             "QListView::item::hover {background-color: #C0392B }");

    category2View->setStyleSheet
            ("QListView { font-size: 20pt; font-weight: bold; }"
             "QListView::item { background-color: #2ECC71; padding: 10%;"
             "border: 1pt solid #27AE60; }"
             "QListView::item::hover {background-color: #27AE60 }");

    QToolBar* toolBar = new QToolBar(this);
    addToolBar(toolBar);

    addAction = new QAction(this);
    addAction->setIcon(QIcon(":/new/prefix1/resources/add.png"));
    connect(addAction, &QAction::triggered, this, &MainWindow::onAdd);

    removeAction = new QAction(this);
    removeAction->setIcon(QIcon(":/new/prefix1/resources/delete.png"));
    connect(removeAction, &QAction::triggered, this, &MainWindow::onRemove);

    toolBar->addAction(addAction);
    toolBar->addAction(removeAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAdd()
{
    //This is where instances of category sections are added to respective categories
    category1View->model()->insertRow(category1View->model()->rowCount());
    QModelIndex indexA = category1View->model()->
            index(category1View->model()->rowCount() - 1, 0);
    category1View->edit(indexA); //this is where 'edit: editing failed' is being thrown
}

void MainWindow::onRemove()
{
    QModelIndex indexR = category1View->currentIndex();
    category1View->model()->removeRow(indexR.row());
}

