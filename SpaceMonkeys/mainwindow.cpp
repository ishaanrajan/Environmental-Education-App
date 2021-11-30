#include <QLabel>
#include <QToolBar>
#include <QBoxLayout>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget* pWidget = new QWidget(this);
    pWidget->setStyleSheet("background-color: #ECF0F1");
    setCentralWidget(pWidget);

    QVBoxLayout* pMainLayout = new QVBoxLayout();
    pWidget->setLayout(pMainLayout);

    QLabel* pTitle = new QLabel("Build Your Eco City", this);
    pMainLayout->addWidget(pTitle);
    pTitle->setAlignment(Qt::AlignCenter);
    pTitle->setStyleSheet("font-size: 30pt; margin: 10%;");

    QHBoxLayout* pHLayoutLabels = new QHBoxLayout();
    pMainLayout->addLayout(pHLayoutLabels);

    QLabel* pLabelPending = new QLabel("Dirty Energy", this);
    pLabelPending->setStyleSheet("font-size: 15pt;");
    pHLayoutLabels->addWidget(pLabelPending);

    QLabel* pLabelCompleted = new QLabel("Clean Energy", this);
    pLabelCompleted->setStyleSheet("font-size: 15pt;");
    pHLayoutLabels->addWidget(pLabelCompleted);

    QHBoxLayout* pHLayout = new QHBoxLayout();
    pMainLayout->addLayout(pHLayout);

    pendingView = new QListView(this);
    pendingView->setDragEnabled(true);
    pendingView->setAcceptDrops(true);
    pendingView->setDropIndicatorShown(true);
    pendingView->setDefaultDropAction(Qt::MoveAction);
    pHLayout->addWidget(pendingView);

    completedView = new QListView(this);
    completedView->setDragEnabled(true);
    completedView->setAcceptDrops(true);
    completedView->setDropIndicatorShown(true);
    completedView->setDefaultDropAction(Qt::MoveAction);
    pHLayout->addWidget(completedView);

    pendingView->setModel(new QStringListModel());
    completedView->setModel(new QStringListModel());

    pendingView->setStyleSheet
            ("QListView { font-size: 20pt; font-weight: bold; }"
             "QListView::item { background-color: #E74C3C; padding: 10%;"
             "border: 1pt solid #C0392B; }"
             "QListView::item::hover {background-color: #C0392B }");

    completedView->setStyleSheet
            ("QListView { font-size: 20pt; font-weight: bold; }"
             "QListView::item { background-color: #2ECC71; padding: 10%;"
             "border: 1pt solid #27AE60; }"
             "QListView::item::hover {background-color: #27AE60 }");

    QToolBar* pToolBar = new QToolBar(this);
    addToolBar(pToolBar);

    addAction = new QAction(this);
    addAction->setIcon(QIcon(":/resources/add.png")); //not showing up for some reason
    connect(addAction, &QAction::triggered, this, &MainWindow::onAdd);

    removeAction = new QAction(this);
    removeAction->setIcon(QIcon(":/resources/delete.png")); //not showing up for some reason
    connect(addAction, &QAction::triggered, this, &MainWindow::onRemove);

    pToolBar->addAction(addAction);
    pToolBar->addAction(removeAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAdd()
{
    pendingView->model()->insertRow(pendingView->model()->rowCount());
    QModelIndex indexA = pendingView->model()->
            index(pendingView->model()->rowCount() - 1, 0);
    pendingView->edit(indexA);
}

void MainWindow::onRemove()
{
    QModelIndex indexR = pendingView->currentIndex();
    pendingView->model()->removeRow(indexR.row());
}

