/*
    Deck_T.h
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (Deck_T.h) declares a Deck class with 2 public
    member functions.
*/

// All includes
#pragma once

#include <iostream>

#include "CardSet_T.h"

/*
    Declaration of Deck class. It contains two
    public member functions to shuffle the deck of
    cards and to collect cards from an input CardSet.
*/
template <typename Suit, typename Rank>
class Deck : public CardSet<Suit, Rank>
{
    public:
        void shuffle();
        void collect(CardSet<Suit, Rank> &cs);
};

// Inclusion gaurds for Deck_T.cpp
#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "Deck_T.cpp"
#endif