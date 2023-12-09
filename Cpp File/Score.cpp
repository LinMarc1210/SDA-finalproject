#include "Score.h"
#include <QFont>

Score::Score()
{
    score = 0;
    highestScore = 20000;

    basicTankScore = 0;
    fastTankScore = 0;
    powerTankScore = 0;
    armorTankScore = 0;

    basicTankNum = 0;
    fastTankNum = 0;
    powerTankNum = 0;
    armorTankNum = 0;

    setPlainText("Score: " + QString::number(score));   //文字內容
    setDefaultTextColor(Qt::white);      //顏色
    setFont(QFont("times", 16));        //字體、字型大小
}

void Score::increase(char type)
{
    // 打中敵機加分
    switch(type)
    {
        case 'b':
            score += 100;
            basicTankScore += 100;
            basicTankNum++;
            break;
        case 'f':
            score += 200;
            fastTankScore += 100;
            fastTankNum++;
            break;
        case 'p':
            score += 300;
            powerTankScore += 100;
            powerTankNum++;
            break;
        case 'a':
            score += 400;
            armorTankScore += 100;
            armorTankNum++;
            break;
    }

    setPlainText("Score: " + QString::number(score));   //文字內容
}

int Score::getScore()
{
    return score;
}

void Score::updateHighestScore()
{
    if (score >= highestScore)
    {
        highestScore = score;
    }

    setPlainText("Score: " + QString::number(score));   //文字內容
}
