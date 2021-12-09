#include "gridtile.h"
#include <QListView>
#include <QDropEvent>
#include <QDrag>

GridTile::GridTile(QWidget *parent) : QListWidget(parent)
{

}

void GridTile::dropEvent(QDropEvent *event)
{
    if (this->count() == 0)
    {
        QListWidget::dropEvent(event);
    }
}

void GridTile::startDrag(Qt::DropActions supportedActions)
{
    if(supportedActions & Qt::CopyAction)
    {
        QList<QListWidgetItem*> m_items = selectedItems();
        if(m_items.isEmpty())
                return;
        QMimeData *data = mimeData(m_items);
        QDrag *drag = new QDrag(this);
        QListWidgetItem * gb = m_items.at(0);
        std::string gbString = ":/resources/" + gb->toolTip().toStdString();
        QPixmap pixmap(QString::fromStdString(gbString));
        drag->setPixmap(pixmap);
        drag->setMimeData(data);
        drag->setHotSpot(pixmap.rect().center());
        drag->exec(Qt::CopyAction);

        m_items.at(0)->setSelected(false);
     }
     else
        QListWidget::startDrag(supportedActions);

    this->clear();
}
