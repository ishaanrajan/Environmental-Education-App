#ifndef GRIDTILES_H
#define GRIDTILES_H

#include <QListWidget>

class GridTiles : public QListWidget
{
    Q_OBJECT
public:
    explicit GridTiles(QWidget *parent = nullptr);

signals:


    // QWidget interface
protected:
    void dropEvent(QDropEvent *event) override;
};



#endif // GRIDTILES_H
