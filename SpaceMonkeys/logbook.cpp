#include "logbook.h"
#include "ui_logbook.h"

Logbook::Logbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Logbook)
{
    ui->setupUi(this);

    QListWidgetItem* solarEntry = new QListWidgetItem("*Solar");
    solarEntry->setData(Qt::UserRole, "hello world");
    logMap["solar"] = solarEntry;
    ui->logList->addItem(solarEntry);

    QListWidgetItem* coalEntry = new QListWidgetItem("*Coal Plant");
    coalEntry->setData(Qt::UserRole, "<b>I AM COAL!</b>");
    logMap["coalplant"] = coalEntry;
    ui->logList->addItem(coalEntry);




    solarEntry->setHidden(true);
    coalEntry->setHidden(true);

    connect(ui->logList, &QListWidget::itemClicked, this, &Logbook::handleLogChanged);
}

Logbook::~Logbook()
{
    delete ui;
}

void Logbook::showEntry(std::string building)
{
    logMap[building]->setHidden(false);
}

void Logbook::handleLogChanged(QListWidgetItem *logEntry)
{
    QString text = logEntry->text();
    if(text[0] == '*'){
        logEntry->setText(text.right(text.length()-1));
    }
    ui->logBrowser->setText(logEntry->data(Qt::UserRole).toString());
}
