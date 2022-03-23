#include "EditStuMessBox.h"

//构建添加学生主界面
EditStuMessBox::EditStuMessBox()
{
    /*
     * QVBoxLayout 局部工具中放置 QFormLayout 和 QHBoxLayout
     * QFormLayout 中放置多个单行输入框
     * QHBoxLayout 中放置两个按钮
    */
   // setWindowFlags(Qt::Dialog);
    setWindowTitle("添加学生信息");
    QVBoxLayout * VBox = new QVBoxLayout;

    QFormLayout *FormLayout = new QFormLayout;
    ID = new QLineEdit;
    name = new QLineEdit;
    sex = new QLineEdit;
    age = new QLineEdit;
    chinese_score = new QLineEdit;
    math_score = new QLineEdit;
    english_score = new QLineEdit;
    FormLayout->addRow("学号：",ID);
    FormLayout->addRow("姓名：",name);
    FormLayout->addRow("年龄：",age);
    FormLayout->addRow("性别：",sex);
    FormLayout->addRow("语文成绩：",chinese_score);
    FormLayout->addRow("数学成绩：",math_score);
    FormLayout->addRow("英语成绩：",english_score);
    FormLayout->setRowWrapPolicy(QFormLayout::WrapLongRows);

    QHBoxLayout * HBox = new QHBoxLayout;
    submit = new QPushButton("提交");
    cancel = new QPushButton("取消");
    HBox->addWidget(submit);
    HBox->addWidget(cancel);

    VBox->addLayout(FormLayout,4);
    VBox->addLayout(HBox,1);
    this->setLayout(VBox);

    // 信号槽连接
    QObject::connect(submit, &QPushButton::clicked, this, &EditStuMessBox::saveStuMess);
    QObject::connect(cancel, &QPushButton::clicked, this, &EditStuMessBox::close);
}

void EditStuMessBox::saveStuMess()
{
    if(this->ID->text() !="" && this->name->text()!="" && this->sex->text()!="" &&
            this->chinese_score->text()!="" && this->math_score->text()!="" &&
            this->english_score->text()!="")
    {

        QT_STUDENT_INFO student;
        student.ID = this->ID->text();
        student.name = this->name->text();
        student.sex = this->sex->text();
        student.age = this->age->text();
        student.chinese_score = this->chinese_score->text();
        student.math_score = this->math_score->text();
        student.english_score = this->english_score->text();

        QFile stuFile(FILE_NAME);
        stuFile.open(QIODevice::WriteOnly | QIODevice::Append);
        QDataStream dataStr(&stuFile); // 读写二进制流

        dataStr << student.ID << student.name << student.age <<
                   student.sex << student.chinese_score <<
                   student.math_score << student.english_score;

        stuFile.close(); // 关闭打开的文件
        this->close();   // 退出当前窗体
        emitCloseBox();
    }
    else
    {
        QMessageBox::warning(this, "提示", "请将信息填写完整", QMessageBox::Ok);
    }
}

// 信号发射器
void EditStuMessBox::emitCloseBox()
{
    emit closeBox();
}
