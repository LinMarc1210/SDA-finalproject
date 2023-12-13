#ifndef LEVEL_H
#define LEVEL_H

//#include "Enemy.h"
#include <vector>
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

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
    void showSurvivor(int remains);     //生成畫面右邊的坦克剩餘圖

    void setTankRemainsVector(const vector<vector<char>>& tankRemains);
    const vector<vector<char>>& getTankRemainsVector() const;

public slots:
    void generateEnemy(int level);

private:
    int level;    //等級
    int number;   //player人數
    int remains;
    vector<vector<char>> tanks;

    QGraphicsPixmapItem *survivors;
    QGraphicsPixmapItem *player1;
    QGraphicsPixmapItem *player2;

    QTimer *spawnTimer;

};


#endif // LEVEL_H
