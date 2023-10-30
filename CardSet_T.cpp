/*
    CardSet_T.cpp
    Ethan Woolbert: e.d.woolbert@wustl.edu
    Monish Kumar: k.monish@wustl.edu
    Jacob Haralson: haralson.j@wustl.edu
    (CardSet_T.cpp) defines a public print funtion,
    insertion operator, is_empty helper function, and
    a get_size helper function for the paramaterized
    CardSet template class.
*/

// All includes
#include <iostream>
#include <vector>
using namespace std;

#include "CardSet_T.h"

/*
    Public print method for the CardSet template class parameterized by
    suit and rank. The functions prints every card to the input ostream
    with divisions for a certain number of cards per line.
*/
template <typename Suit, typename Rank>
void CardSet<Suit, Rank>::print(std::ostream &os, size_t num_per_line)
{
    size_t card_ct = 0;
    // Iterate through every card
    for (long unsigned int i = 0; i < cards.size(); ++i)
    {
        os << cards[i] << " ";
        ++card_ct;
        // Print endl if at last card in line
        if (card_ct == num_per_line)
        {
            os << endl;
            card_ct = 0;
        }
    }
}

/*
   Overloaded insertion operator for the CardSet template class takes the last card
   from this class and pushes it to input CardSet class.
*/
template <typename Suit, typename Rank>
CardSet<Suit, Rank> &CardSet<Suit, Rank>::operator>>(CardSet<Suit, Rank> &cs)
{
    // Checks to see if it is possible to pop card from current class
    if (this->is_empty())
    {
        throw runtime_error("ERROR: Tried to extract from empty deck");
    }

    // Deep copies card, pushes it to input class, and pops from current class.
    Suit s = this->cards.back().suit;
    Rank r = this->cards.back().rank;
    cs.cards.push_back(Card<Suit, Rank>(s, r));
    this->cards.pop_back();
    return *this;
}

/*
    Public CardSet helper function to check if private member variable is empty
*/
template <typename Suit, typename Rank>
bool CardSet<Suit, Rank>::is_empty()
{
    return (this->cards.size() == 0);
}

/*
    Public CardSet helper function to return size of private member variable
*/
template <typename Suit, typename Rank>
int CardSet<Suit, Rank>::get_size()
{
    return (this->cards.size());
}