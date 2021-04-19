#include "mywidget.h"  //自己写的类

#include <QApplication>  //包含一个应用程序类的头文件

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  //a：应用程序对象  QT中有且仅有一个
    MyWidget w;  //窗口对象  QWidget父类
    w.show();//顶层方式弹出窗口控件
    //让应用程序对象进入消息循环
    //阻塞在这一行
    return a.exec();
}
