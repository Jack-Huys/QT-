#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <mainwindow2.h>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QFontComboBox>
#include <QSpinBox>
#include <QTimeEdit>
#include <QScrollBar>
#include <QListView> //QListView 类
#include <QStringListModel> //数据模型类
#include <QProgressBar> //进度条类

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void textButton();
    void showMainWindow2();
    void txtButton();
    void startBar();

private:
    Ui::MainWindow *ui;
    QPushButton *pushButton;
    QPushButton *button;
    MainWindow2 w2;
    QLabel *label;
    QLineEdit *lineEdit; // 单行文本
    QTextEdit *textEdit; // 多行文本
    QPlainTextEdit *plainTextEdit; // 多行文本

    QComboBox *comboBox; // 下拉列表框

    QFontComboBox *fontComboBox; // 字体下拉列表框
    QSpinBox *spinBox; // QSpinBox 用于整数的显示和输入
    QTimeEdit *timeEdit; // 时间控件
    QScrollBar *scrollBar; // 控制条

    QListView *listView;
    QStringListModel *model;


    QPushButton *but;
    QProgressBar *bar;

};
#endif // MAINWINDOW_H
