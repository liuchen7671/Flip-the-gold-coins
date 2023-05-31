#include "chooselevescene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include<QTimer>
#include<QLabel>

ChooseLeveScene::ChooseLeveScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(320,588);

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    //创建退出菜单项
    QAction * quitAction = startMenu->addAction("退出");

    //点击退出  实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //加载音效
    QSound * chooseSound = new QSound(":/res/TapButtonSound.wav");//点击关卡音效
    QSound * backSound = new QSound(":/res/BackButtonSound.wav");//点击返回音效

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        //qDebug()<<"释放了返回按钮";
        //告诉主场景 我返回了，主场景监听chooseSceneBack的返回按钮
        //播放返回音效
        backSound->play();
        //延时返回
        QTimer::singleShot(150,this,[=](){
            emit this->chooseSceneBack();
        });
    });

    //创建选择关卡的按钮
    for(int i = 0; i < 20; i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + i % 4 * 70, 130 + i / 4 * 70);

        //监听每个按钮的点击事件
        connect(menuBtn,&MyPushButton::clicked,[=](){
            QString str = QString("您选择的是第%1关").arg(i+1);
            qDebug()<<str;
            //点击关卡音效
            chooseSound->play();
            //进入到游戏场景
            this->hide();//隐藏选择窗口


            play = new PlayScene(i+1);//创建游戏场景
            //重新确定显示位置
            play->setGeometry(this->geometry());

            play->show();//显示游戏场景
            //监听返回
            connect(play, &PlayScene::chooseSceneBack,[=](){
                play->hide();
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play = nullptr;
            });

        });

        QLabel * label = new QLabel(menuBtn);//父亲设置成按钮就不需要移动了
        label->setFixedSize(menuBtn->size());
        label->setText(QString::number(i+1));

        //设置label上的文字对其方式  水平居中 垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //让鼠标进行穿透   51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }

}

//重写绘图事件
void ChooseLeveScene::paintEvent(QPaintEvent *event)
{
    //创建画家
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/res/OtherSceneBg.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
