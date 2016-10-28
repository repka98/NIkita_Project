#include "buildbrowntowericon.h"
#include "game.h"
#include "browntower.h"

extern Game * game;

BuildTowerTwoIcon::BuildTowerTwoIcon(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPixmap (QPixmap(":image/towerTwo.jpg"));
}

void BuildTowerTwoIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!game->building)
    {
        game->building = new BrownTower();
        game->setCursor (QString(":image/towerTwo.jpg"));
    }
}
