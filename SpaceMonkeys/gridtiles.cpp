#include "gridtiles.h"
#include <QListView>
#include <QDropEvent>

GridTiles::GridTiles(QWidget *parent) : QListWidget(parent)
{

}

void GridTiles::dropEvent(QDropEvent *event)
{
    if (this->count() == 0)
    {
        QListWidget::dropEvent(event);
    }
}
