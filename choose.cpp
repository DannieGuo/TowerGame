#include "choose.h"
#include "ui_choose.h"
#include "mainwindow.h"
Choose::Choose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Choose)
{
    ui->setupUi(this);
    connect(ui->Round1, SIGNAL(clicked()), this, SLOT(Round1_clicked()));
    connect(ui->pushButton,SIGNAL(clicked()),this, SLOT(pushButton_clicked()));
}

Choose::~Choose()
{
    delete ui;
}

void Choose::setwin(bool win){
    m_win=win;
}

void Choose::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0,0,1370,750,QPixmap(":/image/finish.png"));
    if(m_win) painter.drawPixmap(300,50,690,418,QPixmap(":/image/win.png"));//根据输赢显示不同的图
    else painter.drawPixmap(300,50,690,418,QPixmap(":/image/defeat.png"));
}

void Choose::on_Round1_clicked()//选择第一关
{
    MainWindow *mw=new MainWindow();
    mw->setRound(1);
    mw->Load();
    mw->show();
    this->close();
}

void Choose::on_pushButton_2_clicked()//选择第二关
{
    MainWindow *mw=new MainWindow();
    mw->setRound(2);
    mw->Load();
    mw->show();
    this->close();
}

void Choose::on_pushButton_clicked()
{
    return;
}
