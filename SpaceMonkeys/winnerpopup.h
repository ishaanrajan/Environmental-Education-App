#ifndef WINNERPOPUP_H
#define WINNERPOPUP_H

#include <QDialog>

namespace Ui {
class winnerPopUp;
}

class winnerPopUp : public QDialog
{
    Q_OBJECT

public:
    explicit winnerPopUp(QWidget *parent = nullptr);
    ~winnerPopUp();

private slots:
    void on_playAgainButton_clicked();

signals:
    void playAgainClicked();

private:
    Ui::winnerPopUp *ui;
};

#endif // WINNERPOPUP_H
