/*
    Suit.cpp
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (Suit.cpp) defines an overloaded ostream insertion
    operator and an overloaded prefix increment operator
    for the Suit enum.
*/

// All includes
#include <iostream>
using namespace std;

#include "Suit.h"

/*
    Defines the overloaded ostream insertion operation
    for the suit enum inserting the respective symbol
    to the osteam and returning the ostream at the end.
*/
ostream &operator<<(ostream &os, const Suits &suit)
{
    switch (suit)
    {
    case Suits::clubs:
        os << "C";
        break;
    case Suits::diamonds:
        os << "D";
        break;
    case Suits::hearts:
        os << "H";
        break;
    case Suits::spades:
        os << "S";
        break;
    case Suits::undefined:
        os << "?";
        break;
    }
    return os;
}

/*
    Defines an overloaded prefix increment operator for the
    suit enum which just increments the enum to its next value
    using a switch statement.
*/
Suits &operator++(Suits &suit)
{
    switch (suit)
    {
    case Suits::clubs:
        suit = Suits::diamonds;
        break;
    case Suits::diamonds:
        suit = Suits::hearts;
        break;
    case Suits::hearts:
        suit = Suits::spades;
        break;
    case Suits::spades:
        suit = Suits::undefined;
        break;
    case Suits::undefined:
        suit = Suits::undefined;
        break;
    }
    return suit;
}