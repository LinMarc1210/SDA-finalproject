#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

class Health : public QGraphicsTextItem
{
public:
    Health();
    void increase();     // buff
    void decrease();     // setter
    int getHealth();     // getter

private:
    int health;
};
#endif // HEALTH_H
