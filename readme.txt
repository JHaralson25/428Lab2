------------------------------------------------------------------------------

CSE 428 Lab 1

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

Design Decisions:

-Card_T:
	For Card_T our << operator outputs the rank and suit of the card with no line breaks as they aren't necessary

-CardSet_T:
	For CardSet_T the print method will iterate over the the cards and print each card with a space after it for readability.
	When the max number of cards per line is reached then the method will move to a new line.

	The >> operator will first check to see if the deck is empty, and if so will throw a runtime error which is caught later.
	It will then look at the card in the back of the cards vector, deep copy it, and push it into the vector of the other cardset.
	Then it pops the card we just deep copied.

    We handle processing the expections of >> by always checking is_empty before using the insertion operator in a CardSet. Therefore an
    exception will never be thrown because we always check before entering into the insertion operator function for CardSet. However,
    if the function does still for some reason throw an error something has gone very very wrong with the program in an unrecoverable
    way becuase we checked the condition before using the insertion operator. Therefore we do not try to process these exceptions in
    each Game/Deck file but instead wrap our play() call in main with a try catch because we cannot process the exception at the Game/Deck
    level as it likely happened because of memory corruption or some other catastrophic reason. I think this aligns with the instruction to
    handle potential errors as soon as possible in the code because the only errors that will propagate up to main are unrecoverable errors
    that will be handled in main and will not propagate out further.

-Deck_T:
	For the shuffle method we use a pseudorandom number generator as this is the most efficient way to generate a random number

-GlobalValues:
	A global values header file was created for good modularity. It allows us to store and reuse strings and enums.
	The char * HOLD_EM_NAME_STR and PINOCHLE_NAME_STR are declared as inline to prevent multiple definition errors when the header file
	is included. This falls in line with the c++17 standard.
	
	The possible return values of SUCCESS, IMPROPER_GAME_INPUT, and GAME_MAKE_FAILURE are present. These are the only options which
	would cause the program to exit, and as such are the only return values

-HoldEmDeck
	Publically inherets from Deck_T as we should be able to use all protected methods and variables

	The constructor for HoldEmDeck iterates through each of the ranks of each suit, pushing back a single card each time with
	two nested do while loops

	The << operator for the HoldEmRank enum uses a switch statement to print out a single character for each rank, or a ? for undefined

	The ++ operator for the HoldEmRank enum uses a switch statement to move each rank up to the next one, or cycle on undefined

-PinochleDeck
	Publically inherets from Deck_T as we should be able to use all protected methods and variables

	The constructor for PinochleDeck iterates through each of the ranks of each suit, pushing back two cards each time with
	two nested do while loops

	The << operator for the PinochleRank enum uses a switch statement to print out a single character for each rank, or a ? for undefined

	The ++ operator for the Pinochle enum uses a switch statement to move each rank up to the next one, or cycle on undefined

	This class has a very similar format to HoldEmDeck

-Suit
	Suit is defined to be an enum class to use the << and ++ operator overloads

	The two operator overloads use a switch statement to print out a single character for the Suit in the case of << and in the case of
	++ it will move each suit to the next one in the order of clubs, diamonds, hearts, and spades and it will cycle on undefined

-Game
	Function terminateGame() was moved from the derived classes up to the game class as it could easily be extended to those classes.
	Other functions, however, were not moved up to the Game class as that would require making Game a template class, which we didn't
	deem necessary

-HoldEmGame
	HoldEmGame publicly inherits from the Game class

	For the play method, we have a few helper functions we loop through to simplify things. The deal() method deals out cards based on the state of the game, and then prints out the board using printBoard(). printPlayers() loops through every player and prints out their respective names and hands. printBoard() prints out the current game board. collectHands() collects the hands of all players and returns them to the deck. collectBoard() collects all the cards on the board and returns them to the deck.

	When printing the players using the printPlayers() we will iterate through all the players, print out the player name, 
	move to a new line, we will then call the print method on the CardSet for that player and then shift to a new line


	When printing the board using the printBoard() method, we will print out a header of BOARD (" << hes << "): and then on the same line
	call board.print, which calls the cardset print method. This will automatically move us to a new line, so we don't include endl in this method.

-PinochleGame
	PinochleGame publicly inherits from the Game class

	For the play method, we have a few helper functions we loop through to simplify things. The deal() method deals out cards based on the state of the game. printPlayers() loops through every player and prints out their respective names and hands. collectHands() collects the hands of all players and returns them to the deck. 

	When printing the players using the printPlayers() we will iterate through all the players, print out the player name, 
	move to a new line, we will then call the print method on the CardSet for that player and then shift to a new line

-lab1
	In our main file we first check to ensure proper command line input

	We then calculate the number of players based on the number of command line arguments

	Then, we check to make sure that the game name input is proper in the main function, instead of in create, so that create
	only does just that, create

	After this, we create the shared pointer for the game

	Then in the main function we make sure the shared pointer was initialized correctly, and if it was we play the game
	
	These sanity checks guarantee there should be no errors for improper input as we will identify them and exit appropriately. 

	Playing the game is also surrounded by a try catch block so that no errors propogate out of main uncaught.

------------------------------------------------------------------------------

Errors and Warnings Encountered:

	One of the primary errors encountered was when including the GlobalValues.h file in lab1.cpp, a double declaration error was thrown
	for HOLDEM_NAME_STR char* and the PINOCHLE_NAME_STR char*. This error was corrected when both of these char*s were declared as
	inline.

	For each for loop used, we received a warning stating that we were comparing integer expressions of different signedness. 
	This was resolved by changing the ints to be unsigned long ints.

	Another common error was that we often forgot to add new files to the Makefile, so when files already in the Makefile tried to
	include them or use them in any way, errors were thrown. We just had to be certain to include every file in the Makefile
	right after we created it to fix this error.

------------------------------------------------------------------------------

Tests:
	
	Memory Leaks were checked for using valgrind with the command valgrind --leak-check=full ./lab1.
	After playing the game and terminating it, we were left with the outputs

	Pinochle:
	==18302== 
	==18302== HEAP SUMMARY:
	==18302==     in use at exit: 0 bytes in 0 blocks
	==18302==   total heap usage: 39 allocs, 39 frees, 75,433 bytes allocated
	==18302== 
	==18302== All heap blocks were freed -- no leaks are possible
	==18302== 
	==18302== For lists of detected and suppressed errors, rerun with: -s
	==18302== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

	HoldEm:
	==18271== 
	==18271== HEAP SUMMARY:
	==18271==     in use at exit: 0 bytes in 0 blocks
	==18271==   total heap usage: 31 allocs, 31 frees, 74,689 bytes allocated
	==18271== 
	==18271== All heap blocks were freed -- no leaks are possible
	==18271== 
	==18271== For lists of detected and suppressed errors, rerun with: -s
	==18271== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

	Each game ran perfectly at the end with no memory leaks.

	Output from Pinochle:
		[haralson.j@linuxlab002 lab1]$ ./lab1 Pinochle p1 p2 p3 p4
        Player: p1
        10H JC AC
        AS QH AC
        9C QS AH
        AH JH QH

        Player: p2
        KC JD JS
        KD KH 10C
        JC 9S 9S
        QC KC KS

        Player: p3
        10C QD QC
        10D 9D KD
        10H 10S 10D
        9H KH KS

        Player: p4
        9C JH JD
        10S QS AS
        JS QD AD
        AD 9D 9H

        Would you like to end the game? (yes/no):

        This is the expected output given the input.

    Output from Pinochle with multiple runs of the game:
        [e.d.woolbert@linuxlab002 428-lab1]$ ./lab1 Pinochle p1, p2, p3, p4
        Player: p1,
        10C QD AC 
        JC 10S JS 
        AS KS 9D 
        QH 10H JC 

        Player: p2,
        JD 10D KC 
        KH AD 9H 
        QC AD 9S 
        9D KH 10H 

        Player: p3,
        JS JH QD 
        QS KC AH 
        9S JH QH 
        KD KS 10C 

        Player: p4
        10D JD QC 
        AH KD QS 
        10S 9C 9C 
        AC 9H AS 

        Would you like to end the game? (yes/no): 
        no
        Player: p1,
        QS 9H QD 
        QD JS 10D 
        QH QH AC 
        9C JS KC 

        Player: p2,
        JC KS 9C 
        AH KD 9D 
        10D AD 10H 
        JH KH 9S 

        Player: p3,
        JD 10H 10C 
        QC KS 9S 
        JD AH QC 
        AD JC 10S 

        Player: p4
        9D KH KD 
        AC JH AS 
        10S 9H KC 
        AS QS 10C 

        Would you like to end the game? (yes/no): 
        no
        Player: p1,
        AS 10D 10S 
        JD JD QC 
        JS JC QS 
        KH QS 9C 

        Player: p2,
        AD KS 10D 
        9D 10C AD 
        9S QH 10H 
        AS KS 9D 

        Player: p3,
        AC 10C QD 
        QH KC AC 
        QD JH JH 
        9H 10H 9S 

        Player: p4
        9C KC AH 
        KH KD JC 
        KD 9H QC 
        AH 10S JS 

        Would you like to end the game? (yes/no):

        This is the expected output given the input.

	Output from HoldEm with various numbers of players:
		[haralson.j@linuxlab002 lab1]$ ./lab1 HoldEm p1 p2
        Player: p1
        AH 5S

        Player: p2
        AD 2H

        BOARD (flop): 8S 9C QH
        BOARD (turn): 8S 9C QH 7S
        BOARD (river): 8S 9C QH 7S 2C
        Would you like to end the game? (yes/no):

        [e.d.woolbert@linuxlab002 428-lab1]$ ./lab1 HoldEm p1, p2, p3, p4, p5
        Player: p1,
        8D 6S 

        Player: p2,
        7H JD 

        Player: p3,
        AH 10S 

        Player: p4,
        5H KS 

        Player: p5
        5D KC 

        BOARD (flop): QH JH 4D 
        BOARD (turn): QH JH 4D 3C 
        BOARD (river): QH JH 4D 3C 8C 
        Would you like to end the game? (yes/no):

        This is the expected output given the input.

    Output from HoldEm with multiple runs of the game:
        [e.d.woolbert@linuxlab002 428-lab1]$ ./lab1 HoldEm p1 p2 p3 p4
        Player: p1
        KC 6D 

        Player: p2
        7D 5S 

        Player: p3
        JD QH 

        Player: p4
        4C 10C 

        BOARD (flop): 6C 9D 8C 
        BOARD (turn): 6C 9D 8C 9S 
        BOARD (river): 6C 9D 8C 9S QD 
        Would you like to end the game? (yes/no): 
        no
        Player: p1
        KC 3C 

        Player: p2
        9C 9D 

        Player: p3
        6S AS 

        Player: p4
        3S 8H 

        BOARD (flop): 4S 2S 8D 
        BOARD (turn): 4S 2S 8D 4D 
        BOARD (river): 4S 2S 8D 4D KS 
        Would you like to end the game? (yes/no): 
        no
        Player: p1
        10H 4S 

        Player: p2
        7H KD 

        Player: p3
        AD 9H 

        Player: p4
        8D 5D 

        BOARD (flop): 8S 6S 7D 
        BOARD (turn): 8S 6S 7D 9D 
        BOARD (river): 8S 6S 7D 9D 2H 
        Would you like to end the game? (yes/no):

        This is the expected output given the input.

    Testing inpropper input (All inpropper inputs correctly failed to run and output the correct usage message):
        [e.d.woolbert@linuxlab002 428-lab1]$ ./lab1 Pinochle
        Usage: ./lab1 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)
        
        [e.d.woolbert@linuxlab002 428-lab1]$ ./lab1 Pino chle
        Usage: ./lab1 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)
        
        [e.d.woolbert@linuxlab002 428-lab1]$ ./lab1 HoldEm
        Usage: ./lab1 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)
        
        [e.d.woolbert@linuxlab002 428-lab1]$ ./lab1 Hold Em
        Usage: ./lab1 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)
        
        [e.d.woolbert@linuxlab002 428-lab1]$ ./lab1 HoldEm p1
        Usage: ./lab1 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)
        
        [e.d.woolbert@linuxlab002 428-lab1]$ ./lab1 HoldEm p1 p2 p3 p4 p5 p6 p7 p8 p9 p10
        Usage: ./lab1 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)
        
        [e.d.woolbert@linuxlab002 428-lab1]$ ./lab1 Pinochle p1 p2 p3 p4 p5
        Usage: ./lab1 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)      