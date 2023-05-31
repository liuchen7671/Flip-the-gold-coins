#ifndef CHOOSELEVESCENE_H
#define CHOOSELEVESCENE_H

#include <QMainWindow>
#include "playscene.h"
#include <QSound>

class ChooseLeveScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLeveScene(QWidget *parent = nullptr);

    //重写绘图事件
    void paintEvent(QPaintEvent *event);

    //游戏场景对象指针
    PlayScene * play = NULL;

signals:
    //自定义信号
    void chooseSceneBack();

};

#endif // CHOOSELEVESCENE_H
