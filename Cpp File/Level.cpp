#include "Level.h"
#include "Wall.h"
#include "Flag.h"
#include "Enemy.h"

Level::Level(int level, int number)
{
    setPlayer(number); //決定幾個玩家並生成在初始位置 //到底是給誰寫?
    generateMap(level);
    showSurvivor(remains);

    vector<vector<char>> tanks = {
        {'f', 'f', 'f', 'f', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'b', 'b', 'b', 'b', 'p', 'p', 'p', 'p'},
        {'p', 'p', 'p', 'p', 'f', 'f', 'f', 'f', 'f', 'f', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'b', 'b'}
    };
    setTankRemainsVector(tanks);

    //定時生成enemy(call generateEnemy)
    spawnTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, this, [this, level](){
        generateEnemy(level);
    });
    spawnTimer->start(2000);

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
            } else if (element == 'f') {
                Flag *flag;
                i+=800/52; //這裡還要再根據圖片大小做調整
            } else {
                continue;  //空白，不用放東西
                i+=800/52; //這裡還要再根據圖片大小做調整
            }
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
    Enemy *enemy= new Enemy(tanks[level-1][0]);

    //並將其從vector裡刪除
    tanks[level-1].erase(tanks[level-1].begin());
    setTankRemainsVector(tanks);

    remains--;
    showSurvivor(remains);
}

/* //還沒搞定，上面應該有bug
void Level::showSurvivor(int remains)
{
    //生成初始ramaining survivors，共20台，10*2
    for (int i=1; i<=remains; i++){
        for (int j=1; j<=2; j++){
            if(i%2==1 && i==remains){

                survivors = new QGraphicsPixmapItem(QPixmap(":/Images/Enemies/Remains.png"));
                survivors->setPos(740+i*10, 60+j*5);
                addItem(survivors);
            }

        }
    }
}
*/
