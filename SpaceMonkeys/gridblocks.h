#ifndef GRIDBLOCKS_H
#define GRIDBLOCKS_H

#include <QListWidget>

class GridBlocks : public QListWidget
{
    Q_OBJECT
public:
    explicit GridBlocks(QWidget *parent = nullptr);

signals:


    // QWidget interface
protected:
    void dropEvent(QDropEvent *event) override;
};



#endif // GRIDBLOCKS_H
