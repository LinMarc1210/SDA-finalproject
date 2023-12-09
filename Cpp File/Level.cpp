#include "Level.h"
#include "Wall.h"
#include <ostream>
#include <vector>

using namespace std;

Level::Level(int level, int number)
{

    setPlayer(number); //決定幾個玩家並生成在初始位置
    generateMap(level);


    //定時生成enemy，然後再call
    spawnTimer = new QTimer();
    connect(spawnTimer, &QTimer::timeout, this, &Level::generateEnemy();
    spawnTimer->start(50);


//生成初始ramaining survivors，共20台，10*2
    for (int i=1; i<=10; i++){
        for (int j=1; j<=2; j++){
            survivors = new QGraphicsPixmapItem(QPixmap(":/Images/Enemies/Remains.png"));
            survivors->setPos(740+i*10, 60+j*5);
            addItem(survivors);
        }
    }
}

void Level::setPlayer(int number)
{
    if(number==1){
        player1 = new QGraphicsPixmapItem(QPixmap(":/Images/Players/Player1.png"));
        player1->setPos(200, 550);
        addItem(player1);
    }else{
        player1 = new QGraphicsPixmapItem(QPixmap(":/Images/Players/Player1.png"));
        player1->setPos(200, 550);
        addItem(player1);

        player2 = new QGraphicsPixmapItem(QPixmap(":/Images/Players/Player1.png"));
        player2->setPos(600, 550);
        addItem(player2);
    }
}

void Level::generateMap(int level)
{
    //map 19
    vector<string> data;

    if (level == 1) {
        data = {
            "*&*&*",
            "$#***",
            "&*###",
            "$$$$$",
            "##$#$"
        };
    } else {
    /map 28
        data = {
            "*&*&*",
            "$#***",
            "&*###",
            "$###$",
            "##$#$"
        };
    }
    //存成二維陣列
    vector<vector<char>> matrix;
    for (const string& row : data) {
        vector<char> rowVector(row.begin(), row.end());
        matrix.push_back(rowVector);
    }

    int i = 0;
    int j = 0;

    //setPos
    for (const auto& rowVector : matrix) {
        i = 0; //寫完一row就回到0
        for (char element : rowVector) {
            if (element == '#') {
                Wall *wall = new Wall('b');
                addItem(wall);
                wall->setPos(i ,j);
                i+=800/52; //這裡還要再根據圖片大小做調整
            } else if (element == '$') {
                Wall *wall = new Wall('i');
                addItem(wall);
                wall->setPos(i, j);
                i+=800/52; //這裡還要再根據圖片大小做調整
            } else if (element == '&') {
                Wall *wall = new Wall('s');
                addItem(wall);
                wall->setPos(i, j);
                i+=800/52; //這裡還要再根據圖片大小做調整
            } else if (element == '%') {
                Wall *wall = new Wall('t');
                addItem(wall);
                wall->setPos(i, j);
                i+=800/52; //這裡還要再根據圖片大小做調整
            } else if (element == '@') {
                Wall *wall = new Wall('w');
                addItem(wall);
                wall->setPos(i, j);
                i+=800/52; //這裡還要再根據圖片大小做調整
            } else if (element == '^') {
                Wall *wall = new Wall('f');
                addItem(wall);
                wall->setPos(i, j);
                i+=800/52; //這裡還要再根據圖片大小做調整
            } else {
                continue;  //空白，不用放東西
                i+=800/52; //這裡還要再根據圖片大小做調整
            }
        }
        j += 800/52;       //這裡還要再根據圖片大小做調整
    }
}
/*
    //另一寫法
    if (level==1){
        //layer 1
        for (int i=1; i<=10; i++){
            for(int j=1; j<=52; j++){
                if(j%4==1){
                    j+=4;

                }else{
                    if(i>8){
                        Wall *wall = new Wall('b');
                        addItem(wall);
                        wall->setPos(800/52*j, 800/52*i);
                    }else{
                        Wall *wall = new Wall('s');
                        addItem(wall);
                        wall->setPos(800/52*j, 800/52*i);
                    }
                }
            }
        }
        //layer 2
        for(int i=1; i<=2; i++){
            for(int j=1; j<=52; j++){
                if(j==17 || j==33){
                    Wall *wall = new Wall('b');
                    addItem(wall);
                    wall->setPos(800/52*j, 800/52+800/52*i);
                }
            }
        }



        //layer 3

    }else{      //map 28但要加上河流呵呵

    }
*/
}

void Level::generateEnemy()
{
    showSurvivor();
}


void Level::showSurvivor()
{
    if(){   //每出現一個tank就要刪除一個，484要改成connect會比較好
        removeItem(survivors);
        //一個一個刪除的方式還沒寫，想不到哈哈哈哈哈
    }

}
