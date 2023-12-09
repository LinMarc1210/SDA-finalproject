#include "Scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

Scene::Scene(QObject *parent):
    gameOn(false), score(0), bestScore(20000),
    scoreTextItem(nullptr),battleCityBigWord(nullptr)
{
    battleCityBigWord = new QGraphicsPixmapItem(QPixmap(":/images/Battlecity_bigword.jpg"));
    addItem(battleCityBigWord);
    battleCityBigWord->setPos(215,150);

    onePlayer = new QGraphicsPixmapItem(QPixmap(":/images/Oneplayer.jpg"));
    addItem(onePlayer);
    onePlayer->setPos(300,350);

    twoPlayer = new QGraphicsPixmapItem(QPixmap(":/images/Twoplayer.jpg"));
    addItem(twoPlayer);
    twoPlayer->setPos(300,400);
    //到時候從setplayer那邊印跟選擇

    scoreTextItem = new QGraphicsTextItem();
    QString htmlString = "<p> I- : " + QString::number(score) + " HI- : " + QString::number(bestScore) + " </p>";
    QFont font("Consolas", 20, QFont::Bold);

    scoreTextItem->setHtml(htmlString);
    scoreTextItem->setFont(font);
    scoreTextItem->setDefaultTextColor(Qt::white);
    addItem(scoreTextItem);

    scoreTextItem->setPos(50,30);
}

Scene::~Scene()
{

}

void Scene::setPlayer()
{
    onePlayer = new QGraphicsPixmapItem(QPixmap(":/images/Oneplayer.jpg"));
    addItem(onePlayer);
    onePlayer->setPos(250,300);

    twoPlayer = new QGraphicsPixmapItem(QPixmap(":/images/Twoplayer.jpg"));
    addItem(twoPlayer);
    twoPlayer->setPos(250,350);
}

void Scene::startGame()
{
    score = 0;
    setGameOn(true);
    // Start animation
}

// (could be improved if using virtual functions)

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool newGameOn)
{
    gameOn = newGameOn;
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {

    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {

    }
    QGraphicsScene::mousePressEvent(event);
}
