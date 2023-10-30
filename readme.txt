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

Step 12: PinochleGame.h/cpp: In the header file we declare a private suit_independent_evaluation function that takes a constant reference to a CardSet and a reference to a vector of PinochleMelds. In the source file, we define said function, and before getting into specifics, the general purpose of this function is to find all the melds in the CardSet and push them onto the vector of PinochleMelds. Now getting into the specifics of the function, we first copy construct the CardSet as to not interfere with the original objects vector member variable. We then create a scoped pointer using the public static method defined in CardSet_T.h, and use it to access the vector member variable of the copied object. We then define variables to count each type of aces, kings, queens, and jacks. We then iterate through the hand and increment the appropriate variables if the cards is a match for any of them. We then check for each type of meld at the end, making sure to check higher priority melds ovefr lower priority ones (ie. we check for thousandaces over hundredaces), and push all the appropriate melds on the vector that was passed to us by reference.

Step 13: PinochleGame.cpp: In this step we edit the existing play() method to print out the melds after every turn. Specifically, after we print out the players and their hands using the printPlayers() method, we create a vector of PinochleMelds and then iterate through every hand. Within every iteration, we make sure to first clear the vector of melds to ensure it is fresh, and then call the suit_independent_evaluation function on the hand. We then iterate through the PinochleMelds vector, and if any melds were added to it (there are cases where no melds are added), the player number alongside their melds are printed to make it clear which players hold which melds.

Step 14: HoleEmGame.h/cpp: In the header we file, we added an enum class HoldEmRank that represent the different rankings of hands that a player can hold in TexasHoldEm (xhigh, pair, twopair, threeofakind, straight, flush fullhouse, fourofakind, straightflush, undefined). We also declare a public ostream insertion operator that takes a reference to an ostream and a constant reference to an object of type HoldEmRank. In the source file, we define said insertion operator. However, before that it should be note that similar to what we did in the PinochleGame class, we define a string array that we can use by casting an object of type HoldEmRank into an int in order to index into it and obtain an appropriate string corresponding to that rank. After this array, we then define the insertion operator to insert an appropriate string corresponding to the HoldEmRank object onto the ostream by casting and inexing into the aforementioned array.


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
        
        [e.d.woolbert@linuxlab002 428-lab1]$ ./lab1 HoldEm p1 p2 p3 p4 p5 p6 p7 p8 p9 p10
        Usage: ./lab1 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)
        
        [e.d.woolbert@linuxlab002 428-lab1]$ ./lab1 Pinochle p1 p2 p3 p4 p5
        Usage: ./lab1 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)      
