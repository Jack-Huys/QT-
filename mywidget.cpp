#include "mywidget.h"
#include <QPushButton>
#include "mypushbutton.h"
#include <QDebug>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton * button = new QPushButton();
    //button->show();
    button->setParent(this);
    button->setText("按钮");

    QPushButton * button2 = new QPushButton("第二个按钮", this);
    button2->move(100,100);
    //重置窗口大小
    resize(600, 400);
    //设置固定大小
    setFixedSize(600,400);
    //设置窗口标题
    setWindowTitle("第一个窗口");

    MyPushButton *mybut = new MyPushButton();
    mybut->setText("我自己的按钮");
    mybut->move(300,0);
    mybut->setParent(this);//设置到对象树中

    //点击按钮，关闭窗口
    connect(button2, &QPushButton::clicked, this, &MyWidget::close );

    connect(mybut, &MyPushButton::clicked, this, &MyWidget::close);
}

MyWidget::~MyWidget()
{
    qDebug() << "mywidget的析构函数";
}

