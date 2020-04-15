#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QTimer>
#include<QKeyEvent>
#include<QtDebug>
#include<QTime>
#include<QMessageBox>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//种下产生随机数的种子
    this->resize(1400,800);//以20*20为一个单元格，相当于50和40随机数

    ui->lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->pushButton->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_2->setFocusPolicy(Qt::NoFocus);

    array.append(position(340,300));
    array.append(position(320,300));
    array.append(position(300,300));

    key= Qt::Key_Right;
    food= false;
    score=0;

    //创建定时器
    QTimer *time=new QTimer(this);
    time->start(600);
    //如果前面有果实的话，头部直接加长
    //没有果实，尾部，改为头部坐标
    connect(time,&QTimer::timeout,[=](){

        if(array[0].x>=1000|array[0].x<=0|array[0].y>=800|array[0].y<=0){
            if(QMessageBox::No==QMessageBox::question(this,"游戏结束！",QString("你的总分是"+QString::number(score)+",是否重新开始游戏？"))){
                ui->pushButton_2->click();

            }

            array.clear();
            array.append(position(340,300));
            array.append(position(320,300));
            array.append(position(300,300));
            key=Qt::Key_Right;

        }

        if(key==Qt::Key_Up){
            if(fruit.x*20==array[0].x&&fruit.y*20==array[0].y-20){
                array.push_front(position(fruit.x*20,fruit.y*20));
                food=false;
                score++;
            }

            else{
                    position tem;
                    tem.x=array[0].x;
                    tem.y=array[0].y-20;
                    array.push_front(tem);//头部插入，尾部删除
                    array.pop_back();
                }
        }
        else if (key==Qt::Key_Down) {
            if(fruit.x*20==array[0].x&&fruit.y*20==array[0].y+20){
                array.push_front(position(fruit.x*20,fruit.y*20));
                food=false;
                score++;
            }
            else{
                    position tem;
                    tem.x=array[0].x;
                    tem.y=array[0].y+20;
                    array.push_front(tem);//头部插入，尾部删除
                    array.pop_back();
                }
        }
        else if (key==Qt::Key_Left) {
            if(fruit.x*20==array[0].x-20&&fruit.y*20==array[0].y){
                array.push_front(position(fruit.x*20,fruit.y*20));
                food=false;
                score++;
            }
            else{
                    position tem;
                    tem.x=array[0].x-20;
                    tem.y=array[0].y;
                    array.push_front(tem);//头部插入，尾部删除
                    array.pop_back();
                }
        }
        else {
            if(fruit.x*20==array[0].x+20&&fruit.y*20==array[0].y){
                array.push_front(position(fruit.x*20,fruit.y*20));
                food=false;
                score++;
            }

            else{
                    position tem;
                    tem.x=array[0].x+20;
                    tem.y=array[0].y;
                    array.push_front(tem);//头部插入，尾部删除
                    array.pop_back();
                }
        }
        update();
    });

    //产生果实
    connect(time,&QTimer::timeout,[=](){
        if(food==false){
            while (1) {
                fruit.x=qrand()%50;
                fruit.y=qrand()%40;
                for (int i=0;i<array.size();i++) {
                    if(fruit.x==array[i].x&&fruit.y==array[i].y){
                        continue;
                    }
                }
                food=true;//存在果实
                break;
            }
        }
    });
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        time->start();
    });

    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        time->stop();
    });







}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{


    qDebug()<<"这里被调用了";
    switch (event->key()) {

    case Qt::Key_Up:
        //向上移动操作
        if(key==Qt::Key_Down){
            qDebug()<<"方向按错了";
        }
        else if (key==Qt::Key_Up) {
            qDebug()<<"重复按下";
        }
        else {
            key=Qt::Key_Up;//记录行进方向
        }
        break;

    case Qt::Key_Down:
        if(key==Qt::Key_Up){
            qDebug()<<"方向按错了";
        }
        else if (key==Qt::Key_Down) {
            qDebug()<<"重复按下";
        }
        else {
            key=Qt::Key_Down;//记录行进方向
        }
        break;

    case Qt::Key_Left:
        if(key==Qt::Key_Right){
            qDebug()<<"方向按错了";
        }
        else if (key==Qt::Key_Left) {
            qDebug()<<"重复按下";
        }
        else {
            key=Qt::Key_Left;//记录行进方向
        }
        break;
    case Qt::Key_Right:
        if(key==Qt::Key_Left){
            qDebug()<<"方向按错了";
        }
        else if (key==Qt::Key_Right) {
            qDebug()<<"重复按下";
        }
        else {
            key=Qt::Key_Right;//记录行进方向
        }
        break;
    }
}
//记住是 paintEvent
void Widget::paintEvent(QPaintEvent *)

{
    QPainter painter(this);
    //设置头部
    painter.drawPixmap(array[0].x,array[0].y,20,20,QPixmap(":/resourseFile/head.jpg"));

    //设置身体
    for(int i=1;i<array.size()-1;i++){
        painter.drawPixmap(array[i].x,array[i].y,20,20,QPixmap(":/resourseFile/body.jpg"));
    }
    //设置尾巴
    painter.drawPixmap(array.last().x,array.last().y,20,20,QPixmap(":/resourseFile/tail.png"));

    //设置果实
    if(food==true){
        painter.drawPixmap(fruit.x*20,fruit.y*20,20,20,QPixmap(":/resourseFile/apple.png"));
    }
    ui->lineEdit->setText(QString::number(score));

}

