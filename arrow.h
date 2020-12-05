#ifndef ARROW_H
#define ARROW_H
#include <QSize>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include "towerposition.h"

class Arrow{
public:
    Arrow(QPoint pos,const QPixmap &sprite=QPixmap(":/image/update1.png"));
    void draw(QPainter *painter) const;
    bool containPoint(const QPoint &pos) const;
    QPoint pos();
private:
    QPoint m_pos;
    QPixmap m_sprite;
    static const QSize ms_fixedSize;
};

#endif // ARROW_H
