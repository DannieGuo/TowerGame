#include "towerice.h"
#include "enemy.h"
#include "utility.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPixmap>

TowerIce::TowerIce(QPoint pos,MainWindow *game,int level,const QPixmap &sprite):
    Tower (pos, game,level, sprite) {}

void TowerIce::chooseEnemyForAttack(Enemy *enemy){
    m_chooseEnemy = enemy;
    attackEnemy();
    m_chooseEnemy->getAttacked(this);
    srand(static_cast<unsigned>(time(nullptr)));
    int still=rand()%7;
    if(still==0&&!m_sleep){
        if(enemy->angryenemy){
            EnemyAngry *enemyangry=(EnemyAngry *)enemy;
            if(!enemyangry->m_alreadyangry){
                m_sleep=true;
                enemy->getice=true;
                sleep();
            }
        }else{
            m_sleep=true;
            enemy->getice=true;
            sleep();
        }
    }
}
void TowerIce::shootWeapon(){
    Bullet *bullet = new Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game,QPixmap(":/image/bulletice.png"));
    bullet->move();
    m_game->addBullet(bullet);
}
void TowerIce::checkEnemyInRange(){
    if(m_chooseEnemy){
        if(!collisionWithCircle(m_pos,m_attackRange,m_chooseEnemy->pos(),1)){
            lostSightOfEnemy();
            m_sleep=false;
        }
    }else{
        QList<Enemy *>enemyList=m_game->enemyList();
        foreach(Enemy *enemy,enemyList){
            if(collisionWithCircle(m_pos,m_attackRange,enemy->pos(),1)){
                m_sleep=false;
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}

void TowerIce::sleep(){
    QTimer *timer=new QTimer();
    m_chooseEnemy->doSleep();
    Ice *ice=new Ice(m_chooseEnemy->pos(),m_game);
    m_game->m_iceList.push_back(ice);
    timer->start(30);
    connect(timer,SIGNAL(timeout()),this,SLOT(m_chooseEnemy->sleepover()));
    m_game->update();
}
void TowerIce::draw(QPainter *painter){
    painter->save();

    QPixmap circle=QPixmap(":/image/circle_bule.png");
    painter->drawPixmap(m_pos.x()-m_attackRange,m_pos.y()-m_attackRange,m_attackRange*2,m_attackRange*2,circle);

    static const QPoint offsetPoint(-ms_fixedSize.width()/2,-ms_fixedSize.height()/2);
    painter->translate(m_pos);
    if(m_level==1) painter->drawPixmap(offsetPoint,m_sprite);
    else if(m_level==2){
        painter->drawPixmap(offsetPoint,QPixmap(":/image/Towerordinary_level2.png"));
        if(m_attackRange<=110){
            m_attackRange+=1;
            m_damage=6;
        }
    }
    else if(m_level==3){
        if(m_attackRange==100) m_attackRange=110;
        painter->drawPixmap(offsetPoint,QPixmap(":/image/Towerordinary_level3.png"));
        if(m_attackRange<=130){
            m_attackRange+=2;
            m_damage=9;
            m_fireRate=400;
        }
    }
    painter->restore();
}
Ice::Ice(QPoint pos,MainWindow *game,const QPixmap &sprite):
    m_pos(pos),
    m_sprite(sprite),
    m_game(game) {}

Ice::~Ice() {}

QPoint Ice::pos(){
    return m_pos;
}

void Ice::draw(QPainter *painter) const{

    painter->drawPixmap(m_pos.x()-22,m_pos.y()-20,m_sprite);
}


