#ifndef GAMEOVERPOPUP_H
#define GAMEOVERPOPUP_H

#include <QDialog>

namespace Ui {
class gameOverPopup;
}

class gameOverPopup : public QDialog
{
    Q_OBJECT

public:
    explicit gameOverPopup(QWidget *parent = nullptr);
    ~gameOverPopup();

private:
    Ui::gameOverPopup *ui;
};

#endif // GAMEOVERPOPUP_H
