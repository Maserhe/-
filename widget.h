#ifndef WIDGET_H
#define WIDGET_H
#include <QVector>
#include <QWidget>
#include "position.h"
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QVector<position> array;

    void keyPressEvent(QKeyEvent *event);//键盘按下事件
    void  paintEvent(QPaintEvent *);//自动调用

private:
    Qt::Key key;//蛇行进方向

    bool food;//检查食物是否被吃掉

    position fruit;//果实


    int score;






    Ui::Widget *ui;
};
#endif // WIDGET_H
