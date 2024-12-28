#include "decks.h"

Decks::Decks() {
    int nowPos = 0;	//当前扑克牌位置


    for (int shapePos = 0; shapePos < 4; shapePos++)	//花色
    {
        for (int numPos = 1; numPos <= 13; numPos++)	//面值
        {
            PK[nowPos].shape = (shapetype)shapePos;	//花色
            PK[nowPos].num = (numtype)numPos;	//面值
            nowPos++;
        }
    }

    startPosition = 0;	//发牌位置
    Shuffle();

}


void Decks::SetstartPosition(int pos){
    startPosition = pos;
}


Card Decks::FirstCard()
{
    return PK[startPosition++];
}

void Decks::Shuffle()
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
