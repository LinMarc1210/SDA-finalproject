#include "Enemy.h"
#include <QGraphicsScene>
#include "Bullet.h"

Enemy::Enemy()
{
    moveSpeed = 20; // Default movement speed
    bulletSpeed=10;
    hits=0;
    setPos(rand() % 700, rand() % 500);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemy::move);
    timer->start(500); // fires every 50ms
    moveDistance = 0; // 初始移動距離為0

}

void Enemy::move() {
    setTransformOriginPoint(boundingRect().center());
    if (moveDistance < 60+rand()%400) {
        // 在改變方向後先前進一段距離
        if(currentDirection==Up){
            setPos(x(), y()+moveSpeed);
            current_tank_Direction=4;
            shootBullet();
            moveDistance += moveSpeed; // 更新移動的距離
        }
        if(currentDirection==Down){
            setPos(x(), y()-moveSpeed);
            current_tank_Direction=3;
            shootBullet();
            moveDistance += moveSpeed; // 更新移動的距離
        }
        if(currentDirection==Left){
            setPos(x()-moveSpeed, y());
            current_tank_Direction=1;
            shootBullet();
            moveDistance += moveSpeed; // 更新移動的距離
        }
        if(currentDirection==Right){
            setPos(x()+moveSpeed, y());
            current_tank_Direction=2;
            shootBullet();
            moveDistance += moveSpeed; // 更新移動的距離
        }
    } else {
        switch (rand()%4) {
        case 0:
            setRotation(-90);
            currentDirection=Right;
            break;
        case 1:
            setRotation(90);
            currentDirection=Left;
            break;
        case 2:
            setRotation(180);
            currentDirection=Down;
            break;
        case 3:
            setRotation(0);
            currentDirection=Up;
            break;}
        moveDistance = 0; // 重置移動距離
    }
    if (y() < 0 ||y()  >800||x() < 0||x()  >800) {
        scene()->removeItem(this);
        delete this;
        qDebug() << "Enemy deleted...";
    }
}


void Enemy::shootBullet() {
    Bullet *bullet = new Bullet(bulletSpeed);
   // bullet->setPixmap(QPixmap(":/images/Bullet/bullet.png"));
    switch (currentDirection) {
    case Up://player->x() + player->pixmap().width() / 2 - bullet->pixmap().width() / 2, player->y());
        bullet->setPos(x() + boundingRect().width() / 2 - bullet->boundingRect().width() / 2, y() + boundingRect().height());
        //bullet->setRotation(0);
        break;
    case Down:
        bullet->setPos(x() + boundingRect().width() / 2 - bullet->boundingRect().width() / 2, y() - boundingRect().height());
        //bullet->setRotation(180);
        break;
    case Right:
        //bullet->setRotation(90);
        bullet->setPos(x() + boundingRect().width()+25, y() + boundingRect().width()/2  - bullet->boundingRect().height() /2);
        break;
    case Left:
       // bullet->setRotation(-90);
        bullet->setPos(x() - bullet->boundingRect().width()-25, y() + boundingRect().width()/2  - bullet->boundingRect().height()/2);
        break;
    default:
        break;
    }

    bullet->setCurrentDirection(current_tank_Direction);
    scene()->addItem(bullet);

    QTimer *bulletTimer = new QTimer();
    connect(bulletTimer, &QTimer::timeout, bullet, &Bullet::enemy_move);
    bulletTimer->start(30);
}


