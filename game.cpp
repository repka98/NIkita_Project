#include "game.h"
#include <QGraphicsScene>
#include "bullet.h"
#include "enemy.h"
#include "buildbrowntowericon.h"
#include "buildgreentowericon.h"
#include "buildredtowericon.h"
#include "browntower.h"
#include <QGraphicsLineItem>
#include <QPen>


Game::Game() : QGraphicsView()
{
    scene = new QGraphicsScene(this);

    scene->setSceneRect (0, 0, 800, 600);
    setScene(scene);

    cursor = nullptr;
    building = nullptr;

    setMouseTracking (true);

    setFixedSize (800, 600);
    setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);

    spawnTimer = new QTimer(this);
    enemiesSpawned = 0;
    maxNumberOfEnemies = 0;
    pointsToFollow << QPointF(800, 0) << QPointF(450,450) << QPointF(0,600);

    createEnemies (5);

    createRoad ();

    BuildTowerTwoIcon * tt = new BuildTowerTwoIcon();
    BuildGreenTowerIcon * gt = new BuildGreenTowerIcon();
    BuildRedTowerIcon * rt = new BuildRedTowerIcon();
    gt->setPos (x (), y () + 100);
    rt->setPos (x (), y () + 200);
    scene->addItem (tt);
    scene->addItem (gt);
    scene->addItem (rt);

}

void Game::setCursor(QString filename)
{
    if (cursor)
    {
        scene->removeItem (cursor);
        delete cursor;
    }

    cursor = new QGraphicsPixmapItem();
    cursor->setPixmap (QPixmap(filename));
    scene->addItem (cursor);
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if (cursor)
    {
        cursor->setPos (event->pos ());
    }
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if (building)
    {
       QList<QGraphicsItem *> items = cursor->collidingItems ();
       for (size_t i = 0, n = items.size (); i < n; i++)
       {
           if (dynamic_cast<Tower*>(items[i]))
           {
               return;
           }
       }
       scene->addItem (building);
       building->setPos (event->pos ());
       cursor = nullptr;
       building = nullptr;
    }
    else {
        QGraphicsView::mousePressEvent (event);
    }
}

void Game::createEnemies(int numberOfEnemies)
{
    enemiesSpawned = 0;
    maxNumberOfEnemies = numberOfEnemies;
    connect (spawnTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    spawnTimer->start(1000);
}

void Game::createRoad()
{
    for (size_t i = 0, n = pointsToFollow.size () - 1; i < n; i++)
    {
        QLineF line(pointsToFollow[i], pointsToFollow[i + 1]);
        QGraphicsLineItem * lineItem = new QGraphicsLineItem(line);

        QPen pen;
        pen.setWidth (15);
        pen.setColor (Qt::darkGray);

        lineItem->setPen (pen);
        scene->addItem (lineItem);
    }
}

void Game::spawnEnemy()
{
    Enemy * enemy = new Enemy(pointsToFollow);
    enemy->setPos (pointsToFollow[0]);
    scene->addItem (enemy);
    enemiesSpawned += 1;

    if (enemiesSpawned >= maxNumberOfEnemies)
    {
        spawnTimer->disconnect();
    }
}
