#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"
#include<QPropertyAnimation>
#include <QSound>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    //重写构造函数
    PlayScene(int levelNum);

    int levelIndex;//内部成员属性 记录所选的关卡

    //重写paintEvent事件
    void paintEvent(QPaintEvent *event);

    int gameArray[4][4];//二维数组数据

    MyCoin * coinBtn[4][4];//维护金币

    //是否胜利的标志
    bool isWin;

signals:
    //自定义信号
    void chooseSceneBack();

};

#endif // PLAYSCENE_H
