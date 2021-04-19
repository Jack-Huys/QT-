#include "widget.h"
#include "ui_widget.h"

#include <QPushButton>

Widget::Widget(QWidget *parent)  //初始化列表
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //创建老师的对象
    this->ter = new Teachar(this);

    //创建学生的对象
    this->stu = new student(this);
    //信号和槽进行连接
//    connect(ter, &Teachar::hungry, stu, &student::treat);
//    //触发信号函数
//    classOver();

    //连接带参数的信号槽(重载的槽函数)
    //带参和不带参的函数地址不同，connect函数调用一致，编译器无法识别->报错
    //解决：用函数指针-> 函数地址
    void (Teachar::*teacharSignal)(QString) = &Teachar::hungry;
    void (student::*studentSlot)(QString) = &student::treat;
    connect(ter, teacharSignal, stu, studentSlot);
    classOver();

    //点击下课按钮，再触发下课
    QPushButton * btn = new QPushButton("下课", this);
    this->resize(600,400);

    connect(btn, &QPushButton::clicked, this, &Widget::classOver);

    //信号连接信号  信号再连接槽函数
    //信号连接槽函数
    //一个信号可以连接多个槽函数，多个信号可以连接同一个槽函数  -->信号类似广播出去，需要的自己取响应

    //断开连接信号
    //disconnect(ter, teacharSignal, stu, studentSlot);

    //lambda表达式
    //=以值传递方式传递、& 以引用传递
   //mutable 按值传递函数对象时，可以修改值传递的拷贝，不能修改值本身
    //返回值
//    [=]() {
//        btn->setText("classover");
//    }();

    //利用lambda表达式关闭窗口
    QPushButton * btn2 = new QPushButton;
    btn2->setText("关闭");
    btn2->move(100,0);
    btn2->setParent(this);
    connect(btn2, &QPushButton::clicked, this, [=](){
        this->close();
        emit ter->hungry("猪脚饭");
    });

    //test
    QPushButton * button = new QPushButton;
    button->setText("open");
    button->move(100,100);
    button->setParent(this);

    QPushButton * button1 = new QPushButton;
    button1->setText("close");
    button1->move(100,200);
    button->setParent(this);





}

void Widget::classOver(){
    //触发函数发生信号  emit
    //emit ter->hungry();
    emit ter->hungry("猪脚饭");
}

Widget::~Widget()
{
    delete ui;
}

