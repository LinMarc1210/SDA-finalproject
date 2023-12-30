#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "Bullet.h"
#include "Health.h"
#include "Player.h"
#include "Player2.h"
#include "Score.h"
#include "Scene.h"
#include "Wall.h"

using namespace std;

class Level : public QGraphicsScene
{
    Q_OBJECT
public:
    Level(int =0, int =0); //接收scene傳來的level跟number of players
    void setPlayer(int number);
    void generateMap(int level);
    bool gamePause();//目前不寫
    void saveGame(); //目前不知怎麼搞
    void showGameover();//最後再寫

    void setTankRemainsVector(const vector<vector<char>>& tankRemains);
    const vector<vector<char>>& getTankRemainsVector() const;

    int current_player_Direction=3;
    int current_player2_Direction=3;
    void enemy_move();
    void checkPlayerWallCollision(Player *player, int playerDir);

    char tankType ;


public slots:
    void generateEnemy(int level);
    void increaseScore(Bullet *bullet, Enemy *enemy);
    void hitOnWall(Wall *wall, Bullet *bullet);
    // void encounterWall(Wall *wall);

signals:
    void handleBulletCreation(Bullet *bullet);

private:
    int level;    //等級
    int number;//player人數
    int number_1;
    int remains;
    vector<vector<char>> tanks;
    QGraphicsPixmapItem *survivors;
    QTimer *spawnTimer;
    Player *player;
    Player2 *player2;
    QTimer *timer;
    Score *score;
    Health *health;
    Scene* scene;
    QList<int> keys;
    void slotTimeOut1();
    QTimer* keyRespondTimer1;
protected:
    void keyPressEvent (QKeyEvent *event)override ;
    void keyReleaseEvent (QKeyEvent *event);
};

#endif // LEVEL_H
