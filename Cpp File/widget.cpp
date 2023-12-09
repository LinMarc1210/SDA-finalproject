#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>

Widget::Widget(QWidget *parent)//宣告一個QWidget的物件叫parent
    : QWidget(parent)//直接初始化
    , ui(new Ui::Widget), scene(new Scene)//直接初始化
{
    ui->setupUi(this);
    scene->setSceneRect(0,0,800,600);//game's O(0,0)為左上角座標,800跟600為寬跟高
    ui->graphicsView->setScene(scene);//透過graphicsView看scene
    ui->graphicsView->setFixedSize(800,600);//只能看到固定的大小
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//不給使用者show出上下調整的滾輪
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/images/Solid_black.png")));
}

Widget::~Widget()
{
    delete ui;
    delete scene;
}

