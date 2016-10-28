#include "tower.h"
#include "bullet.h"
#include "game.h"
#include "enemy.h"
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <QLineF>
#include <QTimer>
#include <QGraphicsRectItem>

extern Game * game;

Tower::Tower(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
        QVector<QPointF> points;
    points << QPoint(1,0) << QPoint(2,0) << QPoint(3,1) << QPoint(3,2) << QPoint(2,3) <<
              QPoint(1,3) << QPoint(0,2) << QPoint(0,1);

    int SCALE_FACTOR = 75;

    for (size_t i = 0, n = points.size (); i < n; i++)
    {
        points[i] *= SCALE_FACTOR;
    }

    attack_area = new QGraphicsPolygonItem(QPolygonF(points), this);
    attack_area->setPen (QPen(Qt::DotLine));

    QPointF poly_center(1.5, 1.5);
    poly_center *= SCALE_FACTOR;
    poly_center = mapToScene (poly_center);
    QPointF tower_center(x () + 44, y () + 44);
    QLineF ln(poly_center, tower_center);
    attack_area->setPos (x () + ln.dx (), y () +ln.dy ());

    attack_dest = QPoint(800,0);
    has_target = false;

}

double Tower::distanceTo(QGraphicsItem *item)
{
    QLineF ln(pos (), item->pos ());
    return ln.length ();

}

void Tower::fire()
{
    Bullet * bullet = new Bullet();
    bullet->setPos (x () + 44, y () + 44);

    QLineF ln(QPointF(x () + 44, y () + 44),attack_dest);
    int angle = -1 * ln.angle ();

    bullet->setRotation (angle);
    game->scene->addItem (bullet);
}

void Tower::aquire_target()
{
    QList<QGraphicsItem *> collding_inems = attack_area->collidingItems ();

    has_target = false;

    double clouse_dist = 300;
    QPointF clouset_pt = QPointF(0, 0);
    for (size_t i = 0, n = collding_inems.size (); i < n; i++)
    {
        Enemy * enemy = dynamic_cast<Enemy *>(collding_inems[i]);
        if (enemy)
        {
            double this_dist = distanceTo (collding_inems[i]);
            if (this_dist < clouse_dist)
            {
                clouse_dist = this_dist;
                clouset_pt = collding_inems[i]->pos ();
                has_target = true;
            }
        }

    }

    if (has_target)
    {
        attack_dest = clouset_pt;
        fire();
    }
}
