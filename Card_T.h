/*
    Card_T.h
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (Card_T.h) declares a Card struct with 2 public
    member variables, 2 public member function, and a default constructor. It
    also declares an ostream insertion operator for
    Card.
*/

// All includes
#pragma once

#include <iostream>

/*
    Forward declaration of card. Is parameterized
    by suit and rank types.
*/
template <typename t_suit, typename t_rank>
struct Card;

/*
    Forward declaration of insertion operator for card.
    Is parameterized by suit and rank types.
*/
template <typename t_suit, typename t_rank>
std::ostream &operator<<(std::ostream &os, const Card<t_suit, t_rank> &c);

/*
*   Template declaration lessRank function
*   Returns true if first card's rank is less than the second
*   card's rank or if the ranks are equal and the first card's
*   suit is less than the second's
*/
template <typename t_suit, typename t_rank>
bool lessRank(const Card<t_suit, t_rank>& c1, const Card<t_suit, t_rank>& c2);

/*
*   Template declaration for lessSuit function
*   Returns true if first card's suit is less than the second
*   card's suit or if the suit are equal and the first card's
*   rank is less than the second's
*/
template <typename t_suit, typename t_rank>
bool lessSuit(const Card<t_suit, t_rank>& c1, const Card<t_suit, t_rank>& c2);

/*
    Declaration of struct Card. It had two member
    variables and a default constructor. Is parameterized
    by suit and rank types.
*/
template <typename t_suit, typename t_rank>
struct Card
{
    public:
        t_suit suit;
        t_rank rank;

        Card(t_suit s, t_rank r);
};

/*
*   Template declaration for lessSuit function
*   Returns true if first card's suit is less than the second
*   card's suit or if the suit are equal and the first card's
*   rank is less than the second's
*/

// Inclusion gaurds for Card_T.cpp
#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "Card_T.cpp"
#endif