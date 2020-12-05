#ifndef TOWERSLOW_H
#define TOWERSLOW_H

#include "tower.h"
#include <QTime>

class TowerSlow:public Tower{
public:
    TowerSlow(QPoint pos, MainWindow *game, int level = 0, const QPixmap &sprite = QPixmap(":/image/Towervenom_level1.png"));
    void draw(QPainter *painter);
protected:
    void checkEnemyInRange();
    void lostSightOfEnemy();
protected slots:
    void shootWeapon();
};

class Venom{
public:
    Venom(QPoint pos, MainWindow *game, Enemy *enemy, int ty = 0);
    Venom(Venom &venom, int ty);
    ~Venom();
    QPoint pos();
    void setpos(QPoint pos);
    void draw(QPainter *painter) const;
    Enemy *m_enemy;

private:
    int type=0;
    QPoint m_pos;
    MainWindow *m_game;
    QPixmap sprite_1;
    QPixmap sprite_2;
    QPixmap sprite_3;
    QPixmap sprite_4;
    QPixmap sprite_5;
    QPixmap sprite_6;
};

#endif // TOWER2_H
