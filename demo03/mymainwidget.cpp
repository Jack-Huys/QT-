#include "mymainwidget.h"
#include "ui_mymainwidget.h"

#include <QDebug>

MyMainWidget::MyMainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyMainWidget)
{
    ui->setupUi(this);
    setWindowTitle("学生管理系统");
    this->resize(1000,600);
    this->pBoxLayout = new QHBoxLayout(this);
    this->Left_Table_Box = createStuMess();
    this->Right_Table_Box = createMenu();

    pBoxLayout->addWidget(Left_Table_Box,4);
    pBoxLayout->addWidget(Right_Table_Box,2);
}

QGroupBox* MyMainWidget::createStuMess()
{
    QGroupBox *box = new QGroupBox("学生信息");
    TableWidget = new QTableWidget;
    TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    TableWidget->setColumnCount(7);
    // 设置表格的水平表头
    TableWidget->setHorizontalHeaderLabels(QStringList() <<"学号"<< "姓名"<<"年龄"<<"性别"<<"语文成绩"<<"数学成绩"<<"英文成绩");
    flushTable();

    QHBoxLayout * AutoHBoxLayout = new QHBoxLayout;
    AutoHBoxLayout->addWidget(TableWidget);
    box->setLayout(AutoHBoxLayout);

    //当用户点击某个单元格时，更新列表中显示的学生信息
    connect(TableWidget,&QTableWidget::cellClicked,this,&MyMainWidget::flushListWidget);
    //当用户更改某个单元格内的内容时，调用 changeStuMess() 方法处理
    connect(TableWidget,&QTableWidget::cellChanged,this,&MyMainWidget::changeStuMess);
    //将用户更改某个单元格内的内容时，同时还要更新表格中显示的学生信息
    connect(TableWidget,&QTableWidget::cellChanged,this,&MyMainWidget::flushListWidget);
    return box;
}

QGroupBox* MyMainWidget::createMenu()
{
    QGroupBox * box = new QGroupBox("功能面板");
    QVBoxLayout *VBoxLayout = new QVBoxLayout;

    ListWidget = new QListWidget;
    QGridLayout * Buts = new QGridLayout;
    AddStuBtn = new QPushButton("添加");
    DelStuBtn = new QPushButton("删除");
    SaveBtn = new QPushButton("保存");
    ExitBtn = new QPushButton("退出");
    FindStuEdit = new QLineEdit;
    FindStuEdit->setPlaceholderText("输入学生姓名查找...");
    FindStuEdit->setClearButtonEnabled(true);
    FindStuEdit->setStyleSheet("QLineEdit{padding:3,3,3,3;}");
    Buts->addWidget(AddStuBtn,0,0);
    Buts->addWidget(DelStuBtn,0,1);
    Buts->addWidget(FindStuEdit,1,0,1,0);
    Buts->addWidget(SaveBtn,2,0);
    Buts->addWidget(ExitBtn,2,1);

    VBoxLayout->addWidget(ListWidget,4);
    VBoxLayout->addLayout(Buts,2);

    box->setLayout(VBoxLayout);

    //点击添加按钮，执行 addStuBox() 方法
    connect(AddStuBtn,&QPushButton::clicked,this,&MyMainWidget::AddStuBox);
    //点击删除按钮，执行 delStuFun() 方法
    connect(DelStuBtn,&QPushButton::clicked,this,&MyMainWidget::delStuFun);
    //当向输入框内输入信息后，执行 findStuMess() 方法
    connect(FindStuEdit,&QLineEdit::returnPressed,this,&MyMainWidget::findStuMess);
    //点击退出按钮，关闭主窗口
    connect(ExitBtn,&QPushButton::clicked,this,&MyMainWidget::close);
    //点击保存按钮，执行 saveStuMess() 方法
    connect(SaveBtn,&QPushButton::clicked,this,&MyMainWidget::saveStuMess);
    return box;
}

MyMainWidget::~MyMainWidget()
{
    delete ui;
    delete pBoxLayout;
}

//当点击添加按钮时，弹出添加学生信息的子窗口
void MyMainWidget::AddStuBox(){
    messBox = new EditStuMessBox;
    //当添加学生信息窗口关闭时，更新表格，同时清空列表中显示的学生信息
    QObject::connect(messBox,&EditStuMessBox::closeBox,this,&MyMainWidget::flushTable);
    QObject::connect(messBox,&EditStuMessBox::closeBox,ListWidget,&QListWidget::clear);
    messBox->exec();
}

//刷新表格中的内容，当界面初始化、添加和删除学生信息后，都需要对表格内容进行更新
void MyMainWidget::flushTable(){
    //更新表格内容前，要断开与 cellChanged 信号关联的所有槽，否则会导致程序闪退
    disconnect(TableWidget,&QTableWidget::cellChanged,0,0);
    QFile file(FILE_NAME);
    file.open(QIODevice::ReadOnly);
    QDataStream dataStr(&file);
    QString id,name,age,sex,chinese_score,math_score,english_score;
    TableWidget->setRowCount(0);
    while(!dataStr.atEnd()){
        TableWidget->setRowCount(TableWidget->rowCount()+1);
        dataStr>>id>>name>>age>>sex>>chinese_score>>math_score>>english_score;
        TableWidget->setItem(TableWidget->rowCount()-1,0,new QTableWidgetItem(id));
        TableWidget->setItem(TableWidget->rowCount()-1,1,new QTableWidgetItem(name));
        TableWidget->setItem(TableWidget->rowCount()-1,2,new QTableWidgetItem(age));
        TableWidget->setItem(TableWidget->rowCount()-1,3,new QTableWidgetItem(sex));
        TableWidget->setItem(TableWidget->rowCount()-1,4,new QTableWidgetItem(chinese_score));
        TableWidget->setItem(TableWidget->rowCount()-1,5,new QTableWidgetItem(math_score));
        TableWidget->setItem(TableWidget->rowCount()-1,6,new QTableWidgetItem(english_score));
    }
    file.close();
    //完成更新表格的任务后，重新关联与 cellChanged 相关的槽。
    connect(TableWidget,&QTableWidget::cellChanged,this,&MyMainWidget::changeStuMess);
    connect(TableWidget,&QTableWidget::cellChanged,this,&MyMainWidget::flushListWidget);
}

//更新列表中显示的学生信息
void MyMainWidget::flushListWidget(int row){
    //当列表中有信息时，直接修改即可
    if(ListWidget->count() > 0){
        ListWidget->item(0)->setText("学   号：" + TableWidget->item(row,0)->text());
        ListWidget->item(1)->setText("姓   名：" + TableWidget->item(row,1)->text());
        ListWidget->item(2)->setText("年   龄：" + TableWidget->item(row,2)->text());
        ListWidget->item(3)->setText("性   别：" + TableWidget->item(row,3)->text());
        ListWidget->item(4)->setText("语文成绩：" + TableWidget->item(row,4)->text());
        ListWidget->item(5)->setText("数学成绩：" + TableWidget->item(row,5)->text());
        ListWidget->item(6)->setText("英语成绩：" + TableWidget->item(row,6)->text());
    }else{
        ListWidget->addItem("学   号：" + TableWidget->item(row,0)->text());
        ListWidget->addItem("姓   名：" + TableWidget->item(row,1)->text());
        ListWidget->addItem("年   龄：" + TableWidget->item(row,2)->text());
        ListWidget->addItem("性   别：" + TableWidget->item(row,3)->text());
        ListWidget->addItem("语文成绩：" + TableWidget->item(row,4)->text());
        ListWidget->addItem("数学成绩：" + TableWidget->item(row,5)->text());
        ListWidget->addItem("英语成绩：" + TableWidget->item(row,6)->text());
    }
}

/* 删除学生信息
 * 思路：将除目标学生外，其它学生的信息拷贝到一个临时文件中，然后删除原来的文件，并将临时文件的文件名改为和原文件相同的名称。
*/
void MyMainWidget::delStuFun()
{
    QList<QTableWidgetItem*>items = TableWidget->selectedItems();
    //判断用户是否在表格中选中了某个学生信息，只有选中之后，才能执行删除操作
    if(items.count() > 0){
        QMessageBox::StandardButton result=QMessageBox::question(this, "删除","确定要删除学号为【"+items.at(0)->text()+"】的同学吗？");
        if(result == QMessageBox::Yes){
            QString ID,name,age,sex,chinese_score,math_score,english_score;
            QFile file(FILE_NAME);
            file.open(QIODevice::ReadOnly);
            QDataStream readDataStr(&file);

            QFile tempFile(FILE_TEMP_NAME);
            tempFile.open(QIODevice::WriteOnly);
            QDataStream writeDataStr(&tempFile);

            while (!readDataStr.atEnd()) {
                readDataStr >> ID >> name >> age >> sex >> chinese_score >> math_score >> english_score;
                if(ID != items.at(0)->text()){
                    writeDataStr << ID << name << age << sex << chinese_score << math_score << english_score;
                }
            }
            tempFile.close();
            file.close();
            //删除原文件，将临时文件重命名为和原文件相同的名字
            file.remove();
            tempFile.rename(FILE_NAME);
            flushTable();
            ListWidget->clear();
        }
    }else{
        QMessageBox::warning(this,"提示","请选择要删除的学生");
    }
}

//根据输入框中的学生姓名，在表格中查找目标学生
void MyMainWidget::findStuMess()
{
    qint32 count = TableWidget->rowCount();
    bool findSuccess = false;
    if(count>0){
        for(qint32 i=0;i<count;i++){
            QString name = TableWidget->item(i,1)->text();
            if(name == FindStuEdit->text()){
                findSuccess = true;
                TableWidget->selectRow(i);
                flushListWidget(i);
                break;
            }
        }
        if(findSuccess == false){
            QMessageBox::information(this,"查找失败","当前表格中没有【"+FindStuEdit->text()+"】同学");
        }
    }

}

/* 更改学生信息
 * 思路：逐一将学生信息拷贝到另一个临时文件中，当读取到要更改的学生信息时，将更改后的学生信息写入临时文件。最终，临时文件中存储的是更改后所有学生的信息。
 * 拷贝完成后，删除原文件，将临时文件的名称改为和原文件一样。
*/
void MyMainWidget::changeStuMess(int row)
{
    QString ID,name,age,sex,chinese_score,math_score,english_score;
    QString stuName = TableWidget->item(row,1)->text();
    QFile file(FILE_NAME);
    file.open(QIODevice::ReadOnly);
    QDataStream readDataStr(&file);

    QFile tempFile(FILE_TEMP_NAME);
    tempFile.open(QIODevice::WriteOnly);
    QDataStream writeDataStr(&tempFile);

    while (!readDataStr.atEnd()) {
        readDataStr >> ID >> name >> age >> sex >> chinese_score >> math_score >> english_score;
        if(name != stuName){
            writeDataStr << ID << name << age << sex << chinese_score << math_score << english_score;
        }else{
            for(int i=0;i<TableWidget->columnCount();i++){
                writeDataStr<<TableWidget->item(row,i)->text();
            }
        }
    }
    tempFile.close();
    file.close();
    file.remove();
    tempFile.rename(FILE_NAME);
}

//保存学生信息，将表格中的学生信息重新存储到文件中
void MyMainWidget::saveStuMess()
{
    QFile file(FILE_NAME);
    file.open(QIODevice::WriteOnly);
    QDataStream dataStr(&file);

    for(int i=0;i<TableWidget->rowCount();i++){
        for(int j=0;j<TableWidget->columnCount();j++){
            dataStr << TableWidget->item(i,j)->text();
        }
    }
    file.close();
    QMessageBox::information(this,"保存","保存成功！");
}

