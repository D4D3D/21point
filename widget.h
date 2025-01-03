#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSize>
#include <QTimer>
#include <QKeyEvent>
#include <QThread>
#include <QDebug>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QUrl>
#include <QMediaPlayer>
#include <QAudioOutput>

#include "decks.h"
// #include <optional>
// #include <memory>

#define max_length 20;

//这里的color和card的shapetype不同，功能不同，改起来太麻烦
enum color {
    heart = 0,
    club = 1,
    diamond = 2,
    spade = 3,
    other = 4
};

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE



class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void CardMove();
    void keyPressEvent(QKeyEvent* event);
    void placeCard(int,color,int,int);
    void placeStatue(int num,int x,int y);
    bool onEKeypressed();
    void gameContinue();
    void gameOver();
    void playMedie(int time,int num);
    void checkCard();

    //将需要初始化的变量初始化
    void restartGame();


    void initgamescene();
    void initmemuscene();
    void initsettlescene();

    void switchtoMemu();
    void switchtoSettlement();
    void placenote(int num);
    void gameRestart();

    void Game();
    int GetTotalScore(Card gamer[21], int n);

    //私有变量
private:
    Ui::Widget *ui;

    QGraphicsView mGameView;
    QGraphicsScene mScene;
    QGraphicsScene memu;
    QGraphicsScene settlement;
    QGraphicsPixmapItem mCard;

    Card gamers[8][21];
    //gamers[0]存放庄家的牌，gamers[1]到[7]存放玩家的牌
    //设置庄家即是机器人，一个人也能玩

    int numcards[8];	//庄家(numcards[0])及玩家的牌数
    // char name[8][max_length];	//庄家及玩家姓名
    int numgamer;//玩家数



    // int GetTotalScore(Card gamer[21], int n);	//返回第一手牌（第一次发牌）的总分值

    int cardAllow = 0 ;//检测玩家牌数是否超过5
    int gameStatus = 0;

    //这个是新的
    int newshowStatus(int gamer,bool up);

    int keyPressed;
    int hostcard =0;
    int playercard = 0;
    int mode = 0;
    int sendcard = 0;
    QMediaPlayer *player =new QMediaPlayer;

    //实例化一个牌组类
    Decks deck;




    //返回随机一个Card类
    Card FirstCard();


signals:
    // 定义一个信号，当 'E' 键按下时发出
    void keyBoardpressE(int key);

    void keyBoardpressQ(int key);

    void keyBoardpressR(int key);

    void playmusic(int time,int num);

    void cardLimit(int num);

    void theEnd();




};
#endif // WIDGET_H

int posCard(int x);
QPixmap load_card(int num,color s);
