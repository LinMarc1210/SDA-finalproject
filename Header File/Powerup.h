#ifndef POWERUP_H
#define POWERUP_H

#include <QGraphicsPixmapItem>

class PowerUp : public QGraphicsPixmapItem {
public:
    PowerUp(QGraphicsItem *parent = nullptr);
    int getType() const {
        return type;
    }
public slots:
    void collected();

private:
    QPixmap generatePixmap();


    int type; // Add any additional data members as needed
protected:
    void applyGrenadeEffect();
    void applyHelmetEffect();
    void applyShovelEffect();
    void applyStarEffect();
    void applyTankEffect();
    void applyTimerEffect();

};

#endif // POWERUP_H
