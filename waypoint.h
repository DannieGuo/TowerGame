#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QPoint>
#include <QPainter>

class WayPoint{
public:
    WayPoint(QPoint pos);

    void setNextWayPoint(WayPoint *nextPoint);
    WayPoint* nextWayPoint() const;
    const QPoint pos() const;

    void draw(QPainter *painter) const;

private:
    QPoint m_pos;
    WayPoint* m_nextWayPoint;
};

#endif // WAYPOINT_H
