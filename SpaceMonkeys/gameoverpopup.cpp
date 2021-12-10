#include "gameoverpopup.h"
#include "ui_gameoverpopup.h"

gameOverPopup::gameOverPopup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameOverPopup)
{
    ui->setupUi(this);
}

gameOverPopup::~gameOverPopup()
{
    delete ui;
}

void gameOverPopup::on_pushButton_clicked()
{
    this->close();
    emit restartClicked();
}

