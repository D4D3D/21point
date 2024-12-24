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
#include "card.h"
#include <QDebug>



#include <QUrl>
#include <QMediaPlayer>
#include <QAudioOutput>


#define max_length 20;

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
    //函数声明
    void Point21();	//无参构造函数
    void Game();

    bool onEKeypressed();
    void gameContinue();
    void gameOver();

    void playMedie(int time,int num);

    //私有变量
private:
    Ui::Widget *ui;

    QGraphicsView mGameView;
    QGraphicsScene mScene;

    QGraphicsPixmapItem mCard;
    QGraphicsPixmapItem mBackground;

    Card PK[52];//54张牌减去大小王
    int startPosition;//发牌初始位
    Card gamers[8][21];
    //gamers[0]存放庄家的牌，gamers[1]到[7]存放玩家的牌
    //设置庄家即是机器人，一个人也能玩

    int numcards[8];	//庄家(numcards[0])及玩家的牌数
    // char name[8][max_length];	//庄家及玩家姓名
    int numgamer;//玩家数


    void Shuffle();	//洗牌函数

    int GetTotalScore(Card gamer[21], int n);	//返回第一手牌（第一次发牌）的总分值


    //这个是新的
    int newshowStatus(int gamer,bool up);

    int keyPressed;

    int hostcard =0;
    int playercard = 0;

    int mode = 0;
    int sendcard = 0;
    QMediaPlayer *player =new QMediaPlayer;





    //返回随机一个Card类
    Card FirstCard();


signals:
    // 定义一个信号，当 'E' 键按下时发出
    void keyBoardpressE(int key);

    void keyBoardpressQ(int key);

    void keyBoardpressR(int key);

    void playmusic(int time,int num);






};
#endif // WIDGET_H

int posCard(int x);
QPixmap load_card(int num,color s);
