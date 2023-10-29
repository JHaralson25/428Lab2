/*
    Deck_T.cpp
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (Deck_T.cpp) defines a public shuffle function and
    a public collect function for the Deck template class.
*/

// All includes
#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

#include "Deck_T.h"

/*
    Randomly shuffles the ordering of Cards in a CardSet using
    random_device.
*/
template <typename Suit, typename Rank>
void Deck<Suit, Rank>::shuffle()
{
    random_device rd;
    mt19937 rng(rd());
    std::shuffle(CardSet<Suit, Rank>::cards.begin(), CardSet<Suit, Rank>::cards.end(), rng);
}

/*
    Collects all the cards from an input CardSet class into the
    currect Deck.
*/
template <typename Suit, typename Rank>
void Deck<Suit, Rank>::collect(CardSet<Suit, Rank> &cs)
{
    // Only extracts card if deck contains a card to extract.
    while (!cs.is_empty())
    {
        cs >> (*this);
    }
}