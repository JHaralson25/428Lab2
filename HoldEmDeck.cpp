/*
    HoldEmDeck.cpp
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (HoldEmDeck.cpp) defines an ostream insertion operator,
    a prefix increment operator, and a default constructor for
    the HoldEmDeck class.
*/

// All includes
#include <iostream>
#include <vector>
using namespace std;

#include "Suit.h"
#include "Card_T.h"
#include "HoldEmDeck.h"

/*
    Definition of the HoldEmDeck default constructor.
    It adds "Cards" to the vector member variable.
*/
HoldEmDeck::HoldEmDeck()
{
    // Creates instances of rank and suit enums
    HoldEmRanks h;
    Suits s = Suits::clubs;

    do
    {
        h = HoldEmRanks::two;
        do
        {
            cards.push_back(Card(s, h));
            ++h;
        } while (h != HoldEmRanks::undefined);
        ++s;
    } while (s != Suits::undefined);
}

/*
    Definition of the overloaded HoldEmDeck ostream insertion operator.
    Prints number/symbol to the ostream and returns the ostream.
*/
ostream &operator<<(ostream &os, const HoldEmRanks &her)
{
    switch (her)
    {
    case HoldEmRanks::two:
        os << "2";
        break;
    case HoldEmRanks::three:
        os << "3";
        break;
    case HoldEmRanks::four:
        os << "4";
        break;
    case HoldEmRanks::five:
        os << "5";
        break;
    case HoldEmRanks::six:
        os << "6";
        break;
    case HoldEmRanks::seven:
        os << "7";
        break;
    case HoldEmRanks::eight:
        os << "8";
        break;
    case HoldEmRanks::nine:
        os << "9";
        break;
    case HoldEmRanks::ten:
        os << "10";
        break;
    case HoldEmRanks::jack:
        os << "J";
        break;
    case HoldEmRanks::queen:
        os << "Q";
        break;
    case HoldEmRanks::king:
        os << "K";
        break;
    case HoldEmRanks::ace:
        os << "A";
        break;
    case HoldEmRanks::undefined:
        os << "?";
        break;
    }
    return os;
}

/*
    Definition of the overloaded HoldEmDeck prefix insertion operator.
    Increments rank to next rank via a switch statement.
*/
HoldEmRanks &operator++(HoldEmRanks &her)
{
    switch (her)
    {
    case HoldEmRanks::two:
        her = HoldEmRanks::three;
        break;
    case HoldEmRanks::three:
        her = HoldEmRanks::four;
        break;
    case HoldEmRanks::four:
        her = HoldEmRanks::five;
        break;
    case HoldEmRanks::five:
        her = HoldEmRanks::six;
        break;
    case HoldEmRanks::six:
        her = HoldEmRanks::seven;
        break;
    case HoldEmRanks::seven:
        her = HoldEmRanks::eight;
        break;
    case HoldEmRanks::eight:
        her = HoldEmRanks::nine;
        break;
    case HoldEmRanks::nine:
        her = HoldEmRanks::ten;
        break;
    case HoldEmRanks::ten:
        her = HoldEmRanks::jack;
        break;
    case HoldEmRanks::jack:
        her = HoldEmRanks::queen;
        break;
    case HoldEmRanks::queen:
        her = HoldEmRanks::king;
        break;
    case HoldEmRanks::king:
        her = HoldEmRanks::ace;
        break;
    case HoldEmRanks::ace:
        her = HoldEmRanks::undefined;
        break;
    case HoldEmRanks::undefined:
        her = HoldEmRanks::undefined;
        break;
    }
    return her;
}