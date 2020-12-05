#ifndef ENEMYPLUS_H
#define ENEMYPLUS_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include "enemy.h"

class WayPoint;
class QPainter;
class MainWindow;
class Tower;
class TowerPlus;
class TowerPlusPlus;

class EnemyPlus : public Enemy//, public QObject
{
    Q_OBJECT
public:
    EnemyPlus(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/enemyplus.jpg"));
    ~EnemyPlus();
    void draw(QPainter *painter) const;
    void getRemoved();

    //QPoint pos() const;
//signals:

public slots:
    void doActivate();

/*private:

    bool m_active;
    int 	m_maxHp;
    int	 m_currentHp;
    qreal m_walkingSpeed;
    qreal m_rotationSprite;

    QPoint m_pos;
    WayPoint * m_destinationWayPoint;
    MainWindow * m_game;
    QList<Tower *> m_attackedTowersList;
    const QPixmap m_spritee;
    static const QSize ms_fixedSize;
*/
};

#endif // ENEMYPLUS_H


