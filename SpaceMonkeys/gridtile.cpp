#include "gridtile.h"
#include <QListView>
#include <QDropEvent>

GridTile::GridTile(QWidget *parent) : QListWidget(parent)
{

}

void GridTile::dropEvent(QDropEvent *event)
{
    if (this->count() == 0)
    {
        emit addGameBlock(dynamic_cast<GameBlock *> (event->source()));
        QListWidget::dropEvent(event);
    }
}
