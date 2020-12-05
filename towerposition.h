#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H
#include <QPoint>
#include <QSize>
#include <QPixmap>

class QPainter;

class TowerPosition{
public:
    TowerPosition(QPoint pos, const QPixmap &sprite = QPixmap(":/image/towerposition.png"));

    void setHasTower(bool hasTower = true);
    void setHasTowerplusplus(bool hasTowerplusplus = true);
    bool hasTower() const;
    QPoint centerPos() const;
    bool containPoint(const QPoint &pos) const;

    void draw(QPainter *painter) const;

    void setHasTowerSlow(bool hasTowerSlow = true);
    bool hasTowerSlow() const;

    void setHasTowerIce(bool hasTowerIce = true);
    bool hasTowerIce() const;

    void setwant(bool want = true);
    bool getwant();

    void addlevel();
    int getlevel();

private:
    bool m_hasTower;
    bool m_hasTowerSlow;
    bool m_hasTowerIce;
    int m_level=1;
    bool m_want;
    QPoint m_pos;
    QPixmap m_sprite;
    static const QSize m_fixedSize;
};

#endif // TOWERPOSITION_H
