#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);

    //参数代表传入的金币路径 还是银币路径
    MyCoin(QString btnImg);

    //金币的属性
    int posX;//x坐标位置
    int posY;//y坐标位置
    bool flag;//正反标志

    //改变标志，执行翻转效果
    void changeFlag();
    QTimer * timer;//定时器
    int min = 1;//最小图片
    int max = 8;//最大图片

    //执行动画的标志
    bool isAnimation = false;

    //重写按下
    void mousePressEvent(QMouseEvent *e);

    //是否胜利
    bool isWin = false;

signals:

};

#endif // MYCOIN_H
