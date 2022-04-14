#ifndef LOGBOOK_H
#define LOGBOOK_H

#include <QDialog>
#include <string>
#include <map>
#include <QListWidgetItem>

namespace Ui {
class Logbook;
}

class Logbook : public QDialog
{
    Q_OBJECT

public:
    explicit Logbook(QWidget *parent = nullptr);
    ~Logbook();

    void showEntry(std::string);

private:
    Ui::Logbook *ui;
    std::map<std::string, QListWidgetItem*> logMap;

private slots:
    void handleLogChanged(QListWidgetItem* logEntry);
};

#endif // LOGBOOK_H
