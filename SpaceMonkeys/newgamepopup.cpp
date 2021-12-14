#include "newgamepopup.h"
#include "ui_newgamepopup.h"
#include <QRegularExpression>


NewGamePopUp::NewGamePopUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGamePopUp)
{
    ui->setupUi(this);
    ui->playButton->hide();
    ui->graphicsView_21->hide();
    ui->graphicsView_22->hide();
    ui->graphicsView_41->hide();
    ui->graphicsView_42->hide();
    ui->backButton->setEnabled(false);
    currBrowser = ui->textBrowser_1;
    indexOfBrowser = 0;
    QRegularExpression re("textBrowser_(\\d)");
    QList<QTextBrowser*> allSquares = this->findChildren<QTextBrowser*>(re);
    for(QTextBrowser* currBrowser : allSquares){
        currBrowser->hide();
        instructions.push_back(currBrowser);
    }
    currBrowser->show();
}

NewGamePopUp::~NewGamePopUp()
{
    delete ui;
}

void NewGamePopUp::on_nextButton_clicked()
{
    ui->backButton->setEnabled(true);
    if(indexOfBrowser < 3){
        indexOfBrowser++;
        if(indexOfBrowser == 3){
            ui->nextButton->setEnabled(false);
            ui->graphicsView_41->show();
            ui->graphicsView_42->show();
            ui->graphicsView_21->hide();
            ui->graphicsView_22->hide();
            ui->playButton->show();
        }else if(indexOfBrowser == 2){
            ui->graphicsView_21->show();
            ui->graphicsView_22->show();
        }
        currBrowser->hide();
        currBrowser = instructions.at(indexOfBrowser);
        currBrowser->show();
    }

}


void NewGamePopUp::on_backButton_clicked()
{
    indexOfBrowser--;
    ui->nextButton->setEnabled(true);
    if(indexOfBrowser == 0){
        ui->backButton->setDisabled(true);
    }else if(indexOfBrowser == 2){
        ui->graphicsView_41->hide();
        ui->graphicsView_42->hide();
        ui->graphicsView_21->show();
        ui->graphicsView_22->show();
    }else if (indexOfBrowser == 1){
        ui->graphicsView_21->hide();
        ui->graphicsView_22->hide();
    }
    currBrowser->hide();
    currBrowser = instructions.at(indexOfBrowser);
    currBrowser->show();

}


void NewGamePopUp::on_playButton_clicked()
{
    this->close();
}

