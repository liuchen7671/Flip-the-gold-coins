#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QDebug>
#include<QTimer>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置窗口固定大小
    this->setFixedSize(320,588);

    //设置应用图片
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置窗口标题
    this->setWindowTitle("翻金币");

    //退出按钮实现
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });

    //准备开始按钮的音效
    QSound *startSound = new QSound(":/res/TapButtonSound.wav");
//    startSound->setLoops(-1);//设置播放次数 无限循环-1
//    startSound->play();

    //开始按钮
    MyPushButton * startBtn  =new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5,this->height() * 0.7);

    connect(startBtn,&MyPushButton::pressed,[=](){
        qDebug()<<"按下了开始";
        //播放开始音效资源
        startSound->play();
        //做一个弹起的特效
        startBtn->zoom1();
    });

    //实例化选择关卡的场景
    chooseScene = new ChooseLeveScene;

    //监听选择关卡的返回按钮的信号
    connect(chooseScene,&ChooseLeveScene::chooseSceneBack,[=](){
        chooseScene->hide();//将选择关卡场景 隐藏掉
        this->setGeometry(chooseScene->geometry());
        this->show();//重新显示
    });

    connect(startBtn,&MyPushButton::released,[=](){
        qDebug()<<"释放了开始";
        //做一个弹起的特效
        startBtn->zoom2();

        //延时进入选择关卡中
        QTimer::singleShot(150,this,[=](){
            //自身隐藏
            this->hide();
            chooseScene->setGeometry(this->geometry());
            //显示选择关卡场景
            chooseScene->show();
        });

    });

}

//重写画家事件
void MainScene::paintEvent(QPaintEvent *event)
{
    //创建画家
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/res/PlayLevelSceneBg.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5,pix.height() * 0.5);
    painter.drawPixmap(10,30,pix);

}

MainScene::~MainScene()
{
    delete ui;
}

