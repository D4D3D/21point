#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{



    // QObject::connect(QApplication::instance(), &QApplication::focusChanged,this, [this](QWidget *old, QWidget *now) {
    //     if (now == this) {
    //         // 检查某个键是否被按下
    //         if (isKeyPressed(Qt::Key_Space)) {
    //             qDebug() << "Space key is still pressed!";
    //         }
    //     }
    // });
    connect(this,&MainWindow::keyPres,this,&MainWindow::func);

 ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::func(){
    qDebug() << "wow";
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    // 获取按下的键
    keyPressed = event->key();
    // qDebug() << "Key pressed:" << keyPressed;

    // 处理按键事件
    if (keyPressed == Qt::Key_Space) {
        // qDebug() << "Space key pressed!";
    }
     emit keyPres(keyPressed);
}

// 重写键盘释放事件
void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    // 清除按键状态
    keyPressed = Qt::Key_unknown;
    qDebug() << "Key released:" << event->key();
}

// 检查当前是否有按键按下
bool MainWindow::isKeyPressed(int key) const {
    return keyPressed == key;

}

