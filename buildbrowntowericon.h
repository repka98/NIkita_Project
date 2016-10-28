#ifndef BUILDTOWERTWOICON_H
#define BUILDTOWERTWOICON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class BuildTowerTwoIcon : public QGraphicsPixmapItem
{
public:
    BuildTowerTwoIcon(QGraphicsItem * parent = 0);
    void mousePressEvent (QGraphicsSceneMouseEvent *event);
};

#endif // BUILDTOWERTWOICON_H
