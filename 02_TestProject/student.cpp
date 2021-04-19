#include "student.h"

#include <QDebug>

student::student(QObject *parent) : QObject(parent)
{

}

void student::treat(){
    qDebug()<<"请老师吃饭"<<endl;
}

void student::treat(QString foodName){

    //QString -> char * 先转成 QByteArray, 再转char *
    qDebug() << "请老师吃饭，老师要吃"<<foodName.toUtf8().data() <<endl;
}
