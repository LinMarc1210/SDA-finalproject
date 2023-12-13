#include "Scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

Scene::Scene(QObject *parent):
    gameOn(false), score(0), bestScore(20000),level(1),
    scoreTextItem(nullptr)
{
    battleCityBigWord = new QGraphicsPixmapItem(QPixmap(":/images/Homepage/Battlecity_bigword.jpg"));
    addItem(battleCityBigWord);
    battleCityBigWord->setPos(215,150);

    onePlayer = new QGraphicsPixmapItem(QPixmap(":/images/Homepage/Oneplayer.jpg"));
    addItem(onePlayer);
    onePlayer->setPos(300,350);

    twoPlayer = new QGraphicsPixmapItem(QPixmap(":/images/Homepage/Twoplayer.jpg"));
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

void Scene::setPlayer(int newplayer)
{
    player = newplayer;
    //看傳來的player有幾位決定做什麼事
}

int Scene::getPlayer()
{
    return player;
}

void Scene::startGame()
{
    score = 0;
    setGameOn(true);
    // Start animation
}

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
    if (event->key() == Qt::Key_X) {
        if(level<2){
            level++;
        }
        setLevel();
    }
    if (event->key() == Qt::Key_Z) {
        if(level>1){
           level--;
        }
        setLevel();
    }
    if (event->key() == Qt::Key_Return) { // Enter鍵
        emit changeLevel();
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPointF clickPos = event->scenePos(); // 取得滑鼠點擊的位置

        QRectF onePlayerRect = onePlayer->sceneBoundingRect(); // 取得 onePlayer 物件的邊界
        if (onePlayerRect.contains(clickPos)) {
            setPlayer(1);
            setLevel();
            return;
        }

        QRectF twoPlayerRect = twoPlayer->sceneBoundingRect(); // 取得 twoPlayer 物件的邊界
        if (twoPlayerRect.contains(clickPos)) {
            setPlayer(2);
            setLevel();
            return;
        }

    }
    QGraphicsScene::mousePressEvent(event);
}

void Scene::setLevel()
{
    levelChose = new QGraphicsPixmapItem(QPixmap(":/images/Homepage/Level_chose.png"));
    addItem(levelChose);
    qreal scale = 3.0;
    levelChose->setScale(scale);
    levelChose->setPos(0,0);


    levelTextItem = new QGraphicsTextItem();
    QString htmlString = "<p> STAGE : " + QString::number(level);
    //感覺要用timer去更新選擇level
    QFont font("Consolas", 20, QFont::Bold);

    levelTextItem->setHtml(htmlString);
    levelTextItem->setFont(font);
    levelTextItem->setDefaultTextColor(Qt::white);
    addItem(levelTextItem);

    levelTextItem->setPos(275,275);
}

int Scene::getLevel()
{
    return level;
}
