#ifndef GAMEBLOCKMANAGER_H
#define GAMEBLOCKMANAGER_H

#include <QListWidget>
#include <gameblock.h>

class GameBlockManager : public QListWidget
{

public:
    explicit GameBlockManager(QWidget *parent = nullptr);

    // QAbstractItemView interface
protected:
    void startDrag(Qt::DropActions supportedActions);
    void dropEvent(QDropEvent *event);
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif // GAMEBLOCKMANAGER_H
