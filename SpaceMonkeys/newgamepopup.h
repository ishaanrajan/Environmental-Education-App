#ifndef NEWGAMEPOPUP_H
#define NEWGAMEPOPUP_H

#include <QDialog>
#include <QTextBrowser>

namespace Ui {
class NewGamePopUp;
}

class NewGamePopUp : public QDialog
{
    Q_OBJECT

public:
    explicit NewGamePopUp(QWidget *parent = nullptr);
    ~NewGamePopUp();

public slots:
    void on_nextButton_clicked();
    void on_backButton_clicked();
    void on_playButton_clicked();

private:
    Ui::NewGamePopUp *ui;
    QTextBrowser* currBrowser;
    int indexOfBrowser;
    std::vector<QTextBrowser*> instructions;
};

#endif // NEWGAMEPOPUP_H
