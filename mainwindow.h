#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "tower.h"
#include "towerplus.h"
#include "towerplusplus.h"
#include "arrow.h"
#include "waypoint.h"
#include "enemy.h"
#include "enemyplus.h"
#include "bullet.h"
#include "enemyangry.h"
#include <QMediaPlayer>
class Ice;
class Venom;
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void getHpDamage(int damage = 1);
    void removedEnemy(Enemy *enemy);
    void removedBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
    void awardGold(int gold);

    QList<Enemy *> enemyList() const;
    QList<Ice *> m_iceList;
    QList<Venom *> m_venomList;
    QList<Angry *> m_angryList;

    bool canBuyTower();
    bool canBuyTowerSlow();
    bool canBuyTowerIce();
    bool canBuyTowerPlus(int type,int level);

    void setRound(int n);
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);
    void drawRound(QPainter *painter);
    void GameOver();

    void Load();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);



private slots:
    void updateMap();
    void gameStart();

    void Build_tower();
    void Build_towerslow();
    void Build_towerice();
    void towerup();
    void clear();


private:
    void loadTowerPositionMap1();
    void addWayPointMap1();
    void addWayPoint2Map1();

    void loadTowerPositionMap2();
    void addWayPointMap2();
    void addWayPoint2Map2();
    void addWayPoint3Map2();

    void loadWaveMap1();
    void loadWaveMap2();

    void loadMenu();
    void setMenustyle(QMenu *me);

private:
    Ui::MainWindow * ui;
    int m_round;
    int m_waves;
    int m_playerHp;
    int	 m_playerGold;
    static int towerCost[3];
    static int towerslowCost[3];
    static int towericeCost[3];
    bool m_gameEnded;
    bool m_gameWin;

private:
    QMenuBar* menuBar;
    QStatusBar* status;
    QList<QMenu *> m_menu;
    QList<QAction *> m_action;
    QList<TowerPosition> m_towerPositionsList;
    QList<Tower *> m_towersList;
    QList<WayPoint *> m_wayPointsList;
    QList<WayPoint*> m_wayPointsList2;
    QList<WayPoint*> m_wayPointsList3;
    QList<Enemy *> m_enemyList;
    QList<Bullet *> m_bulletList;
    QList<Arrow*> m_arrowsList;
};

#endif // MAINWINDOW_H
