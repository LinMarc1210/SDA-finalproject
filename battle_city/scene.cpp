#include "bullet.h"
#include "enemy.h"
#include "scene.h"
#include <QDebug>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include "player.h"
#include "player2.h"

Scene::Scene(QObject *parent): QGraphicsScene(parent)
{
    QGraphicsPixmapItem *bgImage =new QGraphicsPixmapItem(QPixmap(":/images/background.jpg"));
    addItem(bgImage);

    // Create a QGraphicsRectItem (a QGraphicsItem representing a rect)
    player = new Player();
    player->setPos(350, 500);
    addItem(player);

    player2 = new Player2();
    player2->setPos(550, 500); // 根據您的需求設定初始位置
    addItem(player2);

    // Create the score
    score = new Score();
    addItem(score);

    // Create the health
    health = new Health();
    health->setPos(health->x(), health->y() + 25);
    addItem(health);

    // Randomly spawn enemies every 2s
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Scene::spawnEnemy);
    timer->start(5000); // 2s
}

void Scene::spawnEnemy() {
    // Create an enemy
    Enemy *enemy = new Enemy();
    connect(enemy, &Enemy::enemyHitsTheGround, this, &Scene::decreaseHealth);
    addItem(enemy);
}

void Scene::increaseScore(Bullet *bullet, Enemy *enemy)
{
    removeItem(bullet);
    delete bullet;
    removeItem(enemy);
    delete enemy;
    score->increase();
}

void Scene::decreaseHealth(Enemy *enemy)
{
    removeItem(enemy);
    delete enemy;
    health->decrease();
}


void Scene::keyPressEvent1(QKeyEvent *event)
{
    qDebug() << "Scene knows you pressed a key";
    QPointF pos = player->pos();
    player->setTransformOriginPoint(player->boundingRect().center());
    if (event->key() == Qt::Key_Left && pos.x() > 0) {
        current_player_Direction = 1;
        player->setRotation(-90); // 左邊
        player->setPos(pos + QPointF(-10, 0));
    } else if (event->key() == Qt::Key_Right && pos.x() < 700) {
        current_player_Direction = 2; // 改變方向為右邊
        player->setRotation(90); // 右邊
        player->setPos(pos + QPointF(10, 0));
    } else if (event->key() == Qt::Key_Up) {
        current_player_Direction = 3;
        player->setRotation(0); // 上面
        player->setPos(pos + QPointF(0, -10));
    } else if (event->key() == Qt::Key_Down) {
        current_player_Direction = 4;
        player->setRotation(180); // 下面
        player->setPos(pos + QPointF(0, 10));
    }

    if (event->key() == Qt::Key_Space) {
        Bullet *bullet = new Bullet();
        connect(bullet, &Bullet::bulletHitsEnemy, this, &Scene::increaseScore);
        //bullet->setPos(player->pos());

        switch (current_player_Direction) {
        case 3:
            bullet->setPos(player->x() + player->pixmap().width() / 2 - bullet->pixmap().width() / 2, player->y());
            break;
        case 4:
            bullet->setPos(player->x() + player->pixmap().width() / 2 - bullet->pixmap().width() / 2, player->y() + player->pixmap().height() - bullet->pixmap().height());
            break;
        case 1:
            bullet->setPos(player->x(), player->y() + player->pixmap().height() / 2 - bullet->pixmap().height() / 2);
            break;
        case 2:
            bullet->setPos(player->x() + player->pixmap().width() - bullet->pixmap().width(), player->y() + player->pixmap().height() / 2 - bullet->pixmap().height() / 2);
            break;
        default:
            break;
        }
        bullet->setCurrentDirection(current_player_Direction);
        addItem(bullet);
    }
}

void Scene::keyPressEvent2(QKeyEvent *event)
{
    //part2
    QPointF pos2 = player2->pos();
    player2->setTransformOriginPoint(player2->boundingRect().center());
    if (event->key() == Qt::Key_A && pos2.x() > 0) {
        current_player2_Direction = 1;
        player2->setRotation(-90); // 左邊
        player2->setPos(pos2 + QPointF(-10, 0));
    } else if (event->key() == Qt::Key_D && pos2.x() < 700) {

        current_player2_Direction = 2; // 改變方向為右邊
        player2->setRotation(90); // 右邊
        player2->setPos(pos2 + QPointF(10, 0));
    } else if (event->key() == Qt::Key_W) {

        current_player2_Direction = 3;
        player2->setRotation(0); // 上面
        player2->setPos(pos2 + QPointF(0, -10));
    } else if (event->key() == Qt::Key_S) {

        current_player2_Direction = 4;
        player2->setRotation(180); // 下面
        player2->setPos(pos2 + QPointF(0, 10));
    }

    if (event->key() == Qt::Key_Q) {
        Bullet *bullet = new Bullet();
        connect(bullet, &Bullet::bulletHitsEnemy, this, &Scene::increaseScore);
        //bullet->setPos(player->pos());

        switch (current_player2_Direction) {
        case 3:
            bullet->setPos(player2->x() + player2->pixmap().width() / 2 - bullet->pixmap().width() / 2, player2->y());
            break;
        case 4:
            bullet->setPos(player2->x() + player2->pixmap().width() / 2 - bullet->pixmap().width() / 2, player2->y() + player2->pixmap().height() - bullet->pixmap().height());
            break;
        case 1:
            bullet->setPos(player2->x(), player2->y() + player2->pixmap().height() / 2 - bullet->pixmap().height() / 2);
            break;
        case 2:
            bullet->setPos(player2->x() + player2->pixmap().width() - bullet->pixmap().width(), player2->y() + player2->pixmap().height() / 2 - bullet->pixmap().height() / 2);
            break;
        default:
            break;
        }
        bullet->setCurrentDirection(current_player2_Direction);
        addItem(bullet);
    }
}

void Scene::keyPressEvent(QKeyEvent *event) {
    keyPressEvent1(event); // 這裡處理player1的按鍵事件
    keyPressEvent2(event); // 這裡處理player2的按鍵事件
}
