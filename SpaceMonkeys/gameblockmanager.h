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
};

#endif // GAMEBLOCKMANAGER_H
