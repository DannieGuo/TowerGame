#include "enemy.h"
#include "enemyangry.h"
#include "mainwindow.h"
#include "waypoint.h"
#include "utility.h"
#include "towerice.h"
#include "towerslow.h"
static const int Health_Bar_Width = 20;

EnemyAngry::EnemyAngry(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite):
    Enemy(startWayPoint,game,sprite)
{
    angryenemy=true;
}

EnemyAngry::~EnemyAngry() {}

void EnemyAngry::getDamage(int damage){
    //m_game->audioPlayer()->playSound(LaserShootSound);
    m_currentHp -= damage;

    if(!getice&&!m_alreadyangry&&m_currentHp <=m_maxHp/3){
        getAngry();
        m_alreadyangry=true;
    }

    // 阵亡,需要移除
    else if (m_currentHp <= 0)
    {
        //m_game->audioPlayer()->playSound(EnemyDestorySound);
        //m_game->awardGold(200);
        getRemoved();
    }
}

void EnemyAngry::getRemoved()
{
    if (m_attackedTowersList.empty())
        return;

    foreach (Tower *attacker, m_attackedTowersList)
        attacker->targetKilled();
    foreach(Ice *ice,m_game->m_iceList){
        if(ice->pos()==m_pos){
            m_game->m_iceList.removeOne(ice);
            break;
        }
    }
    foreach(Venom *venom, m_game->m_venomList){
        if(venom->pos()==m_pos){
            m_game->m_venomList.removeOne(venom);
            break;
        }
    }
    if(m_angry!=nullptr){
        foreach(Angry *angry,m_game->m_angryList){
            if(m_angry->pos()==angry->pos()){
                m_game->m_angryList.removeOne(angry);
                break;
            }
        }
    }

    // 通知game,此敌人已经阵亡
    m_game->awardGold(100);
    m_game->removedEnemy(this);
}

void EnemyAngry::move()
{
    if (!m_active)
        return;

    if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
    {
        // 敌人抵达了一个航点
        if (m_destinationWayPoint->nextWayPoint())
        {
            // 还有下一个航点
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        }
        else
        {
            // 表示进入基地
            m_game->getHpDamage();
            if(m_angry!=nullptr){
                foreach(Angry *angry,m_game->m_angryList){
                    if(m_angry->pos()==angry->pos()){
                        m_game->m_angryList.removeOne(angry);
                        break;
                    }
                }
            }
            m_game->removedEnemy(this);
            return;
        }
    }

    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = m_destinationWayPoint->pos();
    // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值

    // 向量标准化
    qreal movementSpeed = m_walkingSpeed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * movementSpeed;

    m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 180;
}

void EnemyAngry::getAngry(){
    if(m_walkingSpeed!=0) m_walkingSpeed+=1.5;
    m_angry=new Angry(m_pos,m_game,this);
    m_game->m_angryList.push_back(m_angry);
}

void EnemyAngry::draw(QPainter *painter) const{
    if (!m_active)
        return;

    painter->save();
    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 2 - 5, -ms_fixedSize.height() /2);

    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 5));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 5));
    painter->drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上
    painter->translate(m_pos);
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);

    // 绘制敌人
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

Angry::Angry(QPoint &pos, MainWindow *game, Enemy *enemy,const QPixmap &sprite):
    m_pos(pos),
    m_sprite(sprite),
    m_enemy(enemy),
    m_game(game) {}

Angry::~Angry() {}

void Angry::setpos(QPoint pos){
    m_pos=pos;
}

QPoint Angry::pos(){
    return m_pos;
}

void Angry::draw(QPainter *painter) const{
    painter->drawPixmap(m_pos,m_sprite);
}
