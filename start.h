#ifndef START_H
#define START_H

#include <QWidget>
#include <QPainter>
#include <QMediaPlayer>

namespace Ui {
class Start;
}

class Start : public QWidget
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = 0);
    ~Start();
private slots:
    void paintEvent(QPaintEvent *);
    void on_startgame_clicked();
    void on_exit_clicked();

private:
    Ui::Start *ui;
};

#endif // START_H
