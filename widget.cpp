#include "widget.h"
#include "./ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    connect(this,&Widget::keyBoardpressE,this,&Widget::gameContinue);
    connect(this,&Widget::keyBoardpressQ,this,&Widget::gameOver);
    connect(this,&Widget::playmusic,this,&Widget::playMedie);
    connect(this,&Widget::cardLimit,this,&Widget::checkCard);

    QSize msize  = QSize(900,400);
    this->setFixedSize(msize);

    mGameView.setSceneRect(QRect(0,0,900,400));
    mScene.setSceneRect(QRect(0,0,900,400));

    QMediaPlayer *player = new QMediaPlayer;

    mBackground.setPixmap(QPixmap(":/image/D:/desktop/img/thedesktop.png"));
    mScene.addItem(&mBackground);

    mGameView.setScene(&mScene);
    mGameView.setParent(this);
    mGameView.show();
    Point21();
    Game();



}

Card Widget::FirstCard()
{
    return PK[startPosition++];
}

void Widget::Point21()
{
    int nowPos = 0;	//当前扑克牌位置


    char* str;

    for (int shapePos = 0; shapePos < 4; shapePos++)	//花色
    {
        for (int numPos = 1; numPos <= 13; numPos++)	//面值
        {
            PK[nowPos].shape = (shapetype)shapePos;	//花色
            PK[nowPos].num = (numtype)numPos;	//面值
            nowPos++;
        }
    }
    str = new char[1];

    //人数输入位置 目前设置为1

    numgamer = 1;


    // while (numgamer < 1 || numgamer>7) //限制人数在1~7之间
    // {
    //     cout << endl << "玩家人数限定在1~7个,请重新输入人数：";
    //     cin >> str;
    //     numgamer = atoi(str);
    // }

    startPosition = 0;	//发牌位置
    int i = 0;	//临时变量
    //庄家numcards[0]及玩家numcards[1~7]手中的扑克牌张数
    for (i = 0; i <= numgamer; i++) numcards[i] = 0;

    // strcpy_s(name[0], "host");



    // for (i = 1; i <= numgamer; i++)   //玩家姓名
    // {
    //     cout << "输入第" << i << "个玩家的姓名:";
    //     cin >> name[i];
    // }

    // strcpy_s(name[1], "player");
    // cout << "游戏开始" << endl << endl;
}


Widget::~Widget()
{
    delete ui;
}



void Widget::CardMove(){
    mCard.moveBy(5,5);
}

void Widget::checkCard(){

    if(playercard>4){
        cardAllow = 1;
    }
}

void Widget::playMedie(int time, int num){

    if(num == 1){
        // player->setMedia(QUrl::fromLocalFile("/image/D:/desktop/img/medie/gaming.wav"));
    }
    if(num == 2){
        player->setMedia(QUrl::fromLocalFile("/image/D:/desktop/img/medie/lose.mp3"));
    }
    if(num == 3){
        // player->setMedia(QUrl::fromLocalFile("/image/D:/desktop/img/medie/sendcard.mp3"));
    }
    if(num == 4){
        // player->setMedia(QUrl::fromLocalFile("/image/D:/desktop/img/medie/start.wav"));
    }
    if(num == 5){
        player->setMedia(QUrl::fromLocalFile("/image/D:/desktop/img/medie/win.mp3"));
    }

}

void Widget::keyPressEvent(QKeyEvent* event)
{
    keyPressed = event->key();

    if( keyPressed == Qt::Key_E)
    {
        emit keyBoardpressE(keyPressed);
    }
    if( keyPressed == Qt::Key_Q)
    {
        emit keyBoardpressQ(keyPressed);
    }
    if( keyPressed == Qt::Key_R){
        emit keyBoardpressR(keyPressed);
    }

}



//传入牌型，在Scene中显示
void Widget::placeCard(int num,color s,int x,int y)
{
    QGraphicsPixmapItem* cardK = new QGraphicsPixmapItem;
    cardK->setPixmap(load_card(num,s));
    cardK->setPos(x,y);
    mScene.addItem(cardK);

}

void Widget::placeStatue(int num,int x,int y){
    QGraphicsPixmapItem* statue = new QGraphicsPixmapItem;
    QPixmap* image = new QPixmap;
    if(num ==1){
        // image->load(":/image/D:/desktop/img/testimage.png");
    }
    statue->setPixmap(*image);
    statue->setPos(x,y);
    mScene.addItem(statue);

}

//返回一个QPixmap的指针
QPixmap load_card(int num,color s)
{
    QPixmap* allCards = new QPixmap;
    QPixmap* backCards = new QPixmap;
    QPixmap* cardK = new QPixmap;
    allCards->load(":/image/D:/desktop/img/cards.png");
    backCards->load(":/image/D:/desktop/img/Enhancers.png");
    if(num == -1&&s==other){
        *cardK = backCards->copy(4,4 ,71,95);
    }

    if (s == heart)
    {
        *cardK = allCards->copy(posCard(num), (95*0), 71, 95);

    }
    else if (s == club)
    {
        *cardK = allCards->copy(posCard(num), (95*1), 71, 95);
    }
    else if (s == diamond)
    {
        *cardK = allCards->copy(posCard(num), (95*2), 71, 95);
    }
    else if (s == spade)
    {
        *cardK = allCards->copy(posCard(num), (95*3), 71, 95);
    }
    return *(cardK);


}

int posCard(int x) {
    if (x == 1) {
        return (923 * 12 / 13);
    }
    else {
        return ((923 / 13) * (x - 1));
    }

}


void Widget::Shuffle()
{
    srand((unsigned)time(NULL));	//通过调用时间函数初始化随机数
    for (int nowPos = 51; nowPos > 0; nowPos--)
    {
        int pos = rand() % (nowPos + 1);	//产生0~nowPos之间的随机数

        Card temp;		//定义一个临时变量用于交换牌
        temp = PK[pos];
        PK[pos] = PK[nowPos];
        PK[nowPos] = temp;
    }
}
//定义返回第一手牌的总分值 的函数
int Widget::GetTotalScore(Card gamer[21], int n)
{
    int pos;
    int totalScore = 0;
    for (pos = 0; pos < n; pos++)	//循环求最大分值(A的分值为11)
    {
        if (gamer[pos].num == A) totalScore += 11;	//A的分值为11
        else if (gamer[pos].num > ten)totalScore += 10;	//J,Q,K的分值为10
        else totalScore += (int)gamer[pos].num;	//TWO~TEN分值为2~10
    }
    //分值大于21时，将A的分值改为1
    for (pos = 0; totalScore > 21 && pos < n; pos++)
    {
        if (gamer[pos].num == A) totalScore -= 10;
    }
    return totalScore;
}


//place是对于玩家/庄家，牌所在的顺序
int Widget::newshowStatus(int gamer,bool up){
    color s;
    int cardnum;;

    //庄家

    if(gamer == 0)
    {
        if(up)
        {
            if (gamers[0][hostcard].shape == clubs) s = club;
            else if (gamers[0][hostcard].shape == diamonds) s = diamond;
            else if (gamers[0][hostcard].shape == hearts) s = heart;
            else if (gamers[0][hostcard].shape == spades) s = spade;

            if (gamers[0][hostcard].num == A) cardnum = 11;	//A表示A
            else if (gamers[0][hostcard].num == J) cardnum = 12;
            else if (gamers[0][hostcard].num == Q) cardnum = 13;
            else if (gamers[0][hostcard].num == K) cardnum = 14;
            else cardnum =  (int)gamers[0][hostcard].num;

            placeCard(cardnum,s,(286+(128*hostcard)),10);
            hostcard++;
            return 0;


        }
        else{
            placeCard(-1,other,286+(128*hostcard),10);
            return 0;
        }
    }
    //玩家
    else{
        if (gamers[gamer][playercard].shape == clubs) s = club;
        else if (gamers[gamer][playercard].shape == diamonds) s = diamond;
        else if (gamers[gamer][playercard].shape == hearts) s = heart;
        else if (gamers[gamer][playercard].shape == spades) s = spade;

        if (gamers[gamer][playercard].num == A) cardnum = 11;	//A表示A
        else if (gamers[gamer][playercard].num == J) cardnum = 12;
        else if (gamers[gamer][playercard].num == Q) cardnum = 13;
        else if (gamers[gamer][playercard].num == K) cardnum = 14;
        else cardnum =  (int)gamers[gamer][playercard].num;

        placeCard(cardnum,s,(158+(128*(playercard))),286);

        playercard++;
        return 0;


    }

}

void Widget::Game()
{
    Shuffle();	//洗牌
    int i, j;
    //为庄家发两张牌
    for (i = 0; i < 2; i++){
        gamers[0][numcards[0]++] = FirstCard();

    }
    newshowStatus(0,false);
    newshowStatus(0,false);
    //向各玩家发牌并显示
    for (i = 1; i <= numgamer; i++)
    {
        for (j = 0; j < 2; j++){
            gamers[i][numcards[i]++] = FirstCard();
            newshowStatus(1,true);
        }
    }
}


void Widget::gameContinue(){
    if(cardAllow==0){
    sendcard--;
    gamers[1][numcards[1]++] = FirstCard();
    newshowStatus(1,true);
    emit playmusic(-1,3);

    }
    emit checkCard();
}

void Widget::gameOver(){

    int i;
    hostcard = 0;
    newshowStatus(0,true);	//显示庄家的前两张牌
    newshowStatus(0,true);

    //庄家总分小于等于16，必须再拿牌
    if (GetTotalScore(gamers[0], numcards[0]) <= 16)
    {
        QThread::msleep(50);
        gamers[0][numcards[0]++] = FirstCard();	//为庄家发1张牌
        newshowStatus(0,true);
        emit checkCard();
    }

    if (GetTotalScore(gamers[0], numcards[0]) > 21)
    {
        for (i = 1; i <= numgamer; i++)
        {	//依次查看每位玩家
            if (GetTotalScore(gamers[i], numcards[i]) <= 21)
                emit playmusic(-1,5);
            else {
                // cout << name[i] << ",唉,可惜超过21点了，打了平局！" << endl;//玩家引爆
                placeStatue(1,100,100);
            }
        }
    }
    else
    {//庄家没有引爆,依次查看每位玩家
        for (i = 1; i <= numgamer; i++)
        {//总分比庄家大
            if (GetTotalScore(gamers[i], numcards[i]) <= 21 && GetTotalScore(gamers[i], numcards[i]) > GetTotalScore(gamers[0], numcards[0]))
            {//玩家未引爆，且总分比庄家大，玩家赢
                emit playmusic(-1,5);
            }
            else if (GetTotalScore(gamers[i], numcards[i]) == GetTotalScore(gamers[0], numcards[0]))
            {//玩家总分与庄家相等，平局
                // qDebug() << ",唉，可惜了你与庄家总分相同，打了平局!" ;
            }
            else if (GetTotalScore(gamers[i], numcards[i]) < GetTotalScore(gamers[0], numcards[0]))
            {//玩家引爆或总分比庄家小，玩家输
                emit playmusic(-1,2);
            }
            else if (GetTotalScore(gamers[i], numcards[i]) > 21)
            {
                emit playmusic(-1,2);
            }
        }
    }
}


