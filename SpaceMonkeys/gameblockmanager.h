#ifndef GAMEBLOCKMANAGER_H
#define GAMEBLOCKMANAGER_H

#include <QListWidget>
#include <gameblock.h>

class GameBlockManager : public QListWidget
{

public:
    explicit GameBlockManager(QWidget *parent = nullptr);

    void setActionsRemaining(int actions);

    void mutateActions(int delta);

    int getActionsRemaining();

    // QAbstractItemView interface
protected:
    void startDrag(Qt::DropActions supportedActions);
    void dropEvent(QDropEvent *event);
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
    int actionsRemaining = 4;
};

#endif // GAMEBLOCKMANAGER_H
