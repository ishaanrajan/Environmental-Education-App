#include "gridblocks.h"
#include <QListView>
#include <QDropEvent>

GridBlocks::GridBlocks(QWidget *parent) : QListWidget(parent)
{

}

void GridBlocks::dropEvent(QDropEvent *event)
{
    if (this->count() == 0)
    {
        QListWidget::dropEvent(event);
    }
}
