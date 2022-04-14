#include "gameblockmanager.h"
#include <QListWidget>
#include <QDrag>
#include "gameblock.h"
#include <QDropEvent>

GameBlockManager::GameBlockManager(QWidget *parent) : QListWidget(parent)
{

}

void GameBlockManager::setActionsRemaining(int actions)
{
    actionsRemaining = actions;
}

void GameBlockManager::mutateActions(int delta)
{
    actionsRemaining += delta;
}

int GameBlockManager::getActionsRemaining()
{
    return actionsRemaining;
}

void GameBlockManager::startDrag(Qt::DropActions supportedActions)
{
    if(supportedActions & Qt::CopyAction)
    {
        // If no actions left, ignore drag
        if(actionsRemaining == 0){
            return;
        }

        QList<QListWidgetItem*> m_items = selectedItems();
        if(m_items.isEmpty())
                return;
        QMimeData *data = mimeData(m_items);
        QDrag *drag = new QDrag(this);
        GameBlock * gb = dynamic_cast <GameBlock *>(m_items.at(0));
        std::string gbString = ":/resources/" + gb->getType();
        QPixmap pixmap(QString::fromStdString(gbString));
        drag->setPixmap(pixmap);
        drag->setMimeData(data);
        drag->setHotSpot(pixmap.rect().center());
        drag->exec(Qt::CopyAction);

        m_items.at(0)->setSelected(false);
     }
     else{
        QListWidget::startDrag(supportedActions);
    }


}

void GameBlockManager::dropEvent(QDropEvent *event)
{
    event->setDropAction(Qt::DropAction::IgnoreAction);
}

void GameBlockManager::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QList<QListWidgetItem*> m_items = selectedItems();
    if(m_items.isEmpty())
            return;
    GameBlock * gb = dynamic_cast <GameBlock *>(m_items.at(0));
    std::string gbString = ":/resources/" + gb->getType();

    gbString = "QListView::item:selected{background-image: url(" + gbString + ");}";

   this->setStyleSheet(QString::fromStdString(gbString));

    QListView::selectionChanged(selected, deselected);
}
