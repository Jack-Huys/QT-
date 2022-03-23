#ifndef EDITSTUMESSBOX_H
#define EDITSTUMESSBOX_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>

#define FILE_NAME "student.txt"
#define FILE_TEMP_NAME "student.txt"

//自定义添加学生信息窗口
class EditStuMessBox : public QDialog
{
    Q_OBJECT
public:
    // 构建添加学生信息界面
    EditStuMessBox();

    // 自定义信号
signals:
    void closeBox();

    // 自定义槽函数
    // 保留添加学生信息到文件
public slots:
    void saveStuMess();

    // 信号发射器 emit关键字
public:
    void emitCloseBox();
private:
    QLineEdit * ID;
    QLineEdit * name;
    QLineEdit * sex;
    QLineEdit * age;
    QLineEdit * chinese_score;
    QLineEdit * math_score;
    QLineEdit * english_score;
    QPushButton * submit;
    QPushButton * cancel;
};
// 学生信息
typedef struct tagQT_STUDENT_INFO
{
    QString ID;
    QString name;
    QString sex;
    QString age;
    QString chinese_score;
    QString math_score;
    QString english_score;
}QT_STUDENT_INFO;
#endif // EDITSTUMESSBOX_H
