/*
    Card_T.cpp
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (Card_T.cpp) defines a constructor for the
    Card template class and an ostream insertion operator.
*/

// All includes
#include <iostream>
using namespace std;

#include "Card_T.h"

/*
    Definition of default card constructor.
    Is parameterized by suit and rank types.
*/
template <typename t_suit, typename t_rank>
Card<t_suit, t_rank>::Card(t_suit s, t_rank r) : suit(s), rank(r) {}

/*
    Definition of insertion operator for card.
    Is parameterized by suit and rank types.
*/
template <typename t_suit, typename t_rank>
ostream &operator<<(ostream &os, const Card<t_suit, t_rank> &s)
{
    os << s.rank << s.suit;
    return os;
}

/*
*   Definition of lessRank
*/
template <typename t_suit, typename t_rank>
bool lessRank(const Card<t_suit, t_rank>& c1, const Card<t_suit, t_rank>& c2) {
    return (less(c1.suit, c2.suit) && (c1.rank == c2.rank)) || less(c1.rank, c2.rank);
}

/*
*   Definition of lessSuit
*/
template <typename t_suit, typename t_rank>
bool lessSuit(const Card<t_suit, t_rank>& c1, const Card<t_suit, t_rank>& c2) {
    return less(c1.suit, c2.suit) || ((c1.suit == c2.suit) && less(c1.rank, c2.rank));
}
