#include "bullet.h"
#include <QTimer>
#include <qmath.h>
#include <QPixmap>
#include "game.h"

extern Game * game;

Bullet::Bullet(QGraphicsItem *parent) : QObject(),
    QGraphicsPixmapItem(parent)
{
    setPixmap (QPixmap(":/image/arrow.jpg"));

    QTimer * move_timer = new QTimer(this);
    connect (move_timer, SIGNAL(timeout()), this, SLOT(move()));
    move_timer->start (50);

    maxRange = 100;
    distanceTravalled = 0;
}

void Bullet::move()
{
    int STEP_SIZE = 30;
    double theta = rotation ();

    double dy = STEP_SIZE * qSin(qDegreesToRadians (theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians (theta));

    setPos(x () + dx, y () + dy);
}

double Bullet::getMaxRange()
{
    return maxRange;
}

double Bullet::getDistanceTravelled()
{
    return distanceTravalled;
}

void Bullet::setMaxRange(double rng)
{
    maxRange = rng;
}

void Bullet::setDistanceTravelled(double dist)
{
    distanceTravalled = dist;
}
