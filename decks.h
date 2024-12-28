#ifndef DECKS_H
#define DECKS_H

#include "card.h"
#include <cstdlib> // 包含 srand 和 rand
#include <ctime>   // 包含 time

class Decks
{
public:
    Decks();

    Card FirstCard();
    void Shuffle();
    void SetstartPosition(int pos);

private:
    Card PK[52];//54张牌减去大小王
    int startPosition;//发牌初始位


};


#endif // DECKS_H
