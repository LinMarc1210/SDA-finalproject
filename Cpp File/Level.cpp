#include "Wall.h"
#include "Flag.h"
#include "Level.h"
#include <QDebug>
#include "Bullet.h"
#include "Enemy.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include "Player.h"
#include "Player2.h"
#include "Scene.h"

Level::Level(int level, int number)
    :remains(20),
    tanks({{'f', 'f', 'f', 'f', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'b', 'b', 'b', 'b', 'p', 'p', 'p', 'p'},
           {'p', 'p', 'p', 'p', 'f', 'f', 'f', 'f', 'f', 'f', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'b', 'b'}}),tankType('\0')
{
    number_1=number;
    generateMap(level);
    setPlayer(number); //決定幾個玩家並生成在初始位置
//    showSurvivor(remains);
    setTankRemainsVector(tanks);

    //定時生成enemy(call generateEnemy)
    spawnTimer = new QTimer(this);
    generateEnemy(level); // 先生成一個初始敵人
    connect(spawnTimer, &QTimer::timeout, this, [this, level](){
        generateEnemy(level);
    });
    spawnTimer->start(8000); // 2000 改成 8000

    // Create the score
    score = new Score();
    addItem(score);

    // Create the health
    health = new Health();
    health->setPos(health->x(), health->y() + 25);
    addItem(health);

    keyRespondTimer1 = new QTimer(this);
    connect(keyRespondTimer1, &QTimer::timeout, this, &Level::slotTimeOut1);

}

void Level::setPlayer(int number)
{
    if(number==1){
        player = new Player();
        player->setPos(246,738);
        player->setPos1(player->pos());
        addItem(player);
    }else{
        player = new Player();
        player->setPos(246,738);
        player->setPos1(player->pos());
        addItem(player);
        player2 = new Player2();
        player2->setPos(492,738);

        addItem(player2);
    }
}

void Level::increaseScore(Bullet *bullet, Enemy *enemy)
{
    removeItem(bullet);
    delete bullet;

    if (tankType == 'a') { // 如果是Armor Tank
        enemy->hits++;
        qDebug() << "Armor Tank hits: " << enemy->hits;

        // 檢查是否被射擊了四次
        if (enemy->hits >= 4) {
            removeItem(enemy);
            delete enemy;
        }
    } else {
        // 如果是其他坦克類型，直接刪除
        removeItem(enemy);
        delete enemy;
    }
    //removeItem(enemy);
    //delete enemy;
    //score->increase();
}

void Level::hitOnWall(Wall *wall, Bullet *bullet)
{
    switch(wall->getTypeIndex()){
        case 0:
            removeItem(bullet);
            delete bullet;
            removeItem(wall);
            delete wall;
            break;
        case 1:
            removeItem(bullet);
            delete bullet;
            break;
        default:
            break;
    }
}

//void Level::encounterWall(Wall *wall)
//{

//    //player->setPos1(player->pos()); // pos1 紀錄移動前

//    switch(wall->getTypeIndex()){
//        case 0:
//        case 1:
//        case 3:
//            // qDebug() << "Hi"; // 有觸發
//            player->setColliding(true);
//            player->setPos(player->getPrev()); // 把圖片退回前一步
////            player->setColliding(false);
//            break;
//        default:
//            break;
//    }
//}


void Level::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
            Bullet *bullet = new Bullet(10);
            connect(bullet, &Bullet::bulletHitsEnemy, this, &Level::increaseScore);
            //bullet->setPos(player->pos());
            switch (player->current_player_Direction) {
            case 3:
            bullet->setPos(player->x() + player->pixmap().width() / 2 - bullet->pixmap().width() / 2, player->y());
            break;
            case 4:
            bullet->setPos(player->x() + player->pixmap().width() / 2 - bullet->pixmap().width() / 2, player->y() + player->pixmap().height() - bullet->pixmap().height());
            break;
            case 1:
            bullet->setPos(player->x(), player->y() + player->pixmap().height() / 2 - bullet->pixmap().height() / 2);
            break;
            case 2:
            bullet->setPos(player->x() + player->pixmap().width() - bullet->pixmap().width(), player->y() + player->pixmap().height() / 2 - bullet->pixmap().height() / 2);
            break;
            default:
            break;
            }
            bullet->setCurrentDirection(player->current_player_Direction);
            addItem(bullet);

    }
    if(number_1==2){
            if (event->key() == Qt::Key_Q) {
            Bullet *bullet = new Bullet(10);
            connect(bullet, &Bullet::bulletHitsEnemy, this, &Level::increaseScore);
            //bullet->setPos(player->pos());

            switch (player2->current_player2_Direction) {
            case 3:
                bullet->setPos(player2->x() + player2->pixmap().width() / 2 - bullet->pixmap().width() / 2, player2->y());
                break;
            case 4:
                bullet->setPos(player2->x() + player2->pixmap().width() / 2 - bullet->pixmap().width() / 2, player2->y() + player2->pixmap().height() - bullet->pixmap().height());
                break;
            case 1:
                bullet->setPos(player2->x(), player2->y() + player2->pixmap().height() / 2 - bullet->pixmap().height() / 2);
                break;
            case 2:
                bullet->setPos(player2->x() + player2->pixmap().width() - bullet->pixmap().width(), player2->y() + player2->pixmap().height() / 2 - bullet->pixmap().height() / 2);
                break;
            default:
                break;
            }
            bullet->setCurrentDirection(player2->current_player2_Direction);
            addItem(bullet);}

    }

    if (!event->isAutoRepeat()) {
        keys.append(event->key());
    }
    if (!keyRespondTimer1->isActive()) {
        keyRespondTimer1->start(4);
    }
}

void Level::keyReleaseEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        keys.removeAll(event->key());
    }
    if (keys.isEmpty()) {
        keyRespondTimer1->stop();
    }
}



void Level::slotTimeOut1() {

    //player->keyPressEvent1(keys); // 這裡處理player1的按鍵事件
    foreach (int key, keys){
        QPointF pos = player->pos();  // Assuming 'player' is the current instance
        player->setPrev(pos); // prev 相當於記移動前的位置
        player->setTransformOriginPoint(player->boundingRect().center());
        QPointF nextpos = pos;

        if (key == Qt::Key_Left ) {
            player->current_player_Direction = 1;
            player->setRotation(180); // 左邊
            nextpos = pos + QPointF(-2, 0);
        } else if (key == Qt::Key_Right) {
            player->current_player_Direction = 2; // 改變方向為右邊
            player->setRotation(0); // 右邊
            nextpos = pos + QPointF(2, 0);
        } else if (key == Qt::Key_Up) {
            player->current_player_Direction = 3;
            player->setRotation(-90); // 上面
            nextpos = pos + QPointF(0, -2);
        } else if (key == Qt::Key_Down) {
            player->current_player_Direction = 4;
            player->setRotation(90); // 下面
            nextpos = pos + QPointF(0, 2);
        }
        player->setPos1(nextpos);
        checkPlayerWallCollision(player, player->current_player_Direction);

//        if (player->getColliding()) {
//            player->setPos1(player->getPrev());
//            player->setColliding(false);
//        }
//        else {
//            player->setPos1(nextpos);
//            qDebug() << nextpos << player->pos() << "prev = " << player->getPrev();
//        }

//        if (player->getPos1() == player->getPrev()){
//            player->setColliding(false);
//        }
        player->setPos(player->getPos1());  // 把player1 在畫面上移到正確的位置


        // player->keyPressEvent1(key);


        if(number_1==2){
            player2->keyPressEvent2(key); // 這裡處理player2的按鍵事件 
        }
    }
}

void Level::generateMap(int level)
{
    //map 19
    vector<string> data;
    if (level == 1) {
        data = {
            "****####****####****####****####****####****####****",//layer1
            "****####****####****####****####****####****####****",
            "****####****####****####****####****####****####****",
            "****####****####****####****####****####****####****",
            "****####****####****####****####****####****####****",
            "****####****####****####****####****####****####****",
            "****####****####****####****####****####****####****",
            "****####****####****####****####****####****####****",
            "****####****####****####****####****####****####****",
            "****&&&&****&&&&****&&&&****&&&&****&&&&****&&&&****",
            "****&&&&****&&&&****&&&&****&&&&****&&&&****&&&&****",
            "****************************************************",
            "****************************************************",
            "****************####************####****************",//layer2
            "****************####************####****************",
            "####****####****####************####****####****####",
            "####****####****####************####****####****####",
            "####****############****####****############****####",
            "####****############****####****############****####",
            "####****####****####****####****####****####****####",
            "####****####****####****####****####****####****####",
            "&&&&****&&&&****&&&&****&&&&****&&&&****&&&&****&&&&",
            "&&&&****&&&&****&&&&****&&&&****&&&&****&&&&****&&&&",
            "****************&&&&************&&&&****************",
            "****************&&&&************&&&&****************",
            "%%%%%%%%********####****%%%%****####********%%%%%%%%",//layer3
            "%%%%%%%%********####****%%%%****####********%%%%%%%%",
            "%%%%%%%%********####****%%%%****####********%%%%%%%%",
            "%%%%%%%%********####****%%%%****####********%%%%%%%%",
            "%%%%%%%%%%%%%%%%########%%%%########%%%%%%%%%%%%%%%%",
            "%%%%%%%%%%%%%%%%########%%%%########%%%%%%%%%%%%%%%%",
            "%%%%%%%%%%%%%%%%####****%%%%****####%%%%%%%%%%%%%%%%",
            "%%%%%%%%%%%%%%%%####****%%%%****####%%%%%%%%%%%%%%%%",
            "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
            "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
            "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
            "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
            "****************####%%%%%%%%%%%%####****************",
            "****************####%%%%%%%%%%%%####****************",
            "####****####****####%%%%%%%%%%%%####****####****####",
            "####****####****####%%%%%%%%%%%%####****####****####",
            "****####****####********%%%%********####****####****",//layer4
            "****####****####********%%%%********####****####****",
            "****####****####********%%%%********####****####****",
            "****####****####********************####****####****",
            "****####****####********************####****####****",
            "****####****####****############****####****####****",
            "****####****####****############****####****####****",
            "****####****####****####f***####****####****####****",
            "****####****####****####****####****####****####****",
            "********************####****####********************",
            "********************####****####********************"
        };
    } else {
        //map 28
        data = {
            "****************************************************",
            "****************************************************",
            "****************************************************",
            "****************************************************",
            "****************####****####************************",
            "****************####****####************************",
            "****************####****####************************",
            "****************####****####************************",
            "%%%%********%%%%####%%%%####%%%%********%%%%********",
            "%%%%********%%%%####%%%%####%%%%********%%%%********",
            "%%%%********%%%%####%%%%####%%%%********%%%%********",
            "%%%%********%%%%####%%%%####%%%%********%%%%********",
            "####%%%%%%%%####################%%%%%%%%####%%%%****",
            "####%%%%%%%%####################%%%%%%%%####%%%%****",
            "####%%%%%%%%####################%%%%%%%%####%%%%****",
            "####%%%%%%%%####################%%%%%%%%####%%%%****",
            "################&&&&####&&&&################%%%%****",
            "################&&&&####&&&&################%%%%****",
            "################&&&&####&&&&################%%%%****",
            "################&&&&####&&&&################%%%%****",
            "@@@@@@@@@@@@####################@@@@@@@@@@@@%%%%****",
            "@@@@@@@@@@@@####################@@@@@@@@@@@@%%%%****",
            "@@@@@@@@@@@@####################@@@@@@@@@@@@%%%%****",
            "@@@@@@@@@@@@####################@@@@@@@@@@@@%%%%****",
            "@@@@####################################@@@@@@@@%%%%",
            "@@@@####################################@@@@@@@@%%%%",
            "@@@@####################################@@@@@@@@%%%%",
            "@@@@####################################@@@@@@@@%%%%",
            "############@@@@############@@@@############%%%%%%%%",
            "############@@@@############@@@@############%%%%%%%%",
            "############@@@@############@@@@############%%%%%%%%",
            "############@@@@############@@@@############%%%%%%%%",
            "########@@@@@@@@@@@@####@@@@@@@@@@@@########@@@@@@@@",
            "########@@@@@@@@@@@@####@@@@@@@@@@@@########@@@@@@@@",
            "########@@@@@@@@@@@@####@@@@@@@@@@@@########@@@@@@@@",
            "########@@@@@@@@@@@@####@@@@@@@@@@@@########@@@@@@@@",
            "%%%%@@@@@@@@%%%%%%%%%%%%%%%%%%%%@@@@@@@@%%%%@@@@%%%%",
            "%%%%@@@@@@@@%%%%%%%%%%%%%%%%%%%%@@@@@@@@%%%%@@@@%%%%",
            "%%%%@@@@@@@@%%%%%%%%%%%%%%%%%%%%@@@@@@@@%%%%@@@@%%%%",
            "%%%%@@@@@@@@%%%%%%%%%%%%%%%%%%%%@@@@@@@@%%%%@@@@%%%%",
            "****%%%%%%%%********************%%%%%%%%****%%%%****",
            "****%%%%%%%%********************%%%%%%%%****%%%%****",
            "****%%%%%%%%********************%%%%%%%%****%%%%****",
            "****%%%%%%%%********************%%%%%%%%****%%%%****",
            "****************************************************",
            "****************************************************",
            "********************############********************",
            "********************############********************",
            "********************####f***####********************",
            "********************####****####********************",
            "********************####****####********************",
            "********************####****####********************"
        };
    }

    //存成二維陣列
    vector<vector<char>> matrix;
    for (const string& row : data) {
        vector<char> rowVector(row.begin(), row.end());
        matrix.push_back(rowVector);
    }

    float i = 0;
    float j = 0;

    //setPos
    for (const auto& rowVector : matrix) {
        i = 0; //寫完一row就回到0
        for (char element : rowVector) {
            if (element == '#') {
                Wall *wall = new Wall('b');
                addItem(wall);
                wall->setPos(i ,j);
                connect(wall, &Wall::breakWall, this, &Level::hitOnWall);
//                connect(wall, &Wall::wallBlockTank, this, &Level::encounterWall);
//                connect(wall, &Wall::wallBlockTank, [=](){
//                    encounterWall(wall);
//                    player->setPos(player->getPrev()); // 把圖片退回前一步
//                });
            } else if (element == '&') {
                Wall *wall = new Wall('s');
                addItem(wall);
                wall->setPos(i, j);
                connect(wall, &Wall::breakWall, this, &Level::hitOnWall);
//                connect(wall, &Wall::wallBlockTank, this, &Level::encounterWall);
            } else if (element == '%') {
                Wall *wall = new Wall('t');
                addItem(wall);
                wall->setPos(i, j);
            } else if (element == '@') {
                Wall *wall = new Wall('w');
                addItem(wall);
                wall->setPos(i, j);
//                connect(wall, &Wall::wallBlockTank, this, &Level::encounterWall);
            } else if (element == '$') {
                Wall *wall = new Wall('i');
                addItem(wall);
                wall->setPos(i, j);
            } else if (element == 'f') {
                Flag *flag = new Flag();
                addItem(flag);
                flag->setPos(370, 740);
            } else {
                i+=800/52; //這裡還要再根據圖片大小做調整
                continue;  //空白，不用放東西
            }
            i += 800/52; //這裡還要再根據圖片大小做調整
        }
        j += 800/52;       //這裡還要再根據圖片大小做調整
    }
}

void Level::setTankRemainsVector(const vector<vector<char> > &tankRemains)
{
    tanks = tankRemains;
}

const vector<vector<char> > &Level::getTankRemainsVector() const
{
    return tanks;
}

void Level::generateEnemy(int level)
{
    //用connect,當timeout就生成一隻tank
    getTankRemainsVector();


    //並將其從vector裡刪除
    if(!tanks[level-1].empty())
    {

        tankType = tanks[level - 1].front();
        Enemy *enemy = new Enemy();

        switch (tankType)
        {
        case 'f':
            enemy->setPixmap(QPixmap(":/images/Enemies/Fast_Tank.png").scaled(40, 40));
            enemy->moveSpeed=30;
            enemy->bulletSpeed=20;
            break;
        case 'a':
            enemy->setPixmap(QPixmap(":/images/Enemies/Armor_Tank.png").scaled(40, 40));
            enemy->moveSpeed=20;
            enemy->bulletSpeed=20;
            //tankType='a';
            break;
        case 'b':
            enemy->setPixmap(QPixmap(":/images/Enemies/Basic_Tank.png").scaled(40, 40));
            enemy->moveSpeed=10;
            enemy->bulletSpeed=10;
            break;
        case 'p':
            enemy->setPixmap(QPixmap(":/images/Enemies/Power_Tank.png").scaled(40, 40));
            enemy->moveSpeed=30;
            enemy->bulletSpeed=30;
            break;
        default:
            break;
        }
        addItem(enemy);
        qDebug()<<"delete picture...";
        tanks[level-1].erase(tanks[level-1].begin());
        setTankRemainsVector(tanks);
    }
    else
    {
        qDebug()<<"finish deleting";
        spawnTimer->stop();
    }
}

void Level::checkPlayerWallCollision(Player *player, int playerDir) {
    QPointF pos = player->pos();
    QPointF nextpos = player->getPos1();  // 玩家下一步的位置

    // 遍歷所有牆，看是否與玩家發生碰撞
    for (QGraphicsItem *item : items()) {
        Wall *wall = dynamic_cast<Wall*>(item);
        if (wall) {
            switch(wall->getTypeIndex()){
            case 0:
            case 1:
                // 如果以下情況，阻止玩家移動
                // 1. 若往左走小於牆的x
                // 2. 若往右走大於牆的x
                // 3. 若往上走小於牆的y
                // 4. 若往下走大於牆的y
                if (nextpos.x() < wall->pos().x() + wall->boundingRect().width() &&
                    nextpos.x() + player->pixmap().width() > wall->pos().x() &&
                    nextpos.y() < wall->pos().y() + wall->boundingRect().height() &&
                    nextpos.y() + player->pixmap().height() > wall->pos().y()) {
                    player->setPos1(pos);  // 玩家位置還原當前位置
                    return;
                }
            }
        }
    }
}
