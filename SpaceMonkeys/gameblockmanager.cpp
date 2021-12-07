#include "gameblockmanager.h"
#include <QListWidget>
#include <QDrag>

GameBlockManager::GameBlockManager(QWidget *parent) : QListWidget(parent)
{

}

void GameBlockManager::startDrag(Qt::DropActions supportedActions)
{
    if(supportedActions & Qt::CopyAction)
    {
        QList<QListWidgetItem *> m_items = selectedItems();
        if(m_items.isEmpty())
                return;
        QMimeData *data = mimeData(m_items);
        QDrag *drag = new QDrag(this);
        QPixmap pixmap(":/resources/windfarm.png");
        drag->setPixmap(pixmap);
        drag->setMimeData(data);
        drag->setHotSpot(pixmap.rect().center());
        drag->exec(Qt::CopyAction);
     }
     else
        QListWidget::startDrag(supportedActions);
}
