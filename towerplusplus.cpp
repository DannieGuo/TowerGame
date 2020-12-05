#include "towerplusplus.h"
#include "mainwindow.h"
#include <QPainter>
#include <QSize>
const QSize TowerPlusPlus::ms_fixedSize(100, 100);

TowerPlusPlus::TowerPlusPlus(QPoint pos, MainWindow *game, const QPixmap &sprite)
    :Tower(pos, game, sprite) {
    m_game = game;
    m_attackRange = 250;
    m_damage = 15;
    m_fireRate = 100;
}

void TowerPlusPlus::draw(QPainter *painter) const {
    painter->setPen(Qt::white);
    QPixmap circle = QPixmap(":/image/circle_red.png");
    painter->drawPixmap(m_pos.x() - m_attackRange, m_pos.y() - m_attackRange, m_attackRange * 2, m_attackRange * 2, circle);
    painter->drawPixmap(m_pos.x() - ms_fixedSize.width() / 2, m_pos.y() - ms_fixedSize.height() / 2, ms_fixedSize.width(), ms_fixedSize.height(), m_sprite);
}
