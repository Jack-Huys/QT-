#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pushButton = new QPushButton("按钮A", this);
    // pushButton->setGeometry(QRect(100,100,100,25));
    QObject::connect(pushButton, &QPushButton::released, this, &MainWindow::textButton);

    // 点击按钮打开新窗口
    button = new QPushButton(this);
    // 按钮显示位置
    button->setGeometry(QRect(50,50,100,25));

    button->setText("下一个新窗口");
    // 点击信号槽事件
    QObject::connect(button, &QPushButton::clicked, this, &MainWindow::showMainWindow2);


    //实例 QLabel 控件
    label = new QLabel("我是 QLabel",this);
    //QLabel 位置
    //label->move(100,100);
    label->setGeometry(QRect(100,100,200,30));
    //label 样式(CSS 样式表)
    //font-size 字号
    //color 字体颜色
    //font-weight 字宽
    //font-style 字体样式
     label->setStyleSheet("QLabel{font-size:20px;color:red;font-weight:bold;fontstyle:italic;}");


     lineEdit = new QLineEdit(this);
     lineEdit->setGeometry(QRect(150,150,200,25));
     lineEdit->setStyleSheet("QLineEdit{border:1px;border-style:solid;color:red;border-color: bluered;}");
     //限制最长输入 12 位
     lineEdit->setMaxLength(12);
     //不可写入
     //lineEdit->setEchoMode(QLineEdit::NoEcho);
     //密码*号输入
     lineEdit->setEchoMode(QLineEdit::Password);

     //实例 QTextEdit 控件
     textEdit = new QTextEdit(this);
     //控件位置大小
     textEdit->setGeometry(QRect(200,200,200,150));
     //内容
     textEdit->setText("我是第一行<br/>我是第二行");

     //实例
     plainTextEdit = new QPlainTextEdit(this);
     //位置
     plainTextEdit->setGeometry(QRect(250,250,200,100));
     //添加内容
     plainTextEdit->setPlainText("第一行");


     //实例 QComboBox
     comboBox = new QComboBox(this);
     //控件显示位置大小
     comboBox->setGeometry(QRect(300,300,120,25));
     //定义字符串列表
     QStringList str;
     str << "数学" << "语文" << "地理";
     //将字符串列表绑定 QComboBox 控件
     comboBox->addItems(str);

     //实例 QFontComboBox
     fontComboBox = new QFontComboBox(this);
     //实例 QPushButton
     //button = new QPushButton(this);
     //实例 QLabel
     //label = new QLabel(this);
     //label->setGeometry(QRect(50,150,300,25));
     //按钮名
     pushButton->setText("按钮");
     //位置
     pushButton->move(180,50);
     //事件
     connect(pushButton,SIGNAL(released()),this,SLOT(txtButton()));
     //QFontComboBox 控件位置
     fontComboBox->setGeometry(QRect(50,50,120,25));

     //实例 QSpinBox
     spinBox = new QSpinBox(this);
     //位置
     spinBox->setGeometry(QRect(350,350,100,25));
     //值范围
     spinBox->setRange(0,200);
     //初始值
     spinBox->setValue(10);
     //后缀
     spinBox->setSuffix("元");
     //前缀
     //spinBox->setPrefix("$");

     //实例
     timeEdit = new QTimeEdit(this);
     //位置
     timeEdit->setGeometry(QRect(400,400,120,25));
     //获取系统时间
     QDateTime sysTime = QDateTime::currentDateTime();
     //获取时分秒以“：”号拆分赋予 list 数组
     QStringList list = sysTime.toString("hh:mm:ss").split(':');
     //将时分秒绑定控件
     timeEdit->setTime(QTime(list[0].toInt(),list[1].toInt(),list[2].toInt()));

     //实例
     scrollBar = new QScrollBar(this);
     //spinBox = new QSpinBox(this);
     //横显/竖显
     scrollBar->setOrientation(Qt::Horizontal);
     //位置
     scrollBar->setGeometry(QRect(450,450,180,20));
     spinBox->setGeometry(QRect(350,450,100,25));
     //控制条宽度
     scrollBar->setPageStep(10);
     //scrollBar 事件
     connect(scrollBar,SIGNAL(valueChanged(int)),spinBox,SLOT(setValue(int)));
     //spinBox 事件
     connect(spinBox,SIGNAL(valueChanged(int)),scrollBar,SLOT(setValue(int)));
     //初始值
     scrollBar->setValue(100);


     //实例 listView 控件
     listView = new QListView(this);
     //定义位置宽高
     listView->setGeometry(QRect(50,450,100,100));
     //StringList 数组
     QStringList string;
     string << "数学" << "语文" << "外语" <<"地理";
     //添加数据
     model = new QStringListModel(string);
     //将数据绑定 listView 控件
     listView->setModel(model);


     //实例 QProgressBar 控件
     bar = new QProgressBar(this);
     //位置
     bar->setGeometry(QRect(80,400,200,20));
     //范围值
     bar->setRange(0,100000-1);
     //初始值
     bar->setValue(0);
     //实例 Button
     but = new QPushButton(this);
     //位置
     but->setGeometry(QRect(300,400,80,25));
     //值
     but->setText("开始");
     //事件
     connect(but,SIGNAL(clicked()),this,SLOT(startBar()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete pushButton;
}

void MainWindow::textButton()
{
    pushButton->setText("按钮B");
}
void MainWindow::showMainWindow2()
{
    w2.show();
}

//方法
void MainWindow::txtButton()
{
    label->setText("选择字体："+fontComboBox->currentText());
}

void MainWindow::startBar()
{
    for(int i=0;i<100000;i++)
    {
        //100%结束
        if(i == 99999)
        {
            button->setText("结束");
        }
        //赋值
        bar->setValue(i);
    }
}
