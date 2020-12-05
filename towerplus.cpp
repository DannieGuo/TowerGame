#include "towerplus.h"
#include "mainwindow.h"
#include <QPainter>
#include <QSize>
const QSize TowerPlus::ms_fixedSize(100, 100);

TowerPlus::TowerPlus(QPoint pos, MainWindow *game, const QPixmap &sprite)
    :Tower(pos, game, sprite) {
    m_game = game;
    m_attackRange = 200;
    m_damage = 10;
    m_fireRate = 300;
}

void TowerPlus::draw(QPainter *painter) const
{
    QPixmap circle = QPixmap(":/image/circle_red.png");
    painter->drawPixmap(m_pos.x()-m_attackRange, m_pos.y()-m_attackRange, m_attackRange*2, m_attackRange*2, circle);
    painter->drawPixmap(m_pos.x()-ms_fixedSize.width()/2, m_pos.y()-ms_fixedSize.height()/2, ms_fixedSize.width(), ms_fixedSize.height(), m_sprite);
}

