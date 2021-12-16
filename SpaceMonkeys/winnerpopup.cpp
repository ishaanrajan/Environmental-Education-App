#include "winnerpopup.h"
#include "ui_winnerpopup.h"

winnerPopUp::winnerPopUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::winnerPopUp)
{
    ui->setupUi(this);
}

winnerPopUp::~winnerPopUp()
{
    delete ui;
}

void winnerPopUp::on_playAgainButton_clicked()
{
    this->close();
    emit playAgainClicked();
}

