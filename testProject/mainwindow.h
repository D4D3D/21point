#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // 检查当前是否有按键按下
    bool isKeyPressed(int key) const;
    void func();
protected:
    // 重写键盘按下事件
    void keyPressEvent(QKeyEvent *event) override;
    // 重写键盘释放事件
    void keyReleaseEvent(QKeyEvent *event) override;
private:
    Ui::MainWindow *ui;

    // 存储当前按下的键
    int mod = 0;
    int keyPressed;

signals:
    // 自定义信号，表示按键被按下
    void keyPres(int key);







};
#endif // MAINWINDOW_H
