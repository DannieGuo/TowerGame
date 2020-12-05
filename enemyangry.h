#ifndef ENEMYANGRY_H
#define ENEMYANGRY_H

#include "enemy.h"

class Angry;

class EnemyAngry:public Enemy{
public:
    EnemyAngry(WayPoint *startWayPoint, MainWindow *game,const QPixmap &sprite = QPixmap(":/image/enemy1.png"));
    ~EnemyAngry();

    void getDamage(int damage);
    void move();
    void getRemoved();
    void getAngry();
    void draw(QPainter *painter) const;
    Angry * m_angry;
    bool m_alreadyangry=false;
};

class Angry{
public:
    Angry(QPoint &pos, MainWindow *game, Enemy *m_enemy,const QPixmap &sprite=QPixmap(":/image/angry.png"));
    ~Angry();

    void draw(QPainter *painter) const;
    void setpos(QPoint pos);
    QPoint pos();
    Enemy *m_enemy;

private:
    QPoint m_pos;
    QPixmap m_sprite;
    MainWindow *m_game;

};

#endif // ENEMYANGRY_H
