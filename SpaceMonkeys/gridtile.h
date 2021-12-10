#ifndef GRIDTILE_H
#define GRIDTILE_H

#include <QListWidget>
#include "gameblock.h"

class GridTile : public QListWidget
{
    Q_OBJECT
public:
    explicit GridTile(QWidget *parent = nullptr);

signals:
    void addGameBlock(GameBlock *);

    // QWidget interface
protected:
    void dropEvent(QDropEvent *event) override;
    void startDrag(Qt::DropActions supportedActions);
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
};



#endif // GRIDTILE_H
