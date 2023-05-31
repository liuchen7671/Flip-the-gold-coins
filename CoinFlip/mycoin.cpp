#include "mycoin.h"
#include <QDebug>

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}

//参数代表传入的金币路径 还是银币路径
MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret)
    {
        qDebug()<<"图片"<<btnImg<<"加载失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(pix.size());
    this->setFocusPolicy(Qt::NoFocus);//键盘无法选中

    //初始化定时器
    this->timer = new QTimer(this);

    //监听正面翻反面的信号并且翻转
    connect(timer,&QTimer::timeout,[=](){
        if(flag)
        {

            QPixmap pix;
            pix.load(QString(":/res/Coin000%1.png").arg(this->max--));
            this->setFixedSize(pix.width(),pix.height());
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(pix);
            this->setIconSize(pix.size());
            //如果翻完了，将max重置为8 停止计时器
            if(max < min)
            {
                this->max = 8;
                timer->stop();
                isAnimation = false;
            }
        }
        else
        {
            QPixmap pix;
            pix.load(QString(":/res/Coin000%1.png").arg(this->min++));
            this->setFixedSize(pix.width(),pix.height());
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(pix);
            this->setIconSize(pix.size());
            //如果翻完了，将min重置为1 停止计时器
            if(min > max)
            {
                this->min = 1;
                timer->stop();
                isAnimation = false;
            }
        }

    });
}

//改变标志，执行翻转效果
void MyCoin::changeFlag()
{
    this->isAnimation = true;
    if(this->flag)
    {
        timer->start(30);
        this->flag = false;
    }
    else
    {
        timer->start(30);
        this->flag = true;
    }


}

//重写按下
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
