/*
    CardSet_T.h
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (CardSet_T.h) declares CardSet template class with
    5 public functions and a private member variable.
*/

// All includes
#pragma once

#include <iostream>
#include <vector>

#include "Card_T.h"

/*
    Declaration of CardSet class with a public print funtion,
    insertion operator, is_empty helper function, a get_size helper
    function, a destructor, a public static function that return a scoped pointer to the cards member variable and a private vector member variable
    containing Card classes.
*/
template <typename Suit, typename Rank>
class CardSet
{
public:
    void print(std::ostream &os, size_t num_per_line);
    CardSet<Suit, Rank> &operator>>(CardSet<Suit, Rank> &cs);
    bool is_empty();
    int get_size();
    static std::vector<Card <Suit, Rank> > CardSet::*getVector() { return &CardSet::cards; }

protected:
    std::vector<Card <Suit, Rank> > cards;
};

// Inclusion gaurds for CardSet_T.cpp
#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "CardSet_T.cpp"
#endif