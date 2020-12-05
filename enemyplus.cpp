#include "enemyplus.h"
#include "enemy.h"
#include "waypoint.h"
#include "tower.h"
#include"towerplus.h"
#include"towerplusplus.h"
#include "utility.h"
#include "mainwindow.h"
//#include "audioplayer.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

static const int Health_Bar_Width = 70;

//const QSize EnemyPlus::ms_fixedSize(60, 72);

EnemyPlus::EnemyPlus(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite/* = QPixmap(":/image/enemyplus.jpg")*/)
    :Enemy(startWayPoint, game, sprite)
{           m_game = game;

            m_maxHp= 50;
            m_currentHp= 50;
            m_walkingSpeed= 4.0;
            m_rotationSprite = 0.0;
            m_gold = 500;
}

EnemyPlus::~EnemyPlus()
{
    m_attackedTowersList.clear();
    m_destinationWayPoint = nullptr;
    m_game = nullptr;
}

void EnemyPlus::doActivate()
{
    m_active = true;
}

void EnemyPlus::draw(QPainter *painter) const
{
    if (!m_active)
        return;

    painter->save();

    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 2 - 5, -ms_fixedSize.height() /2 );
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 5));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 5));
    painter->drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    // 绘制敌人
    painter->drawPixmap(offsetPoint, m_sprite);

    painter->restore();
}

void EnemyPlus::getRemoved()
{
    if (m_attackedTowersList.empty())
        return;

    foreach (Tower *attacker, m_attackedTowersList)
        attacker->targetKilled();
    // 通知game,此敌人已经阵亡
    m_game->awardGold(m_gold);
    m_game->removedEnemy(this);
}
