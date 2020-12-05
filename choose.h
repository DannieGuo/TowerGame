#ifndef CHOOSE_H
#define CHOOSE_H

#include <QWidget>

namespace Ui {
class Choose;
}

class Choose : public QWidget
{
    Q_OBJECT

public:
    void setwin(bool win);
    explicit Choose(QWidget *parent = nullptr);
    ~Choose();

private slots:
    void on_Round1_clicked();
    void paintEvent(QPaintEvent *);
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    bool m_win;
    Ui::Choose *ui;
};

#endif // CHOOSE_H
