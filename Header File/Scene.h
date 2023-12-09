#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsPixmapItem>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    ~Scene();
    void startGame();

    bool getGameOn() const;
    void setGameOn(bool newGameOn);
    void setPlayer();

signals:

private:
    bool gameOn;
    int score;
    int bestScore;

    //在QGraphicsScene中就有PixmapItem, TextItem
    QGraphicsPixmapItem *battleCityBigWord;
    QGraphicsPixmapItem *onePlayer;
    QGraphicsPixmapItem *twoPlayer;
    QGraphicsTextItem *scoreTextItem;

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H
