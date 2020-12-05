#ifndef TOWERICE_H
#define TOWERICE_H

#include "tower.h"

class MainWindow;

class TowerIce:public Tower{
public:
    TowerIce(QPoint pos, MainWindow *game, int level=1, const QPixmap &sprite = QPixmap(":/image/Towerordinary_level1.png"));
    void draw(QPainter *painter);
protected:
    bool m_sleep;
    void chooseEnemyForAttack(Enemy *enemy);
    void checkEnemyInRange();
    void sleep();
protected slots:
    void shootWeapon();
};

class Ice{
public:
    Ice(QPoint pos, MainWindow *game, const QPixmap &sprite= QPixmap(":/image/ice.png"));
    ~Ice();
    void draw(QPainter *painter) const;
    QPoint pos();

private:
    QPoint m_pos;
    QPixmap m_sprite;
    MainWindow *m_game;
};

#endif // TOWER3_H
