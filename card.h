#ifndef CARD_H
#define CARD_H

#pragma once
#pragma once

typedef enum
{
    //牌面A,J=10,Q=10,K=10
    A = 1, two, three, four, five, six, seven, eight, nine, ten, J, Q, K
}numtype;
//变量numtype的类型为枚举型enum

typedef enum
{
    //扑克牌的花色：clubs(梅花)，diamonds(方块)，hearts(红桃)和spades(黑桃)
    clubs, diamonds, hearts, spades
}shapetype;
//变量shapetype的类型为枚举型enum


//实现一张牌的对象
struct Card
{
    numtype num;//面值数字
    shapetype shape;//花色形状
};
//定义一副牌的结构体





#endif // CARD_H
