#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);

    //构造函数重载版本
    MyPushButton(QString normalImg,QString pressdImg = "");//如果不需要按下图片则使用默认值

    QString normalImgPath;//默认显示图片路径
    QString pressedImgPath;//按下后显示图片路径

    //弹跳的特效
    void zoom1();//向下跳
    void zoom2();//向上跳

    //重写鼠标 按下 和 释放 事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

};

#endif // MYPUSHBUTTON_H
