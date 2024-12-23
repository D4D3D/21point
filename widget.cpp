#include "widget.h"
#include "./ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    connect(this,&Widget::keyBoardpressE,this,&Widget::gameContinue);
    connect(this,&Widget::keyBoardpressQ,this,&Widget::gameOver);

    QSize msize  = QSize(900,400);
    this->setFixedSize(msize);

    mGameView.setSceneRect(QRect(0,0,900,400));
    mScene.setSceneRect(QRect(0,0,900,400));

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

void Widget::changeMode(){
    mode = 1;
}


void Widget::sendCard(){
    sendcard++;
}


void Widget::CardMove(){
    mCard.moveBy(5,5);
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

}
// bool Widget::onEKeypressed(){
//     return true;
// }



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
    //label1->setScaledContents(true);

    //QScreen* screen = QGuiApplication::primaryScreen();

    //QRect  screenGeometry = screen->geometry();
    //
    //QSize size = screen->size()*0.4;
    if(num == -1&&s==other){
        *cardK = backCards->copy(4,4 ,71,95);
    }

    if (s == heart)
    {
        *cardK = allCards->copy(posCard(num), (95*0), 71, 95);

        //label1->setPixmap(*cardK);
        //layout->addWidget(label1);
    }
    else if (s == club)
    {

        *cardK = allCards->copy(posCard(num), (95*1), 71, 95);
        //label1->setPixmap(*cardK);
        //layout->addWidget(label1);
    }
    else if (s == diamond)
    {

        *cardK = allCards->copy(posCard(num), (95*2), 71, 95);
        //label1->setPixmap(*cardK);
        //layout->addWidget(label1);
    }
    else if (s == spade)
    {
        *cardK = allCards->copy(posCard(num), (95*3), 71, 95);
        //label1->setPixmap(*cardK);
        //layout->addWidget(label1);
    }
    // cardK->scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // label1->setPixmap(*cardK);

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

/*num为玩家代号
 hide为是否隐藏首张牌
*/

//发庄家的牌，让其背面向上，发玩家的牌，
//在每次抽牌后都会重新显示
//让庄家的牌翻面
//最后庄家加牌时，再次显示
//庄家根据0判断，发牌位置根据数字判断，返回一个现在牌库上有几张牌
// void Widget::ShowStatus(int num, bool hideFirstCard)

// {

//     // cout << endl << name[num] << ":";	//显示庄家或玩家姓名

//     //根据庄家的状态隐藏或显示庄家首张牌的花色
//     int cardnum;
//     color s;
//     int place = 0;

//     // if (hideFirstCard)cout << "<**庄家首张牌被隐藏**>";//隐藏首张牌
//     // else if (gamers[num][0].shape == clubs) cout << "梅花";
//     // else if (gamers[num][0].shape == diamonds) cout << "方块";
//     // else if (gamers[num][0].shape == hearts) cout << "红桃";
//     // else if (gamers[num][0].shape == spades) cout << "黑桃";
//     // //输出庄家首张牌的面值
//     // if (hideFirstCard)  cout << "";
//     // else if (gamers[num][0].num == A) cout << "A ";	//A表示A
//     // else if (gamers[num][0].num == J) cout << "J ";
//     // else if (gamers[num][0].num == Q) cout << "Q ";
//     // else if (gamers[num][0].num == K) cout << "K ";
//     // else cout << (int)gamers[num][0].num;

//     if(hideFirstCard) s =other;
//     else if (gamers[num][0].shape == clubs) s = club;
//     else if (gamers[num][0].shape == diamonds) s = diamond;
//     else if (gamers[num][0].shape == hearts) s = heart;
//     else if (gamers[num][0].shape == spades) s = spade;

//     if(hideFirstCard) cardnum = -1;
//     else if (gamers[num][0].num == A) cardnum = 11;	//A表示A
//     else if (gamers[num][0].num == J) cardnum = 12;
//     else if (gamers[num][0].num == Q) cardnum = 13;
//     else if (gamers[num][0].num == K) cardnum = 14;
//     else cardnum =  (int)gamers[num][0].num;

//     placeCard(cardnum,s,(286+(128*place)),10);





//     for (int i = 1; i < numcards[num]; i++)
//     {
//         if (gamers[num][i].shape == clubs) s = club;
//         else if (gamers[num][i].shape == diamonds) s = diamond;
//         else if (gamers[num][i].shape == hearts) s = heart;
//         else if (gamers[num][i].shape == spades) s = spade;

//         //输出面值
//         if (gamers[num][i].num == A) cardnum = 11;	//A表示A
//         else if (gamers[num][i].num == J) cardnum = 12;
//         else if (gamers[num][i].num == Q) cardnum = 13;
//         else if (gamers[num][i].num == K) cardnum = 14;
//         else cardnum =  (int)gamers[num][i].num;
//         placeCard(cardnum,s,(158+(128*(i-1))),286);

//     }
//     if (!hideFirstCard)
//     //     cout << "   总分值" << GetTotalScore(gamers[num], numcards[num]);
//     // cout << endl;
//         placeStatue(1,100,100);
//     if (GetTotalScore(gamers[num], numcards[num]) > 21)
//         // cout << endl << name[num] << "引爆(超过21点啦 ！ 结束啦)!" << endl;
//         placeStatue(1,100,100);
// }

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
    for (i = 0; i < 2; i++)
        gamers[0][numcards[0]++] = FirstCard();

    // ShowStatus(0, true);	//显示庄家状态，隐藏首张牌与总分
    // ShowStatus(0, true);
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
    // cout << endl;
    //依次向各玩家发额外的牌
    // for (i = 1; i <= numgamer; i++)
    // {
    //     // cout << endl << name[i] << ",你还想再要一张牌吗?如果要请输入1,不要请输入0:";
    //     placeStatue(1,100,100);



    // while(quit==0)
    // {
    //     while(sendcard>0&&GetTotalScore(gamers[i], numcards[i]) <=21)
    //     {
    //         sendcard--;

    //         while (GetTotalScore(gamers[i], numcards[i]) <= 21 && p == '1')
    //         {
    //             gamers[i][numcards[i]++] = FirstCard();
    //             newshowStatus(1,true);

    //         }
    //     }
    // }

    //     while(mode == 0){
    //         QThread::msleep(50);
    //         while(sendcard>0){
    //             sendcard--;
    //             gamers[i][numcards[i]++] = FirstCard();
    //             newshowStatus(1,true);

    //         }
    //     }

    // }

//     hostcard = 0;
//     newshowStatus(0,true);	//显示庄家的前两张牌
//     newshowStatus(0,true);

//     //庄家总分小于等于16，必须再拿牌
//     while (GetTotalScore(gamers[0], numcards[0]) <= 16)
//     {
//         QThread::msleep(50);
//         gamers[0][numcards[0]++] = FirstCard();	//为庄家发1张牌
//         newshowStatus(0,true);
//     }

//     if (GetTotalScore(gamers[0], numcards[0]) > 21)
//     {
//         for (i = 1; i <= numgamer; i++)
//         {	//依次查看每位玩家
//             if (GetTotalScore(gamers[i], numcards[i]) <= 21)
//                  // cout << name[i] << ",恭喜你，庄家引爆，而你没有超过21点，你赢了！" << endl;//玩家没有引爆
//                 placeStatue(1,100,100);
//             else {
//                 // cout << name[i] << ",唉,可惜超过21点了，打了平局！" << endl;//玩家引爆
//                 placeStatue(1,100,100);
//             }
//         }
//     }
//     else
//     {//庄家没有引爆,依次查看每位玩家
//         for (i = 1; i <= numgamer; i++)
//         {//总分比庄家大
//             if (GetTotalScore(gamers[i], numcards[i]) <= 21 && GetTotalScore(gamers[i], numcards[i]) > GetTotalScore(gamers[0], numcards[0]))
//             {//玩家未引爆，且总分比庄家大，玩家赢
//                 // cout << name[i] << ",恭喜你，你最接近21点，你赢了!" << endl;
//             }
//             else if (GetTotalScore(gamers[i], numcards[i]) == GetTotalScore(gamers[0], numcards[0]))
//             {//玩家总分与庄家相等，平局
//                 // cout << name[i] << ",唉，可惜了你与庄家总分相同，打了平局!" << endl;
//             }
//             else if (GetTotalScore(gamers[i], numcards[i]) < GetTotalScore(gamers[0], numcards[0]))
//             {//玩家引爆或总分比庄家小，玩家输
//                 // cout << name[i] << ",对不起，你输了!（庄家更接近21点）" << endl;
//             }
//             else if (GetTotalScore(gamers[i], numcards[i]) > 21)
//             {
//                 // cout << name[i] << ",对不起，你输了!（超过21点）" << endl;
//             }
//         }
//     }
// }

}


void Widget::gameContinue(){
    sendcard--;
    gamers[1][numcards[1]++] = FirstCard();
    newshowStatus(1,true);
}

void Widget::gameOver(){

    int i;
    hostcard = 0;
    newshowStatus(0,true);	//显示庄家的前两张牌
    newshowStatus(0,true);

    //庄家总分小于等于16，必须再拿牌
    while (GetTotalScore(gamers[0], numcards[0]) <= 16)
    {
        QThread::msleep(50);
        gamers[0][numcards[0]++] = FirstCard();	//为庄家发1张牌
        newshowStatus(0,true);
    }

    if (GetTotalScore(gamers[0], numcards[0]) > 21)
    {
        for (i = 1; i <= numgamer; i++)
        {	//依次查看每位玩家
            if (GetTotalScore(gamers[i], numcards[i]) <= 21)
                // cout << name[i] << ",恭喜你，庄家引爆，而你没有超过21点，你赢了！" << endl;//玩家没有引爆
                placeStatue(1,100,100);
            else {
                // cout << name[i] << ",唉,可惜超过21点了，打了平局！" << endl;//玩家引爆
                placeStatue(1,100,100);
            }
        }
    }
    else
    {//庄家没有引爆,依次查看每位玩家
        // for (i = 1; i <= numgamer; i++)
        // {//总分比庄家大
        //     if (GetTotalScore(gamers[i], numcards[i]) <= 21 && GetTotalScore(gamers[i], numcards[i]) > GetTotalScore(gamers[0], numcards[0]))
        //     {//玩家未引爆，且总分比庄家大，玩家赢
        //         qDebug() <<",恭喜你，你最接近21点，你赢了!" ;
        //     }
        //     else if (GetTotalScore(gamers[i], numcards[i]) == GetTotalScore(gamers[0], numcards[0]))
        //     {//玩家总分与庄家相等，平局
        //         qDebug() << ",唉，可惜了你与庄家总分相同，打了平局!" ;
        //     }
        //     else if (GetTotalScore(gamers[i], numcards[i]) < GetTotalScore(gamers[0], numcards[0]))
        //     {//玩家引爆或总分比庄家小，玩家输
        //         qDebug() << ",对不起，你输了!（庄家更接近21点）" ;
        //     }
        //     else if (GetTotalScore(gamers[i], numcards[i]) > 21)
        //     {
        //         qDebug() << ",对不起，你输了!（超过21点）" ;
        //     }
        // }
    }
}


