#ifndef SCENE_H
#define SCENE_H

#include "bullet.h"
#include "health.h"
#include "player.h"
#include "player2.h"
#include "score.h"
#include <QAudioOutput>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QTimer>
#include <QGraphicsPixmapItem>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(QObject* parent);
    //enum Player_Direction { Up, Down, Left, Right };
    //Player_Direction current_player_Direction = Up;
    int current_player_Direction=3;
    int current_player2_Direction=3;

private:
    Player *player;
    Player2 *player2;
    QTimer *timer;
    Score *score;
    Health *health;


public slots:
    void spawnEnemy();
    void increaseScore(Bullet *bullet, Enemy *enemy);
    void decreaseHealth(Enemy *enemy);


protected:
    //void keyPressEvent(QKeyEvent *event);
    void keyPressEvent1(QKeyEvent *event) ;
        // 這裡是處理第一個按鍵事件的程式
    void keyPressEvent2(QKeyEvent *event) ;
        // 這裡是處理第二個按鍵事件的程式碼
    void keyPressEvent(QKeyEvent *event) override ;

};

#endif // SCENE_H
