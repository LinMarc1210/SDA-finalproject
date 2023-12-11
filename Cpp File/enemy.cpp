#include "enemy.h"
#include <QGraphicsScene>
#include "bullet.h"
Enemy::Enemy()
{
    setPos(rand() % 700, rand() % 500);
    /*switch(rand()%4)
    {
    case 0:
        tanktype = Tanktype::BASIC;
        setPixmap(QPixmap(":/images/basic_tank.png"));
        break;
    case 1:
        tanktype = Tanktype::FAST;
        setPixmap(QPixmap(":/images/fast_tank.png"));
        break;
    case 2:
        tanktype = Tanktype::POWER;
        setPixmap(QPixmap(":/images/power_tank.png"));
        break;
    case 3:
        tanktype = Tanktype::ARMOR;
        setPixmap(QPixmap(":/images/armor_tank.png"));
        break;

    }*/

    setPixmap(QPixmap(":/images/basic_tank.png"));

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
            setPos(x(), y()+50);
            current_tank_Direction=4;
            shootBullet();
            moveDistance += 50; // 更新移動的距離
        }
        if(currentDirection==Down){
            setPos(x(), y()-50);
            current_tank_Direction=3;
            shootBullet();
            moveDistance += 50; // 更新移動的距離
        }
        if(currentDirection==Left){
            setPos(x()-50, y());
            current_tank_Direction=1;
            shootBullet();
            moveDistance += 50; // 更新移動的距離
        }
        if(currentDirection==Right){
            setPos(x()+50, y());
            current_tank_Direction=2;
            shootBullet();
            moveDistance += 50; // 更新移動的距離
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
            setRotation(0);
            currentDirection=Up;
            break;
        case 3:
            setRotation(180);
            currentDirection=Down;
            break;}
        moveDistance = 0; // 重置移動距離
    }

    if (y() > 600 || y()<0 ||x()<0||x()>800) {
        emit enemyHitsTheGround(this);
//        // Remove the bullet from the scene first
//        scene()->removeItem(this);
//        delete this;
//        qDebug() << "Bullet deleted...";
    }
}


void Enemy::shootBullet() {
    Bullet *bullet = new Bullet();
    // 设置子弹图像和初始位置
    bullet->setPixmap(QPixmap(":/images/bullet.png"));
    // 根据子弹的方向设置移动方向
    /*
    switch (currentDirection) {
    case Up:
        bullet->setPos(x()+15, y()+110);
        bullet->setRotation(0);
        break;
    case Down:
        bullet->setPos(x()+10, y()-70);
        bullet->setRotation(180);
        break;
    case Left:
        bullet->setPos(x()-30, y()+5);
        bullet->setRotation(90);
        break;
    case Right:
        bullet->setPos(x()+90, y()+10);
        bullet->setRotation(-90);
        break;
    default:
        break;
    }*/

    switch (currentDirection) {
    case Up:
        bullet->setPos(x() + boundingRect().width() / 2 - bullet->boundingRect().width() / 2, y() + boundingRect().height());
        bullet->setRotation(0);
        break;
    case Down:
        bullet->setPos(x() + boundingRect().width() / 2 - bullet->boundingRect().width() / 2, y()- bullet->boundingRect().height());
        bullet->setRotation(180);
        break;
    case Right:
        bullet->setPos(x() + boundingRect().width()+50, y() + boundingRect().height() / 2 - bullet->boundingRect().height() / 2);
        bullet->setRotation(90);
        break;
    case Left:
        bullet->setPos(x() - bullet->boundingRect().width()-50, y() + boundingRect().height() / 2 - bullet->boundingRect().height() / 2);
        bullet->setRotation(-90);
        break;
    default:
        break;
    }


    bullet->setCurrentDirection(current_tank_Direction);
    scene()->addItem(bullet);

    // 启动子弹的移动定时器，设置一个合适的时间间隔
    QTimer *bulletTimer = new QTimer();
    connect(bulletTimer, &QTimer::timeout, bullet, &Bullet::enemy_move);
    bulletTimer->start(30); // 调整时间间隔适合你的游戏速度
}
