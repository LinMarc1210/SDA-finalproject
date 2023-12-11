#include "Powerup.h"
#include <QGraphicsScene>
#include <ctime>
#include <random>
PowerUp::PowerUp(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));


    int xPos = std::rand() % 700;
    int yPos = std::rand() % 500;
    setPos(xPos, yPos);

    type = rand() % 6;
    setPixmap(generatePixmap());
}
QPixmap PowerUp::generatePixmap() {
    QString imageName;

    switch (type) {
    case 0:
        imageName = ":/image/Grenade.png";
        break;
    case 1:
        imageName = ":/image/Helmat.png";
        break;
    case 2:
        imageName = ":/image/Shovel.png";
        break;
    case 3:
        imageName = ":/image/Star.png";
        break;
    case 4:
        imageName = ":/image/Tank.png";
        break;
    case 5:
        imageName = ":/image/Timer.png";
        qDebug() << "Failed to load image: " << imageName;
        break;
    default:
        qDebug() << "Unknown power-up type!";
        return QPixmap();
    }
    QPixmap pixmap(imageName);
    if (pixmap.isNull()) {
        qDebug() << "Failed to load image: " << imageName;
    }

    return QPixmap(imageName);
}

void PowerUp::collected() {
    switch (type) {
    case 0:
        applyGrenadeEffect();
        break;
    case 1:
        applyHelmetEffect();
        break;
    case 2:
        applyShovelEffect();
        break;
    case 3:
        applyStarEffect();
        break;
    case 4:
        applyTankEffect();
        break;
    case 5:
        applyTimerEffect();
        break;
    default:
        qDebug() << "Unknown power-up type!";
    }
}

void PowerUp::applyGrenadeEffect() {
    qDebug() << "Grenade effect applied!";

}

void PowerUp::applyHelmetEffect() {
    qDebug() << "Helmet effect applied!";
}

void PowerUp::applyShovelEffect() {
    qDebug() << "Shovel effect applied!";
}

void PowerUp::applyStarEffect() {
    qDebug() << "Star effect applied!";
}

void PowerUp::applyTankEffect() {
    qDebug() << "Tank effect applied!";
}

void PowerUp::applyTimerEffect() {

    qDebug() << "Timer effect applied!";
}


