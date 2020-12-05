#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "mainwindow.h"
#include "utility.h"
#include <QTimer>
#include <QVector2D>

const QSize Tower::ms_fixedSize(55,67);

Tower::Tower(QPoint pos, MainWindow *game, int level,const QPixmap &sprite):
    m_pos(pos),
    m_attackRange(100),
    m_damage(5),
    m_fireRate(500),
    m_attacking(false),
    m_chooseEnemy(nullptr),
    m_game(game),
    m_sprite(sprite),
    m_level(level)
    //m_rotationSprite(0.0)
{
    m_fireRateTimer=new QTimer(this);
    connect(m_fireRateTimer,SIGNAL(timeout()),this,SLOT(shootWeapon()));
}

Tower::~Tower(){
    delete m_fireRateTimer;
    m_fireRateTimer=nullptr;
}

QPoint Tower::Pos() const
{
    return m_pos;
}

void Tower::draw(QPainter *painter)
{
    painter->save();
    QPixmap circle=QPixmap(":/image/circle_red.png");
    painter->drawPixmap(m_pos.x()-m_attackRange,m_pos.y()-m_attackRange,m_attackRange*2,m_attackRange*2,circle);

    static const QPoint offsetPoint(-ms_fixedSize.width()/2,-ms_fixedSize.height()/2);
    painter->translate(m_pos);
    if(m_level==2){//根据不同的level判断当前该画那个塔
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
    }else{
        painter->drawPixmap(offsetPoint,QPixmap(":/image/Towerordinary_level1.png"));
    }
    painter->restore();
}

void Tower::checkEnemyInRange()//判断敌人是否在攻击范围内
{
    if(m_chooseEnemy)
    {
        if(!collisionWithCircle(m_pos,m_attackRange,m_chooseEnemy->pos(),1))
        {
            lostSightOfEnemy();
        }
    }else
    {
        QList<Enemy *>enemyList=m_game->enemyList();
        foreach(Enemy *enemy,enemyList)//遍历每一个敌人
        {
            if(collisionWithCircle(m_pos,m_attackRange,enemy->pos(),1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}

void Tower::lostSightOfEnemy()//敌人已出攻击范围
{
    m_chooseEnemy->gotLostSight(this);
    if(m_chooseEnemy)
        m_chooseEnemy=nullptr;
    m_fireRateTimer->stop();
}

void Tower::attackEnemy()//攻击敌人
{
    m_fireRateTimer->start(m_fireRate);
}

void Tower::chooseEnemyForAttack(Enemy *enemy)//选择要攻击的敌人
{
    m_chooseEnemy = enemy;
    attackEnemy();
    m_chooseEnemy->getAttacked(this);
}

void Tower::shootWeapon()//bullet
{
    Bullet *bullet = new Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet->move();
    m_game->addBullet(bullet);
}

void Tower::targetKilled()
{
    if(m_chooseEnemy)
        m_chooseEnemy=nullptr;
    m_fireRateTimer->stop();
}

