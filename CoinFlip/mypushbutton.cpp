#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>//创建动画对象

MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
{

}

//构造函数重载版本
MyPushButton::MyPushButton(QString normalImg, QString pressdImg)//声明有默认值，实现不能加，二者只能一个有
{
    //normalImgPath默认显示图片路径
    normalImgPath = normalImg;
    //pressedImgPath//按下后显示图片路径
    pressedImgPath = pressdImg;

    //创建QPixmap对象
    QPixmap pix;
    //判断石头能够加载图片，若不能提示加载失败
    bool ret = pix.load(normalImgPath);
    if(!ret)
    {
        qDebug()<<normalImg<<"加载图片失败!";
        return;
    }
    //设置图片固定尺寸 和图片大小相同
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片的样式表
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(pix.size());

}

//弹跳的特效
void MyPushButton::zoom1()
{
    //创建动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画的时间间隔
    animation->setDuration(50);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+5,this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyPushButton::zoom2()
{
    //创建动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画的时间间隔
    animation->setDuration(50);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()-5,this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}



//重写鼠标 按下 和 释放 事件
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressedImgPath != "")
    {
        //创建QPixmap对象
        QPixmap pix;
        //判断石头能够加载图片，若不能提示加载失败
        bool ret = pix.load(pressedImgPath);
        if(!ret)
        {
            qDebug()<<pressedImgPath<<"加载图片失败!";
            return;
        }
        //设置图片固定尺寸 和图片大小相同
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片的样式表
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(pix.size());
    }
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->normalImgPath != "")
    {
        //创建QPixmap对象
        QPixmap pix;
        //判断石头能够加载图片，若不能提示加载失败
        bool ret = pix.load(normalImgPath);
        if(!ret)
        {
            qDebug()<<normalImgPath<<"加载图片失败!";
            return;
        }
        //设置图片固定尺寸 和图片大小相同
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片的样式表
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(pix.size());
    }
    return QPushButton::mouseReleaseEvent(e);
}
