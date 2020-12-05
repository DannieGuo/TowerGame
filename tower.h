#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QPixmap>
#include <QObject>
#include <QPainter>
#include <QSize>

#define Original_Fire_Rate 100
#define Original_Attack_Range 150

class MainWindow;
class Enemy;
class MainWindow;
class QTimer;

class Tower:public QObject{
    Q_OBJECT
public:
    Tower(QPoint pos, MainWindow *game, int level = 1,const QPixmap &sprite = QPixmap(":/image/Towerordinary_level1.png"));
    ~Tower();

    virtual void draw(QPainter *painter);

    QPoint Pos() const;

    virtual void checkEnemyInRange();
    void targetKilled();
    void attackEnemy();
    virtual void chooseEnemyForAttack(Enemy *enemy);
    void removeBullt();
    void damageEnemy();
    virtual void lostSightOfEnemy();

protected slots:
    virtual void shootWeapon();



protected:
    const QPoint m_pos;
    int m_attackRange;
    int m_damage;
    int m_fireRate;
    bool m_attacking;
    Enemy *m_chooseEnemy;
    QTimer *m_fireRateTimer;

    MainWindow* m_game;
    const QPixmap m_sprite;
    int m_level = 1;
   // qreal m_rotationSprite;

    static const QSize ms_fixedSize;
};

#endif // TOWER_H
