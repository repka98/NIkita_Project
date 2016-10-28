#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include "tower.h"
#include <QTimer>

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game();

    void setCursor (QString filename);

    void mouseMoveEvent (QMouseEvent *event);

    void mousePressEvent (QMouseEvent *event);

    void createEnemies(int numberOfEnemies);

    void createRoad();


    QGraphicsScene * scene;
    QGraphicsPixmapItem * cursor;
    Tower * building;
    QTimer * spawnTimer;
    int enemiesSpawned;
    int maxNumberOfEnemies;
    QList<QPointF> pointsToFollow;

public slots:
    void spawnEnemy();
};

#endif // GAME_H
