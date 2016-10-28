#include "buildgreentowericon.h"
#include "game.h"
#include "greentower.h"

extern Game * game;

BuildGreenTowerIcon::BuildGreenTowerIcon(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    setPixmap (QPixmap(":/image/towerThree.jpg"));
}

void BuildGreenTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!game->building)
    {
        game->building = new GreenTower();
        game->setCursor (QString(":/image/towerThree.jpg"));
    }
}

