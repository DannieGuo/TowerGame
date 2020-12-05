#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class WayPoint;
class QPainter;
class MainWindow;
class Tower;
class TowerPlus;
class TowerPlusPlus;
class Enemy : public QObject
{
	Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/enemy.png"));
	~Enemy();
    friend class Venom;
    virtual void draw(QPainter *painter) const;
    virtual void move();
    virtual void getDamage(int damage);
    virtual void getRemoved();
    void getAttacked(Tower *attacker);
	void gotLostSight(Tower *attacker);
	QPoint pos() const;
    void addspeed(double add);
    void doSleep();
    bool angryenemy;
    bool getice;
public slots:
	void doActivate();

protected:
    bool m_active;
    bool drawrange;
    int m_maxHp;
    int	 m_currentHp;
    qreal m_walkingSpeed;
    qreal m_rotationSprite;
    int m_gold;
    QPoint m_pos;
    WayPoint * m_destinationWayPoint;
    MainWindow * m_game;
    QList<Tower *> m_attackedTowersList;
    const QPixmap m_sprite;
	static const QSize ms_fixedSize;
};

#endif // ENEMY_H
