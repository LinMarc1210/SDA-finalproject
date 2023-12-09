#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem
{
public:
    Score();
    void increase(char type);   //setter
    int getScore();             //getter
    void updateHighestScore();

private:
    int score; // 總分
    int highestScore; // 當前最高分

    int basicTankScore;
    int fastTankScore;
    int powerTankScore;
    int armorTankScore;

    int basicTankNum;
    int fastTankNum;
    int powerTankNum;
    int armorTankNum;
};

#endif // SCORE_H
