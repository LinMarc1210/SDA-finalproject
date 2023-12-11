#include "bullet.h"
#include "enemy.h"
#include <QGraphicsScene>
#include <QList>
#include <QGraphicsRectItem>
#include "player.h"
#include "player2.h"

Bullet::Bullet()
{
    setPixmap(QPixmap(":/images/bullet.png"));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(50); // fires every 50ms
}

void Bullet::move() {
    // If the bullet collides with an enemy, destroy both
    QList<QGraphicsItem *> colliding_items = collidingItems();
    foreach (QGraphicsItem *item, colliding_items) {
        Enemy * enemy = dynamic_cast<Enemy*>(item);
        if (enemy) {
            emit bulletHitsEnemy(this, enemy);
            return; // important
        }
    }

    setTransformOriginPoint(boundingRect().center());
    if(current_player_Direction == 1){
        setRotation(-90);
        setPos(x()-10, y());
    }
    else if(current_player_Direction == 2){
        setRotation(90);
        setPos(x()+10, y());
    }
    else if(current_player_Direction == 3){
        setRotation(0);
        setPos(x(), y()-10);
    }
    else if(current_player_Direction == 4){
        setRotation(180);
        setPos(x(), y()+10);
    }


    if (y() + boundingRect().height() < 0) {
        // Remove the bullet from the scene first
        scene()->removeItem(this);
        delete this;
        qDebug() << "Bullet deleted...";
    }
}


void Bullet::enemy_move() {
    // 根据当前旋转方向更新子弹位置
    QList<QGraphicsItem *> colliding_items = collidingItems();
    foreach (QGraphicsItem *item, colliding_items) {
        Player * player = dynamic_cast<Player*>(item);
        if (player) {
            //emit bulletHitsEnemy(this, enemy);
            //scene()->removeItem(player);
            scene()->removeItem(this);
            //delete player;
            delete this;
            return; // important
        }
    }

    QList<QGraphicsItem *> colliding_enemy_items = collidingItems();
    foreach (QGraphicsItem *item, colliding_enemy_items) {
        Enemy * enemy = dynamic_cast<Enemy*>(item);
        if (enemy) {
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    QList<QGraphicsItem *> colliding_player2 = collidingItems();
    foreach (QGraphicsItem *item, colliding_player2) {
        Player2 * player2 = dynamic_cast<Player2*>(item);
        if (player2) {
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    switch (current_tank_Direction) {
    case 1:
        setPos(x()+30, y() );
        break;
    case 2:
        setPos(x()-30, y());
        break;
    case 3:
        setPos(x() , y()+30);
        break;
    case 4:
        setPos(x(), y()-30);
        break;
    default:
        break;
    }
}
