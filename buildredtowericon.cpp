#include "buildredtowericon.h"
#include "game.h"
#include "browntower.h"
#include "redtower.h"

extern Game * game;

BuildRedTowerIcon::BuildRedTowerIcon(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent)
{
    setPixmap (QPixmap(":/image/tower.png"));
}

void BuildRedTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!game->building)
    {
        game->building = new RedTower();
        game->setCursor (QString(":/image/tower.png"));
    }
}
