#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waypoint.h"
#include "enemy.h"
#include "enemyangry.h"
#include "bullet.h"
#include "tower.h"
#include "towerslow.h"
#include "towerice.h"
#include "choose.h"
#include "customiconstyle.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QAction>
#include <QMainWindow>
#include <QMediaPlayer>
//#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_waves(0),
    m_playerHp(5),
    m_playerGold(1000),
    m_gameEnded(false),
    m_gameWin(false),
    m_round(0)
{
    ui->setupUi(this);

    QCursor cursor ;
    QPixmap pixmap(":/image/cursor.png") ;
    cursor = QCursor(pixmap,-1,-1);
    setCursor(cursor) ;

    loadMenu();

    Load();

    QMediaPlayer * player = new QMediaPlayer;
    //player->setMedia(":/sounds/2953.mp3");
    player->setMedia(QUrl("qrc:/music/bgm.mp3"));
    player->setVolume(30);
    player->play();

    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateMap()));
    timer->start(30);

    QTimer::singleShot(300,this,SLOT(gameStart()));

    //connect(ui->exit, SIGNAL(clicked()), this, SLOT(exit_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::towerCost[]={150,150,200};
int MainWindow::towerslowCost[]={200,250,250};
int MainWindow::towericeCost[]={250,250,300};

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter1(this);
    if (m_gameEnded || m_gameWin){
        Choose *choose=new Choose();
        if(m_gameWin) choose->setwin(true);
        if(m_gameEnded) choose->setwin(false);
        choose->show();
        this->close();
        return;
    }

    if(m_round==1)
    {
         painter1.drawPixmap(0,0,1300,750,QPixmap(":/image/map1.png"));
    }
    if(m_round==2)
    {
        painter1.drawPixmap(0,0,1300,750,QPixmap(":/image/map2.png"));
    }

    QPen pen;
    pen.setColor(QColor(0,0,0,200));
    painter1.setPen(pen);

    QPainter painter2(this);
    painter2.drawPixmap(650,230,100,90,QPixmap(":/image/towerboss1.png"));


    QPainter painter(this);

    foreach (const TowerPosition &towerPos, m_towerPositionsList)
        towerPos.draw(&painter);

    foreach(Tower *tower,m_towersList)
        tower->draw(&painter);

    foreach(const Enemy *enemy, m_enemyList)
        enemy->draw(&painter);

    foreach(const Bullet *bullet, m_bulletList)
        bullet->draw(&painter);

    foreach(const Ice *ice,m_iceList)
        ice->draw(&painter);

    foreach(const Venom *venom,m_venomList)
        venom->draw(&painter);

    foreach(const Angry *angry,m_angryList)
        angry->draw(&painter);


    drawPlayerGold(&painter);
    drawHP(&painter);
    drawWave(&painter);
    //drawRound(&painter);
}

void MainWindow::setRound(int n)
{
    m_round=n;
}
void MainWindow::Load()//根据不同的关卡加载不同的坐标
{
    if(m_round==1)
    {
        loadTowerPositionMap1();
        addWayPointMap1();
        addWayPoint2Map1();
    }

    if(m_round==2)
    {
        loadTowerPositionMap2();
        addWayPointMap2();
        addWayPoint2Map2();
        addWayPoint3Map2();
    }
}
void MainWindow::drawPlayerGold(QPainter *painter)//
{
    painter->setPen(QPen(Qt::white));
    QFont font1("宋体",15);
    painter->setFont(font1);
    painter->drawText(QRect(1220, 320, 100, 30), QString("%1").arg(m_playerGold));
}

void MainWindow::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::white));
    QFont font1("宋体",15);
    painter->setFont(font1);
    painter->drawText(QRect(1220,140,100,30),QString("%1").arg(m_playerHp));
}

void MainWindow::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::white));
    QFont font1("宋体",15);
    painter->setFont(font1);
    painter->drawText(QRect(1250,470,100,30),QString("%1").arg(m_waves));
}
void MainWindow::drawRound(QPainter *painter)
{
    painter->setPen(QPen(Qt::white));
    QFont font1("宋体",15);
    painter->setFont(font1);
    painter->drawText(QRect(1820,290,100,30),QString("Round"));
    painter->drawText(QRect(1820,330,100,30),QString("%1").arg(m_round));
}
void MainWindow::loadTowerPositionMap1()
{
    QPoint pos[]=
        {
            QPoint(300,275),
            QPoint(500,200),
            QPoint(65,540),
            QPoint(465,390),
            QPoint(230,580),
            QPoint(420,520),
            QPoint(690,520),
            QPoint(860,350),
            QPoint(860,580)
        };
            for (int i=0;i<9;++i)
            {
                m_towerPositionsList.push_back(pos[i]);
            }
}
void MainWindow::loadTowerPositionMap2()
{
    QPoint pos[]=
        {
            QPoint(80,120),
            QPoint(450,250),
            QPoint(280,460),
            QPoint(490,410),
            QPoint(860,370),
            QPoint(686,610),
            QPoint(450,600),
            QPoint(530,150),
            QPoint(16,530)
        };
            for (int i=0;i<9;++i)
            {
                m_towerPositionsList.push_back(pos[i]);
            }
}
void MainWindow::setMenustyle(QMenu *me){
    CustomIconStyle *pstyle=new CustomIconStyle;
    me->setStyle(pstyle);
    me->setStyleSheet(
                         "\
                         QMenu {\
                         background-color:rgb(89,87,87); /*整个背景*/\
                         border: 2px solid rgb(235,110,36);\
                         }\
                     QMenu::icon {\
                         \
                         }\
                     QMenu::item {\
                         font-size: 10pt; \
                         color: rgb(225,225,225);  /*字体颜色*/\
                         border: 1px solid rgb(60,60,60);    /*item选框*/\
                         background-color:rgb(89,87,87);\
                         padding:2px 5px; /*设置菜单项文字上下和左右的内边距，效果就是菜单中的条目左右上下有了间隔*/\
                         margin:1px 1px;/*设置菜单项的外边距*/\
                          }\
                     QMenu::item:selected { \
                         background-color:rgb(235,110,110);/*选中的样式*/\
                         }\
                     QMenu::item:pressed {/*菜单项按下效果*/\
                                               border: 1px solid rgb(60,60,61); \
                                               background-color: rgb(220,80,6); \
                                           }\
                        ");
}

void MainWindow::loadMenu(){

    QAction *act1=new QAction(QIcon(":/image/addtower.png"),"普通塔 ￥150 普通射击      ",this);
    m_action.push_back(act1);
    connect(m_action[0],SIGNAL(triggered()),this,SLOT(Build_tower()));

    QAction *act2=new QAction(QIcon(":/image/addtower.png"),"绿液塔 ￥200 射中敌人会减速      ",this);
    m_action.push_back(act2);
    connect(m_action[1],SIGNAL(triggered()),this,SLOT(Build_towerslow()));

    QAction *act3=new QAction(QIcon(":/image/addtower.png"),"冰塔 ￥250 一定概率让敌人静止       ",this);
    m_action.push_back(act3);
    connect(m_action[2],SIGNAL(triggered()),this,SLOT(Build_towerice()));


    QAction *act4=new QAction("towerboss",this);
    m_action.push_back(act4);
    connect(m_action[3],SIGNAL(triggered()),this,SLOT(clear()));

    QAction *act[6]={
        new QAction(QIcon(":/image/up.png"),"升级 ￥150 中级普通塔       ",this),
        new QAction(QIcon(":/image/up.png"),"升级 ￥200 高级普通塔       ",this),
        new QAction(QIcon(":/image/up.png"),"升级  ￥250  毒液塔        ",this),
        new QAction(QIcon(":/image/up.png"),"升级  ￥250  剧毒塔        ",this),
        new QAction(QIcon(":/image/up.png"),"升级  ￥250  寒冰塔        ",this),
        new QAction(QIcon(":/image/up.png"),"升级  ￥350  冰裂塔        ",this)
    };
    for(int i=0;i<6;i++){
        connect(act[i],SIGNAL(triggered()),this,SLOT(towerup()));
        m_action.push_back(act[i]);
    }

    QMenu *me1=new QMenu("tower",this);
    setMenustyle(me1);
    me1->addAction(m_action[0]);
    me1->addAction(m_action[1]);
    me1->addAction(m_action[2]);
    m_menu.push_back(me1);

    QMenu *me2[3]={
        new QMenu("towerlevel2",this),
        new QMenu("towericelevel2",this),
        new QMenu("towerslowlevel2",this),
    };
    QMenu *me3[3]={
        new QMenu("towerlevel3",this),
        new QMenu("towericelevel3",this),
        new QMenu("towerslowlevel3",this),
    };
    for(int i=0;i<3;i++){
        setMenustyle(me2[i]);
        me2[i]->addAction(m_action[4+2*i]);
        m_menu.push_back(me2[i]);
    }
    for(int i=0;i<3;i++){
        setMenustyle(me3[i]);
        me3[i]->addAction(m_action[5+2*i]);
        m_menu.push_back(me3[i]);
    }



}
void MainWindow::Build_tower()
{
    if(canBuyTower()){//如果钱足够买塔
            auto it=m_towerPositionsList.begin();
            while(it !=m_towerPositionsList.end()){
                if(it->getwant()&&canBuyTower())
                {
                   it->setHasTower();
                    m_playerGold=m_playerGold-towerCost[0];
                    Tower *tower=new Tower(it->centerPos(),this);
                    m_towersList.push_back(tower);
                    update();
                    it->setwant(false);
                    break;
                }
                 ++it;
            }
        }
}

void MainWindow::Build_towerslow()
{
    if(canBuyTowerSlow()){
        auto it=m_towerPositionsList.begin();
        while(it !=m_towerPositionsList.end()){
            if(it->getwant()&&canBuyTowerSlow())
            {
                it->setHasTower();
                it->setHasTowerSlow();
                m_playerGold=m_playerGold-towerslowCost[0];
                TowerSlow *tower=new TowerSlow(it->centerPos(),this);
                m_towersList.push_back(tower);
                update();
                it->setwant(false);
                break;
            }
            ++it;
        }
    }
}
void MainWindow::Build_towerice()
{
    if(canBuyTowerIce()){
        auto it=m_towerPositionsList.begin();
        while(it !=m_towerPositionsList.end()){
            if(it->getwant()&&canBuyTowerIce())
            {
                it->setHasTower();
                it->setHasTowerIce();
                m_playerGold=m_playerGold-towerslowCost[0];
                TowerIce *tower=new TowerIce(it->centerPos(),this);
                m_towersList.push_back(tower);
                update();
                it->setwant(false);
                break;
            }
            ++it;
        }
    }
}

void MainWindow::towerup(){
    auto it=m_towerPositionsList.begin();
    while(it!=m_towerPositionsList.end()){
        if(it->getwant()){
            if(it->hasTowerIce()&&canBuyTowerPlus(1,it->getlevel())){
                it->addlevel();
                foreach(Tower *tower,m_towersList){
                    if(tower->Pos()==it->centerPos()){
                        m_towersList.removeOne(tower);
                        break;
                    }
                }
                m_playerGold-=towerslowCost[it->getlevel()-1];
                TowerIce *towerice=new TowerIce(it->centerPos(),this,it->getlevel());
                m_towersList.push_back(towerice);
                update();
                it->setwant(false);
                break;
            }else if(it->hasTowerSlow()&&canBuyTowerPlus(2,it->getlevel())){
                it->addlevel();
                foreach(Tower *tower,m_towersList){
                    if(tower->Pos()==it->centerPos()){
                        m_towersList.removeOne(tower);
                        break;
                    }
                }
                m_playerGold-=towerslowCost[it->getlevel()-1];
                TowerSlow *towerslow=new TowerSlow(it->centerPos(),this,it->getlevel());
                m_towersList.push_back(towerslow);
                update();
                it->setwant(false);
                break;
            }else if(canBuyTowerPlus(0,it->getlevel())){
                it->addlevel();
                foreach(Tower *tower,m_towersList){
                    if(tower->Pos()==it->centerPos()){
                        m_towersList.removeOne(tower);
                        break;
                    }
                }
                m_playerGold-=towerCost[it->getlevel()-1];
                Tower *tower=new Tower(it->centerPos(),this,it->getlevel());
                m_towersList.push_back(tower);
                update();
                it->setwant(false);
                break;
            }
        }
        ++it;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)//鼠标点击的事件
{
    QPoint pressPos=event->pos();//记下点击点的坐标
    auto it=m_towerPositionsList.begin();
    while(it !=m_towerPositionsList.end())//遍历可放塔的位置
    {
        it->setwant(false);
        if(it->containPoint(pressPos)&&!it->hasTower()){//如果点击点在某个可放塔的位置内
            it->setwant(true);
            m_menu[0]->popup(cursor().pos());
            update();
            break;
        }else//如果有塔,但没有plus,且不在升级状态
            if(it->containPoint(pressPos)&&it->hasTower()&&it->getlevel()<3){
                it->setwant(true);
                if(it->hasTowerIce()){
                    if(it->getlevel()==1) m_menu[3]->popup(cursor().pos());
                    if(it->getlevel()==2) m_menu[6]->popup(cursor().pos());
                }else if(it->hasTowerSlow()){
                    if(it->getlevel()==1) m_menu[2]->popup(cursor().pos());
                    if(it->getlevel()==2) m_menu[5]->popup(cursor().pos());
                }else{
                    if(it->getlevel()==1) m_menu[1]->popup(cursor().pos());
                    if(it->getlevel()==2) m_menu[4]->popup(cursor().pos());
                }
                update();
                break;
            }
        ++it;
    }
}

bool MainWindow::canBuyTower()
{
    if(m_playerGold>=towerCost[0])
    return true;
    else
        return false;
}

bool MainWindow::canBuyTowerSlow()
{
    if(m_playerGold>=towerslowCost[0])
    return true;
    else
        return false;
}
bool MainWindow::canBuyTowerIce()
{
    if(m_playerGold>=towericeCost[0])
    return true;
    else
        return false;
}

bool MainWindow::canBuyTowerPlus(int type,int level){
    switch(type){
    case 0:
        switch(level){
        case 1:
            if(m_playerGold>=towerCost[1])
                return true;
            else
                return false;
        case 2:
            if(m_playerGold>=towerCost[2])
                return true;
            else
                return false;
        }
    case 1:
        switch(level){
        case 1:
            if(m_playerGold>=towericeCost[1])
                return true;
            else
                return false;
        case 2:
            if(m_playerGold>=towericeCost[2])
                return true;
            else
                return false;
        }
    case 2:
        switch(level){
        case 1:
            if(m_playerGold>=towerslowCost[1])
                return true;
            else
                return false;
        case 2:
            if(m_playerGold>=towerslowCost[2])
                return true;
            else
                return false;
        }
    }
}

void MainWindow::getHpDamage(int damage/* = 1*/)
{
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        GameOver();
}
void MainWindow::addWayPointMap1()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(720, 260));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(1010, 260));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(1010, 670));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(820, 670));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(820, 455));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(580, 455));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(580, 314));
    m_wayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(440, 314));
    m_wayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

    WayPoint *wayPoint9 = new WayPoint(QPoint(440, 190));
    m_wayPointsList.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);

    WayPoint *wayPoint10 = new WayPoint(QPoint(240, 190));
    m_wayPointsList.push_back(wayPoint10);
    wayPoint10->setNextWayPoint(wayPoint9);

    WayPoint *wayPoint11 = new WayPoint(QPoint(240, 310));
    m_wayPointsList.push_back(wayPoint11);
    wayPoint11->setNextWayPoint(wayPoint10);

    WayPoint *wayPoint12 = new WayPoint(QPoint(10, 310));
    m_wayPointsList.push_back(wayPoint12);
    wayPoint12->setNextWayPoint(wayPoint11);
}

void MainWindow::addWayPoint2Map1()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(720, 260));
    m_wayPointsList2.push_back(wayPoint1);
   // wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint2 = new WayPoint(QPoint(1010, 260));
    m_wayPointsList2.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(1010, 670));
    m_wayPointsList2.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(820,670));
    m_wayPointsList2.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);


    WayPoint *wayPoint5 = new WayPoint(QPoint(820, 455));
    m_wayPointsList2.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(350, 455));
    m_wayPointsList2.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(350, 650));
    m_wayPointsList2.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(185, 650));
    m_wayPointsList2.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

    WayPoint *wayPoint9 = new WayPoint(QPoint(185, 460));
    m_wayPointsList2.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);

    WayPoint *wayPoint10 = new WayPoint(QPoint(10, 460));
    m_wayPointsList2.push_back(wayPoint10);
    wayPoint10->setNextWayPoint(wayPoint9);

}
void MainWindow::addWayPointMap2()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(1010, 200));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(1010, 600));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(800, 600));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(800, 530));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(620, 530));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(620, 400));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(765, 400));
    m_wayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(765, 260));
    m_wayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

    WayPoint *wayPoint9 = new WayPoint(QPoint(610, 260));
    m_wayPointsList.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);

    WayPoint *wayPoint10 = new WayPoint(QPoint(610, 200));
    m_wayPointsList.push_back(wayPoint10);
    wayPoint10->setNextWayPoint(wayPoint9);

    WayPoint *wayPoint11 = new WayPoint(QPoint(350, 200));
    m_wayPointsList.push_back(wayPoint11);
    wayPoint11->setNextWayPoint(wayPoint10);

    WayPoint *wayPoint12 = new WayPoint(QPoint(350, 260));
    m_wayPointsList.push_back(wayPoint12);
    wayPoint12->setNextWayPoint(wayPoint11);

    WayPoint *wayPoint13 = new WayPoint(QPoint(10, 260));
    m_wayPointsList.push_back(wayPoint13);
    wayPoint13->setNextWayPoint(wayPoint12);
}

void MainWindow::addWayPoint2Map2()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(1010, 200));
    m_wayPointsList2.push_back(wayPoint1);
   // wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint2 = new WayPoint(QPoint(1010, 600));
    m_wayPointsList2.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(800, 600));
    m_wayPointsList2.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(800,530));
    m_wayPointsList2.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);


    WayPoint *wayPoint5 = new WayPoint(QPoint(420, 530));
    m_wayPointsList2.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(420, 405));
    m_wayPointsList2.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(115, 405));
    m_wayPointsList2.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(115, 530));
    m_wayPointsList2.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

    WayPoint *wayPoint9 = new WayPoint(QPoint(205, 530));
    m_wayPointsList2.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);

    WayPoint *wayPoint10 = new WayPoint(QPoint(205, 665));
    m_wayPointsList2.push_back(wayPoint10);
    wayPoint10->setNextWayPoint(wayPoint9);

    WayPoint *wayPoint11 = new WayPoint(QPoint(10, 665));
    m_wayPointsList2.push_back(wayPoint11);
    wayPoint11->setNextWayPoint(wayPoint10);
}

void MainWindow::addWayPoint3Map2()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(1010, 200));
    m_wayPointsList3.push_back(wayPoint1);
   // wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint2 = new WayPoint(QPoint(1010, 600));
    m_wayPointsList3.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(800, 600));
    m_wayPointsList3.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(800,530));
    m_wayPointsList3.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);


    WayPoint *wayPoint5 = new WayPoint(QPoint(620, 530));
    m_wayPointsList3.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(620, 730));
    m_wayPointsList3.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);
}

void MainWindow::awardGold(int gold)
{
    m_playerGold=m_playerGold+gold;
}

void MainWindow::removedEnemy(Enemy *enemy){
    Q_ASSERT(enemy);
    foreach(Venom *venom, m_venomList){
        if(enemy->pos()==venom->pos())
            m_venomList.removeOne(venom);
    }
    m_enemyList.removeOne(enemy);
    delete enemy;
    if(m_enemyList.empty())
    {
        if(m_round==1)
        {
           loadWaveMap1();
        }
        if(m_round==2)
        {
            loadWaveMap2();
        }
    }
}

void MainWindow::loadWaveMap1()
{
   ++m_waves;
    if(m_waves>5)
    {
        m_gameWin=true;
        return ;
    }
    WayPoint *startWayPoint1=m_wayPointsList.back();
    WayPoint *startWayPoint2 = m_wayPointsList2.back(); // 这里是个逆序的，尾部才是其实节点
    qDebug()<<"ccccccccccc";
      int enemyStartInterval[] = { 500, 1500, 2500, 3500, 4500, 5500 };
      for (int i = 0; i < 6; ++i){
          if(rand()%2==0){
              if(rand()%6==0){
                  EnemyAngry *enemy=new EnemyAngry(startWayPoint1,this);
                  m_enemyList.push_back(enemy);
                  QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
              }
              else{
                  Enemy *enemy = new Enemy(startWayPoint1, this);
                  m_enemyList.push_back(enemy);
                  QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
              }
          }
          else{
              if(rand()%6==0){
                  EnemyAngry *enemy=new EnemyAngry(startWayPoint2,this);
                  m_enemyList.push_back(enemy);
                  QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
              }
              else{
                  Enemy *enemy = new Enemy(startWayPoint2, this);
                  m_enemyList.push_back(enemy);
                  QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
              }
          }
      }
}
void MainWindow::loadWaveMap2()
{
   ++m_waves;
    if(m_waves>5)
    {
        m_gameWin=true;
        return ;
    }
    WayPoint *startWayPoint1=m_wayPointsList.back();
    WayPoint *startWayPoint2 = m_wayPointsList2.back(); // 这里是个逆序的，尾部才是其实节点
    WayPoint *startWayPoint3 = m_wayPointsList3.back();
      int enemyStartInterval[] = { 500, 1500, 2500, 3500, 4500, 5500 };
      for (int i = 0; i < 6; ++i)
      {
          if(rand()%3==0)
          {
              if(rand()%6==0)
              {
                  EnemyAngry *enemy=new EnemyAngry(startWayPoint1,this);
                  m_enemyList.push_back(enemy);
                  QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
              }
              else
              {
                  Enemy *enemy = new Enemy(startWayPoint1, this);
                  m_enemyList.push_back(enemy);
                  QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
              }
          }
          else
          if(rand()%3==1)
          {
              if(rand()%6==0){
                  EnemyAngry *enemy=new EnemyAngry(startWayPoint2,this);
                  m_enemyList.push_back(enemy);
                  QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
              }
              else{
                  Enemy *enemy = new Enemy(startWayPoint2, this);
                  m_enemyList.push_back(enemy);
                  QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
              }
          }
          else
              if(rand()%3==2)
              {
                  if(rand()%6==0){
                      EnemyAngry *enemy=new EnemyAngry(startWayPoint3,this);
                      m_enemyList.push_back(enemy);
                      QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
                  }
                  else{
                      Enemy *enemy = new Enemy(startWayPoint3, this);
                      m_enemyList.push_back(enemy);
                      QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
                  }
              }

      }
}

void MainWindow::updateMap()
{
    foreach(Enemy *enemy,m_enemyList)
        enemy->move();
    foreach(Tower *tower,m_towersList)
        tower->checkEnemyInRange();
    foreach(Venom *venom,m_venomList){
        venom->setpos(venom->m_enemy->pos());
        Venom *ve=new Venom(*venom,1);
        m_venomList.removeOne(venom);
        m_venomList.push_back(ve);
    }
    foreach(Angry *angry,m_angryList)
        angry->setpos(angry->m_enemy->pos());
    update();
}

QList <Enemy *> MainWindow::enemyList() const
{
    return m_enemyList;
}

void MainWindow::gameStart()
{
    if(m_round==1)
    {
      loadWaveMap1();
    }
    if(m_round==2)
    {
        loadWaveMap2();
    }
}
void MainWindow::GameOver()
{
        m_gameEnded=true;
        m_gameWin=false;
}

void MainWindow::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void MainWindow::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}

/*
void MainWindow::on_exit_clicked()
{
    Choose *ch=new Choose();
    ch->show();
    this->close();
}*/
void MainWindow::clear()
{
    m_enemyList.clear();
}
