#include "redtower.h"
#include <QTimer>
#include "bullet.h"
#include "game.h"
#include "tower.h"

extern Game * game;

RedTower::RedTower(QGraphicsItem *parent)
{
    QTimer * timer = new QTimer();
    connect (timer, SIGNAL(timeout()), this, SLOT(aquire_target()));
    timer->start(1000);
}

void RedTower::fire()
{
    Bullet * bullet = new Bullet();
    bullet->setPixmap(QPixmap(":/images/redtowerbullet.png"));
    bullet->setPos(x()+44,y()+44);

    QLineF ln(QPointF(x()+44,y()+44),attack_dest);
    int angle = -1 * ln.angle();

    bullet->setRotation(angle);
    game->scene->addItem(bullet);
}

void RedTower::aquire_target()
{
    Tower::aquire_target();
}
