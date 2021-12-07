#ifndef GRIDTILE_H
#define GRIDTILE_H

#include <QListWidget>

class GridTile : public QListWidget
{
    Q_OBJECT
public:
    explicit GridTile(QWidget *parent = nullptr);

signals:


    // QWidget interface
protected:
    void dropEvent(QDropEvent *event) override;
};



#endif // GRIDTILE_H
