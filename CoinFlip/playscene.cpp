#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include <mypushbutton.h>
#include <QTimer>
#include <QLabel>
#include <QFont>
#include "mycoin.h"
#include "dataconfig.h"

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

//重写构造函数
PlayScene::PlayScene(int levelNum)
{
    QString str = QString("进入了第%1关").arg(levelNum);
    qDebug()<<str;
    this->levelIndex = levelNum;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");

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
    QSound * backSound = new QSound(":/res/BackButtonSound.wav");//点击返回音效
    QSound * flipSound = new QSound(":/res/ConFlipSound.wav");//翻金币音效
    QSound * winSound = new QSound(":/res/LevelWinSound.wav");


    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        //qDebug()<<"释放了返回按钮";
        //告诉选择场景 我返回了，主场景监听chooseSceneBack的返回按钮
        //播放返回音效
        backSound->play();
        //延时返回
        QTimer::singleShot(150,this,[=](){
            emit this->chooseSceneBack();
        });
    });

    //显示当前的关卡数
    QLabel * label = new QLabel;
    label->setParent(this);
    QString str2 = QString("LeveL:%1").arg(this->levelIndex);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    //将字体设置到标签控件中
     label->setFont(font);
    label->setText(str2);
    label->setGeometry(30,this->height()-50,120,50);//可以直接设置显示区域

    //初始化每个关卡的二维数组
    dataConfig config;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //胜利图片显示
    QLabel * winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width() - tmpPix.width())*0.5,-tmpPix.height());

    //创建金币背景图片
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            //金币背景图片
            QPixmap pix(":/res/BoardNode.png");
            QLabel * label = new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57+i*pix.width(),200+j*pix.height());

            //创建金币按钮
            QString str3;
            if(this->gameArray[i][j] == 1)
            {
                str3 = ":/res/Coin0001.png";
            }
            else
            {
                str3 = ":/res/Coin0008.png";
            }
            MyCoin * coin = new MyCoin(str3);
            coin->setParent(label);
            coin->move(2,4);

            //给金币的属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];//1正面 0反面

            //将金币放入到金币的二维数组里 以便于后期维护
            this->coinBtn[i][j] = coin;

            //点击金币进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                //播放翻金币音效
                flipSound->play();

                //点击按钮后，将所有按钮全部禁用
                for(int i = 0; i < 4; i++)
                {
                    for(int j = 0; j < 4; j++)
                    {
                        this->coinBtn[i][j]->isWin = true;
                    }
                }

                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;

                //延时翻转
                QTimer::singleShot(240,this,[=](){
                    //翻转周围的硬币
                    if(coin->posX + 1 <= 3)//右侧金币翻转条件
                    {
                        coinBtn[coin->posX +1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX +1][coin->posY] = this->gameArray[coin->posX +1][coin->posY] == 0 ? 1 : 0;
                    }
                    //左侧硬币翻转的条件
                    if(coin->posX -1 >= 0)
                    {
                        coinBtn[coin->posX - 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX - 1][coin->posY] = this->gameArray[coin->posX - 1][coin->posY] == 0 ? 1 : 0;
                    }
                    //上侧硬币翻转的条件
                    if(coin->posY - 1 >= 0)
                    {
                        coinBtn[coin->posX][coin->posY - 1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY - 1] = this->gameArray[coin->posX][coin->posY - 1] == 0 ? 1 : 0;
                    }
                    //下侧硬币翻转条件
                    if(coin->posY + 1 <= 3)
                    {
                        coinBtn[coin->posX][coin->posY + 1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY + 1] = this->gameArray[coin->posX][coin->posY + 1] == 0 ? 1 : 0;
                    }

                    //按钮翻转后，将所有按钮全部解禁
                    for(int i = 0; i < 4; i++)
                    {
                        for(int j = 0; j < 4; j++)
                        {
                            this->coinBtn[i][j]->isWin = false;
                        }
                    }

                    //判断是否胜利
                    this->isWin = true;
                    for (int i = 0; i < 4; i++)
                    {
                        for(int j = 0; j < 4; j++)
                        {
                            if(coinBtn[i][j]->flag == false)//只要有一个反面就算失败
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin)
                    {
                        //胜利了
                        //播放胜利音效
                        winSound->play();
                        qDebug()<<"游戏胜利";
                        //将所有按钮的胜利标志改为true 如果再次点击直接退出鼠标按下事件
                        for (int i = 0; i < 4; i++)
                        {
                            for(int j = 0; j < 4; j++)
                            {
                                coinBtn[i][j]->isWin = true;
                            }
                        }

                        //将胜利的图片移动下来
                        QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+160,winLabel->width(),winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //开始动画
                        animation->start();
                    }
                });

            });

        }
    }



}

//重写paintEvent事件
void PlayScene::paintEvent(QPaintEvent *event)
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
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
