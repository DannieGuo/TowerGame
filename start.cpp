#include "start.h"
#include "ui_start.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include "choose.h"
#include <QMediaPlayer>
Start::Start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
    connect(ui->startgame, SIGNAL(clicked()), this, SLOT(startgame_clicked()));
    connect(ui->exit, SIGNAL(clicked()), this, SLOT(on_exit_clicked()));

  /*  QMediaPlayer * player = new QMediaPlayer;
    //player->setMedia(":/sounds/2953.mp3");
    player->setMedia(QUrl("qrc:/music/bgm.mp3"));
    player->setVolume(30);
    player->play();*/

}

Start::~Start()
{
    delete ui;
}

void Start::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0,0,1300,750,QPixmap(":/image/start.png"));
}

void Start::on_startgame_clicked()//点击游戏开始的键后
{
    MainWindow *mw = new MainWindow();
    mw->setRound(1);//设置关卡为1
    mw->Load();//加载关卡1中的位置路径等
    mw->show();//显示第一关
    this->close();//关掉开始的界面

}

void Start::on_exit_clicked()
{
    qApp->exit();
}

