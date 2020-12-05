#include "towerslow.h"
#include "mainwindow.h"
#include "enemy.h"
#include "utility.h"
#include <QTime>
#include <QPainter>

TowerSlow::TowerSlow(QPoint pos,MainWindow *game,int level,const QPixmap &sprite):
    Tower(pos, game, level, sprite) {}

void TowerSlow::checkEnemyInRange(){
    if(m_chooseEnemy){
        if(!collisionWithCircle(m_pos, m_attackRange, m_chooseEnemy->pos(), 1)){
            if(m_chooseEnemy->angryenemy){
                lostSightOfEnemy();
                return;
            }
            foreach(Venom *venom, m_game->m_venomList){
                if(venom->m_enemy == m_chooseEnemy){
                    m_game->m_venomList.removeOne(venom);
                }
            }
            lostSightOfEnemy();
        }
    } else {
        QList<Enemy *>enemyList = m_game->enemyList();
        foreach(Enemy *enemy, enemyList){
            if(collisionWithCircle(m_pos, m_attackRange, enemy->pos(), 1)) {
                if(enemy->angryenemy){
                    chooseEnemyForAttack(enemy);
                    break;
                }
                enemy->addspeed(-1);
                Venom *venom = new Venom(enemy->pos(), m_game, enemy);
                m_game->m_venomList.push_back(venom);
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}
void TowerSlow::shootWeapon(){
    Bullet *bullet = new Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game,QPixmap(":/image/bulletslow.png"));
    bullet->move();
    m_game->addBullet(bullet);
}
void TowerSlow::lostSightOfEnemy(){
    m_chooseEnemy->gotLostSight(this);
    m_chooseEnemy->addspeed(1);
    if(m_chooseEnemy)
        m_chooseEnemy = nullptr;
    m_fireRateTimer->stop();
    //m_rotationSprite=0.0;
}
void TowerSlow::draw(QPainter *painter){
    painter->save();

    QPixmap circle = QPixmap(":/image/circle_green.png");
    painter->drawPixmap(m_pos.x() - m_attackRange, m_pos.y() - m_attackRange, m_attackRange * 2, m_attackRange * 2, circle);

    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);
    if(m_level == 2){
        painter->drawPixmap(offsetPoint, QPixmap(":/image/Towervenom_level2.png"));
        if(m_attackRange <= 110){
            m_attackRange += 1;
            m_damage = 6;
        }
    } else if(m_level == 3){
        if(m_attackRange == 100) m_attackRange = 110;
        painter->drawPixmap(offsetPoint, QPixmap(":/image/Towervenom_level3.png"));
        if(m_attackRange <= 130){
            m_attackRange += 2;
            m_damage = 9;
            m_fireRate = 400;
        }
    }else{
        painter->drawPixmap(offsetPoint, QPixmap(":/image/Towervenom_level1.png"));
    }
    painter->restore();
}
Venom::Venom(QPoint pos, MainWindow *game, Enemy *enemy, int ty):
    m_enemy(enemy),
    m_pos(pos),
    m_game(game) {
    type = ty;
    sprite_1 = QPixmap(":/image/venom_1.png");
    sprite_2 = QPixmap(":/image/venom_2.png");
    sprite_3 = QPixmap(":/image/venom_3.png");
    sprite_4 = QPixmap(":/image/venom_4.png");
    sprite_5 = QPixmap(":/image/venom_5.png");
    sprite_6 = QPixmap(":/image/venom_6.png");
}

Venom::Venom(Venom &venom, int ty):
    m_enemy(venom.m_enemy),
    m_pos(venom.m_pos),
    m_game(venom.m_game) {
    type = venom.type + ty;
    sprite_1 = QPixmap(":/image/venom_1.png");
    sprite_2 = QPixmap(":/image/venom_2.png");
    sprite_3 = QPixmap(":/image/venom_3.png");
    sprite_4 = QPixmap(":/image/venom_4.png");
    sprite_5 = QPixmap(":/image/venom_5.png");
    sprite_6 = QPixmap(":/image/venom_6.png");
}

Venom::~Venom() {}

QPoint Venom::pos(){
    return m_pos;
}

void Venom::setpos(QPoint pos){
    m_pos = pos;
}

void Venom::draw(QPainter *painter) const{
    if(type%15==0||type%15==1||type%15==2||type%15==3)
        painter->drawPixmap(m_pos.x()-15,m_pos.y()-12,sprite_1);
    else if(type%15==4||type%15==5)
        painter->drawPixmap(m_pos.x()-15,m_pos.y()-12,sprite_2);
    else if(type%15==6||type%15==7)
        painter->drawPixmap(m_pos.x()-15,m_pos.y()-12,sprite_3);
    else if(type%15==8||type%15==9)
        painter->drawPixmap(m_pos.x()-15,m_pos.y()-12,sprite_4);
    else if(type%15==10||type%15==11)
        painter->drawPixmap(m_pos.x()-15,m_pos.y()-12,sprite_5);
    else if(type%15==12||type%15==13||type%15==14)
        painter->drawPixmap(m_pos.x()-15,m_pos.y()-12,sprite_6);
}
