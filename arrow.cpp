#include "arrow.h"
#include <QPainter>
#include <QSize>
#include "towerposition.h"

const QSize Arrow::ms_fixedSize(100, 100);

Arrow::Arrow(QPoint pos, const QPixmap &sprite):
    m_pos(pos),
    m_sprite(sprite) {}

void Arrow::draw(QPainter *painter) const{
    painter->drawPixmap(m_pos.x(), m_pos.y(), 100, 100, m_sprite);
}

bool Arrow::containPoint(const QPoint &pos) const{
    if(pos.x() >= m_pos.x() && pos.x() <= (m_pos.x() + ms_fixedSize.width()) 
        && pos.y() >= m_pos.y() && pos.y() <= (m_pos.y() + ms_fixedSize.height()))
        return true;
    return false;
}

QPoint Arrow::pos(){
    return m_pos;
}
