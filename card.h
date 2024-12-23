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

struct Card
{
    numtype num;//面值数字
    shapetype shape;//花色形状
};
//定义一副牌的结构体


//重载运算符<<
//运用了const
// ostream& operator<<(ostream& output, const Card& card)
// {
//     //输出花色
//     if (card.shape == clubs)  output << "梅花";
//     if (card.shape == diamonds) output << "方块";
//     if (card.shape == hearts) output << "红桃";
//     if (card.shape == spades) output << "黑桃";

//     //输出面值
//     if (card.num == A)
//     {
//         output << "A";
//     }
//     else if (card.num == J)
//     {
//         output << "J";
//     }
//     else if (card.num == Q)
//     {
//         output << "Q";
//     }
//     else if (card.num == K)
//     {
//         output << "K";
//     }
//     else cout << (int)card.num;//强制转化面值为int型

//     return output;

// }


#endif // CARD_H
