#ifndef TOWERPLUSPLUS_H
#define TOWERPLUSPLUS_H


#include <QObject>
#include <QSize>
#include <QPoint>
#include <QPixmap>
#include <QTimer>
#include "tower.h"
class MainWindow;

class TowerPlusPlus : public Tower
{
public:
    TowerPlusPlus(QPoint pos,MainWindow *game,const QPixmap &sprite = QPixmap(":/image/towerplusplus.png") );
    void draw(QPainter *painter) const;


    static const QSize ms_fixedSize;
};
#endif // TOWERPLUSPLUS_H
