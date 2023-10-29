/*
    Suit.h
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (Suit.h) declares an overloaded ostream insertion
    operator and an overloaded prefix increment operator
    for the Suit enum. It also declares/defines the suit
    enum.
*/

// All includes
#pragma once

#include <iostream>

/*
    Declaration and definition of Suits enum.
*/
enum class Suits
{
    clubs,
    diamonds,
    hearts,
    spades,
    undefined
};

// Declaration of overloaded ostream insertion operator of Suits
std::ostream &operator<<(std::ostream &os, const Suits &s);

// Declaration of overloaded prefix increment operator for Suits
Suits &operator++(Suits &suit);