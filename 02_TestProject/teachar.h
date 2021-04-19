#ifndef TEACHAR_H
#define TEACHAR_H

#include <QObject>

class Teachar : public QObject
{
    Q_OBJECT
public:
    explicit Teachar(QObject *parent = nullptr);

signals:
    //自定义信号，写到signals
    //返回值是void ,只需要声明，不需要实现
    //可以有参数，可以重载
    void hungry();

    void hungry(QString foodName);

};

#endif // TEACHAR_H
