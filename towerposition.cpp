#include "towerposition.h"
#include <QPainter>

const QSize TowerPosition::m_fixedSize(60,29);

TowerPosition::TowerPosition(QPoint pos, const QPixmap &sprite):
    m_hasTower(false),
    m_hasTowerSlow(false),
    m_hasTowerIce(false),
    m_pos(pos),
    m_sprite(sprite) {}

QPoint TowerPosition::centerPos() const
{//返回可放塔的位置的中心点
    QPoint offsetPoint(m_fixedSize.width()/2,m_fixedSize.height()/2);
    return m_pos+offsetPoint;
}

bool TowerPosition::containPoint(const QPoint &pos) const
{//判断某点是否在可放塔的位置内
    bool isXInHere=m_pos.x()<pos.x()&&pos.x()<(m_pos.x()+m_fixedSize.width());
    bool isYInHere=m_pos.y()<pos.y()&&pos.y()<(m_pos.y()+m_fixedSize.height());
    return isXInHere && isYInHere;
}

bool TowerPosition::hasTower() const{
    return m_hasTower;
}

void TowerPosition::setHasTower(bool hasTower){
    m_hasTower=hasTower;
}

void TowerPosition::draw(QPainter *painter) const{
    if(!m_hasTower&&!m_hasTowerSlow&&!m_hasTowerIce)
    painter->drawPixmap(m_pos.x(),m_pos.y(),m_sprite);
}


void TowerPosition::setwant(bool want){
    m_want=want;
}

bool TowerPosition::getwant(){
    return m_want;
}

void TowerPosition::addlevel(){
    m_level++;
}

int TowerPosition::getlevel(){
    return m_level;
}

void TowerPosition::setHasTowerSlow(bool hasTowerSlow)
{
    m_hasTowerSlow=hasTowerSlow;
}
bool TowerPosition::hasTowerSlow() const
{
    return m_hasTowerSlow;
}
void TowerPosition::setHasTowerIce(bool hasTowerIce)
{
    m_hasTowerIce=hasTowerIce;
}
bool TowerPosition::hasTowerIce() const
{
    return m_hasTowerIce;
}
