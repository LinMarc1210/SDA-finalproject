#ifndef LEVEL_H
#define LEVEL_H

#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>


class Level : public QGraphicsScene
{
    Q_OBJECT
public:
    Level(int level, int number);
    void setPlayer(int number);
    void generateMap(int level);
    void generateEnemy();
    bool gamePause();//目前不寫
    void saveGame(); //目前不知怎麼搞
    void showGameover();//最後再寫
    void showSurvivor();

private:
    int level;
    QGraphicsPixmapItem *survivors;
    QGraphicsPixmapItem *player1;
    QGraphicsPixmapItem *player2;

    QTimer *spawnTimer;
};


#endif // LEVEL_H
