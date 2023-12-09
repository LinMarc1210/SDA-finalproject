#include "Health.h"
#include <QFont>

Health::Health()
{
    health = 2;

    setPlainText(QString::number(health));   //文字內容
    setDefaultTextColor(Qt::white);       //顏色
    setFont(QFont("times", 16));        //字體、字型大小
}

void Health::increase()
{
    // 吃到道具加血
    health++;
    setPlainText(QString::number(health));   //文字內容
}

void Health::decrease()
{
    // 被打中扣血
    // Level 判斷若是變成 -1，就 gameOver
    health--;
    setPlainText(QString::number(health));   //文字內容
}

int Health::getHealth()
{
    return health;
}
