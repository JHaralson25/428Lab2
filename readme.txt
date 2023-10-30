------------------------------------------------------------------------------

CSE 428 Lab 2

Monish Kumar: k.monish@wustl.edu, 498823
Ethan Woolbert: e.d.woolbert@wustl.edu, 498162
Jacob Haralson: haralson.j@wustl.edu, 491111

------------------------------------------------------------------------------

The submitted program contains information about card, decks, and suits necessary to play
Texas Hold 'Em and Pinochle. The program also contains the necessary driver code in order
to play both games including dealing with decks, hands, and checking for valid game constraints.
The program also contains information to "play" each game printing players hands, the deck at 
given stages, and allows the players to play again or exit.

------------------------------------------------------------------------------
Going over the steps of the lab:

As this lab builds upon the previous lab and the bulk of the classes remain the same, we will be going over the additions we have made to the classes rather than restating everything.

Step 7: Card_T.h/cpp: We have added a lessSuit and lessRank functions. The functions both take in references to cards paramterized with a suit and rank, and return true if the suit or rank (respectively) of the first card is less than the second. Otherwise, the functions will return false.

Step 8: We decided to use the complier provided copy constructor for CardSet. This is because the compiler provided copy constructor will produce a deep copy, and in the case of the vector member variable, will call its default copy constructor to copy it over to the new object. The std::vector copy constructor produces a deep copy as well, so we do not have to worry about acessing the same vector member variable as the original object.

Step 9: CardSet_T.h: We added a public static member function that returns a scoped pointer to the cards member variable of the CardSet. This is an example of a controlled violation of encapsulation.

Step 10: PinochleGame.h/cpp: We added an enum class PinochleMelds to the header file that contains all the different melds that pinochle can have (dix, offsuitmarriage, fortyjacks, pinochle, insuitmarriage, sixtyqueens, eightykings, hundredaces, insuitrun, doublepinochle, fourhundredjacks, sixhundredqueens, eighthundredkings, thousandaces, insuitdoublerun). In the source file, we created an array that we can index into by casting an object of that enum class to an int to get its appropriate point value.

Step 11: PinochleGame.h/cpp: In the header file we declared an ostream insertion operator that takes a reference to an ostream as well as a const reference to a PinochleMelds object. In the source file, before defining the insertion operator, in a similar process to step 10, we created an array that we can index into by casting an object of that enum class to an int to get an appropriate string for that enum class. We then define the insertion operator to print out the label followed by the appropriate point value for a meld, done by indexing into both arrays.

Step 12: PinochleGame.h/cpp: In the header file we declare a private suit_independent_evaluation function that takes a constant reference to a CardSet paramterized with Suits,PinochleRanks and a reference to a vector of PinochleMelds. In the source file, we define said function, and before getting into specifics, the general purpose of this function is to find all the melds in the CardSet and push them onto the vector of PinochleMelds. Now getting into the specifics of the function, we first copy construct the CardSet as to not interfere with the original objects vector member variable. We then create a scoped pointer using the public static method defined in CardSet_T.h, and use it to access the vector member variable of the copied object. We then define variables to count each type of aces, kings, queens, and jacks. We then iterate through the hand and increment the appropriate variables if the cards is a match for any of them. We then check for each type of meld at the end, making sure to check higher priority melds ovefr lower priority ones (ie. we check for thousandaces over hundredaces), and push all the appropriate melds on the vector that was passed to us by reference.

Step 13: PinochleGame.h/cpp: In the header file, we decalre a void printMelds() helper function that will be used to print the melds of all the players. In this source file, we edit the existing play() method to print out the melds after every turn. Specifically, after we print out the players and their hands using the printPlayers() method, we call the printMelds() function. Within this function, we create a vector of PinochleMelds and then iterate through every hand. Within every iteration, we make sure to first clear the vector of melds to ensure it is fresh, and then call the suit_independent_evaluation function on the hand. We then iterate through the PinochleMelds vector, and if any melds were added to it (there are cases where no melds are added), the player number alongside their melds are printed to make it clear which players hold which melds.

Step 14: HoleEmGame.h/cpp: In the header we file, we added an enum class HoldEmRank that represent the different rankings of hands that a player can hold in TexasHoldEm (xhigh, pair, twopair, threeofakind, straight, flush fullhouse, fourofakind, straightflush, undefined). We also declare a public ostream insertion operator that takes a reference to an ostream and a constant reference to an object of type HoldEmRank. In the source file, we define said insertion operator. However, before that it should be note that similar to what we did in the PinochleGame class, we define a string array that we can use by casting an object of type HoldEmRank into an int in order to index into it and obtain an appropriate string corresponding to that rank. After this array, we then define the insertion operator to insert an appropriate string corresponding to the HoldEmRank object onto the ostream by casting and inexing into the aforementioned array.

Step 15: HoldEmGame.h/cpp: In the header file we define a holdem_rank_evaluation that takes a constant reference to a CardSet paramterized with Suits,HoldEmRanks. In the source file, we define said function, whose general purpose (before getting into specifics), is to check for the possible HoldEmRanks a hand can hold and return the highest value one. Similar to its counterpart in PinochleGame, we first copy construct the CardSet as to not interfere with the original objects vector member variable. We then create a scoped pointer using the public static method defined in CardSet_T.h, and use it to access the vector member variable of the copied object. We the use the std::sort method to sort the cards by rank (employing the lessRank function), and then suit (employing the lessSuit function), as this is what we believed would best help us search for HoldEmRanks within the hand. To start off, if the hand size is not 5, we return the undefined rank. We then declare variables to count the number of spades, hearts, clubs, and diamond within the hands, and loop through the hand, incrementing the appropriate variables for each card hit. We first check for four of a kind by comparing the ranks of the different cards (keeping in mind the sorted property of the hand), and if appropriate return fourofakind. We then check for a fullhouse in a similar manner, and if appropriate return fullhouse. We then check for a flush by checking the four variables declared earlier and seeing if any of them equal 5, in which case a flush is present,and we return a flush. We then check for three of a kind by comparing adjacent cards (once again keeping in mind the sorted property of the hand), and if appropriate return threeofakind. We then check for twopair by once again chekcing adjacent cards in an appropriate manner to check if there are two pairs, and if appropriate return twopair. We then similary check if a single pair exists and if so return a pair. It should be noted for both the twopair and pair cases, we do not explicity check that the other cards are of differenr ranks, as if they were not the function would have already returned a better rank beforehand (ie.fourofakind, fullhouse). Lastly, we check for both a straighflush and a straight. Essentially, we first check if the hand matches the lowest possible straight, and if so we then check if all of the cards are of the same suit using the four variables that keep track of suit mentioned earlier (if any of them equal 5 specifically). If the second condition is fullfiled, we return straighflush, otherwise we just return a straight. After checking this base case, we then check if the first cards rank is one less than the seconds,second one less than third, third one less than fourth, , lastly checking if the fourth cards rank is one less than the fifth cards rank (again this is possible specifically because our hand is sorted by rank). If this condition is met, once again we check the variables that counted suits, and if applicable return straightflush, otherwise we just return a flush. Finally, if none of these ranks were ever discovered in the hand, we return an xhigh.


------------------------------------------------------------------------------

Return values:

1. SUCCESS (0) This is returned upon successful completion of the program.

2. IMPROPER_GAME_INPUT (1) This is returned when the input provided by the player
    does not meet the necessary constraints to make or play a game.

3. GAME_MAKE_FAILURE (2) This is returned when the program has been passed valid
    input but fails to create an instance of the game.

4. GAME_PLAY_FAILURE (3) This is returned when the program fails in the play stage
    and if the error was a runtime error which could be thrown by trying to extract
    a card from an empty card set. All instances are checked in the program but this
    check and return value are to extra and absolute security.

------------------------------------------------------------------------------

The program contains a GlobalValues.h file in which program-wide constants are defined.
This allows for consistancy and ease if someone decides to change the program.

Global values:

1. CMD_PROG_IDX (0): Index of name of program in argv,

2. CMD_GAME_IDX (1): Index of name of game in argv.

3. CMD_START_IDX (2): Index of argv that contains the first input player name.

4. PINOCHLE_DEAL_SIZE (3): Size of each deal for each player in Pinochle.

5. HOLD_EM_HAND_SIZE (2): Hand size for every player in Hold 'Em.

6. PINOCHLE_PLAYER_CT (4): Required number of players for Pinochle.

7. MIN_HOLD_EM_PLAYER_CT (2): The minimum number of players that can play Hold 'Em.

8. MAX_HOLD_EM_PLAYER_CT (9): The maximum number of players that can play Hold 'Em.

9. HOLD_EM_FLOP_SIZE (3): Size of the flop for Hold 'Em. Will most likely never be
    changed.

10. HOLD_EM_NAME_STR ("HoldEm"): Name that a player should pass to the program in order
    to play the game Hold 'Em.

11. PINOCHLE_NAME_STR ("Pinochle") Name that a player should pass to the program in order
    to play the game Pinochle.

------------------------------------------------------------------------------

Errors:
We were fortunate enough not to run into any major errors.

------------------------------------------------------------------------------
Example Output:

Pinochle Output:

Without Melds Present:
Player: A
JS AD KC 
KS JC KD 
JC JS JH 
QS QH 10D 

Player: B
9H JH QD 
KC 10S QD 
10C 10H KD 
QC AD 10H 

Player: C
9C 10S 10C 
JD KH 9D 
AH QH AH 
QC KH 9S 

Player: D
JD AS AC 
AC 9D QS 
AS 9S KS 
10D 9H 9C 





Would you like to end the game? (yes/no): 

With Melds Present:

Player: A
KH KD JD 
9C QH QS 
9S JC 9D 
AC QS QC 

Player: B
10H 9H 10D 
10S KS QD 
QD AH JH 
9D AS KC 

Player: C
AH QH 10C 
KH AC 10S 
AS 10H AD 
10D 9C JH 

Player: D
JC KC KD 
9S 10C 9H 
KS AD JD 
JS JS QC 



Player 3: hundredaces 100
 

Would you like to end the game? (yes/no): 


HoldEm Output:



Example Output When Wrong Input Given (showcasing our usage message):

[k.monish@linuxlab004 428Lab2]$ ./lab2 Pinochle A B C
Usage: ./lab2 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)

[k.monish@linuxlab004 428Lab2]$ ./lab2 HoldEm A B C D E F G H I J K L M N O P
Usage: ./lab2 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)