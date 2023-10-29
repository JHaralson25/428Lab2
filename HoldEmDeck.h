/*
    HoldEmDeck.h
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (HoldEmDeck.h) declares an enum to hold ranks for the
    game hold em and a hold em deck class that stores information
    about the deck used in the game.
*/

// All includes
#pragma once

#include <iostream>
#include <vector>

#include "Suit.h"
#include "Deck_T.h"
#include "Card_T.h"

/*
    Declaration and definition of HoldEmRanks enum.
    Holds ranks for card game hold em.
*/
enum class HoldEmRanks
{
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    ace,
    undefined
};

// Declaration of ostream insertion operator for HoldEmRanks enum
ostream &operator<<(ostream &os, const HoldEmRanks &her);

// Declaration of HoldEmRanks overloaded increment prefix operator
HoldEmRanks &operator++(HoldEmRanks &her);

/*
    Declaration of HoldEmDeck class that publicly inherits from Deck.
    This class contains a public constructor.
*/
class HoldEmDeck : public Deck<Suits, HoldEmRanks>
{
    public:
        HoldEmDeck();
};