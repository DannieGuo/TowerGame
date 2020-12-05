#ifndef TOWERPLUS_H
#define TOWERPLUS_H
#include <QObject>
#include <QSize>
#include <QPoint>
#include <QPixmap>
#include <QTimer>
#include "tower.h"

class MainWindow;

class TowerPlus : public Tower
{
public:
    TowerPlus(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/towerplus.png") );
    void draw(QPainter *painter) const;

    static const QSize ms_fixedSize;
};

#endif // TOWERPLUS_H
