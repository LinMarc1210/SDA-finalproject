#ifndef LEVEL_H
#define LEVEL_H

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
    Level(int level, int number);
    void setPlayer(int number);
    void generateMap(int level);
    bool gamePause();//目前不寫
    void saveGame(); //目前不知怎麼搞
    void showGameover();//最後再寫
    void showSurvivor(int remains);

    void setTankRemainsVector(const vector<vector<char>>& tankRemains);
    const vector<vector<char>>& getTankRemainsVector() const;

public slots:
    void generateEnemy(int level);

private:
//    int level;
//    int number;
    int remains =20;
    vector<vector<char>> tanks;

    QGraphicsPixmapItem *survivors;
    QGraphicsPixmapItem *player1;
    QGraphicsPixmapItem *player2;

    QTimer *spawnTimer;
};


#endif // LEVEL_H
