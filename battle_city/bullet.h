#ifndef BULLET_H
#define BULLET_H
#include "enemy.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet();
    void moveEnemyBullets();
    void enemy_move();
    void setCurrentDirection(int direction) {
        current_player_Direction = direction;
    }

public slots:
    void move();

signals:
    void bulletHitsEnemy(Bullet *bullet, Enemy *Enemy);

private:
    QTimer *timer;
    Enemy *enemy;
    int current_player_Direction;
    int current_tank_Direction;

};

#endif // BULLET_H
