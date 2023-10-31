/*
    PinochleDeck.h
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (PinochleDeck.h) declares an enum to hold ranks for the
    game pinochle and a pinochle deck class that stores information
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
    Declaration and definition of PinochleRanks enum.
    Holds ranks for card game pinochle.
*/
enum class PinochleRanks
{
    nine,
    jack,
    queen,
    king,
    ten,
    ace,
    undefined
};

// Declaration of ostream insertion operator for PinochleRanks enum
ostream &operator<<(ostream &os, const PinochleRanks &pr);

// Declaration of PinochleRanks overloaded increment prefix operator
PinochleRanks &operator++(PinochleRanks &pr);

/*
    Declaration of PinochleDeck class that publicly inherits from the Deck class.
    This class contains a default public constructor for the PinochleDeck class
    (all other functionality and member variables are inherited).
*/
class PinochleDeck : public Deck<Suits, PinochleRanks>
{
public:
    PinochleDeck();
};