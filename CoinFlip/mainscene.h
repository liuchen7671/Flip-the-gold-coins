#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "chooselevescene.h"
#include <QSound>//多媒体模块下 的音效头文件

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //重写画家事件
    void paintEvent(QPaintEvent *event);

    ChooseLeveScene *chooseScene = nullptr;

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
