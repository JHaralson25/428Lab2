------------------------------------------------------------------------------

CSE 428 Lab 2

Monish Kumar: k.monish@wustl.edu, 498823
Ethan Woolbert: e.d.woolbert@wustl.edu, 498162
Jacob Haralson: haralson.j@wustl.edu, 491111

------------------------------------------------------------------------------

The submitted program contains information about cards, decks, and suits necessary to play
Texas Hold 'Em and Pinochle. The program also contains the necessary driver code in order
to play both games including dealing with decks, hands, and checking for valid game constraints.
The program also contains information to "play" each game printing players hands, the deck at 
given stages, and the driver code to calculate the rankings and scores of different hands, 
and allows the players to play again or exit.

------------------------------------------------------------------------------
Going over the steps of the lab:

As this lab builds upon the previous lab and the bulk of the classes and files remain the same, we will be going over the additions we have made to the 
classes rather than restating everything.

Step 7: Card_T.h/cpp: We have added a lessSuit and lessRank functions. The functions both take in references to cards paramterized with a suit and rank, 
and return true if the suit or rank (respectively) of the first card is less than the second. Otherwise, the functions will return false.

Step 8: We decided to use the complier provided copy constructor for CardSet. This is because the compiler provided copy constructor will produce a 
deep copy, and in the case of the vector member variable, will call its default copy constructor to copy it over to the new object. The std::vector 
copy constructor produces a deep copy as well, so we do not have to worry about acessing the same vector member variable as the original object.

Step 9: CardSet_T.h: We added a public static member function that returns a scoped pointer to the cards member variable of the CardSet. This is an 
example of a controlled violation of encapsulation.

Step 10: PinochleGame.h/cpp: We added an enum class PinochleMelds to the header file that contains all the different melds that pinochle can have 
(dix, offsuitmarriage, fortyjacks, pinochle, insuitmarriage, sixtyqueens, eightykings, hundredaces, insuitrun, doublepinochle, fourhundredjacks, 
sixhundredqueens, eighthundredkings, thousandaces, insuitdoublerun). In the source file, we created an array that we can index into by casting an 
object of that enum class to an int to get its appropriate point value.

Step 11: PinochleGame.h/cpp: In the header file we declared an ostream insertion operator that takes a reference to an ostream as well as a const 
reference to a PinochleMelds object. In the source file, before defining the insertion operator, in a similar process to step 10, we created an array 
that we can index into by casting an object of that enum class to an int to get an appropriate string for that enum class. We then define the insertion 
operator to print out the label followed by the appropriate point value for a meld, done by indexing into both arrays.

Step 12: PinochleGame.h/cpp: In the header file we declare a private suit_independent_evaluation function that takes a constant reference to a CardSet 
paramterized with Suits,PinochleRanks and a reference to a vector of PinochleMelds. In the source file, we define said function, and before getting into 
specifics, the general purpose of this function is to find all the melds in the CardSet and push them onto the vector of PinochleMelds. Now getting into 
the specifics of the function, we first copy construct the CardSet as to not interfere with the original objects vector member variable. We then create a 
scoped pointer using the public static method defined in CardSet_T.h, and use it to access the vector member variable of the copied object. We then define 
variables to count each type of aces, kings, queens, and jacks. We then iterate through the hand and increment the appropriate variables if the cards is a 
match for any of them. We then check for each type of meld at the end, making sure to check higher priority melds ovefr lower priority ones (ie. we check 
for thousandaces over hundredaces), and push all the appropriate melds on the vector that was passed to us by reference.

Step 13: PinochleGame.h/cpp: In the header file, we decalre a void printMelds() helper function that will be used to print the melds of all the players. 
In this source file, we edit the existing play() method to print out the melds after every turn. Specifically, after we print out the players and their 
hands using the printPlayers() method, we call the printMelds() function. Within this function, we create a vector of PinochleMelds and then iterate 
through every hand. Within every iteration, we make sure to first clear the vector of melds to ensure it is fresh, and then call the 
suit_independent_evaluation function on the hand. We then iterate through the PinochleMelds vector, and if any melds were added to it (there are cases 
where no melds are added), the player number alongside their melds are printed to make it clear which players hold which melds.

Step 14: HoleEmGame.h/cpp: In the header we file, we added an enum class HoldEmRank that represent the different rankings of hands that a player can 
hold in TexasHoldEm (xhigh, pair, twopair, threeofakind, straight, flush fullhouse, fourofakind, straightflush, undefined). We also declare a public 
ostream insertion operator that takes a reference to an ostream and a constant reference to an object of type HoldEmRank. In the source file, we define 
said insertion operator. However, before that it should be note that similar to what we did in the PinochleGame class, we define a string array that we 
can use by casting an object of type HoldEmRank into an int in order to index into it and obtain an appropriate string corresponding to that rank. After
 this array, we then define the insertion operator to insert an appropriate string corresponding to the HoldEmRank object onto the ostream by casting 
 and inexing into the aforementioned array.

Step 15: HoldEmGame.h/cpp: In the header file we define a holdem_rank_evaluation that takes a constant reference to a CardSet paramterized with Suits,
HoldEmRanks. In the source file, we define said function, whose general purpose (before getting into specifics), is to check for the possible HoldEmRanks
a hand can hold and return the highest value one. Similar to its counterpart in PinochleGame, we first copy construct the CardSet as to not interfere 
with the original objects vector member variable. We then create a scoped pointer using the public static method defined in CardSet_T.h, and use it to 
access the vector member variable of the copied object. We the use the std::sort method to sort the cards by rank (employing the lessRank function), 
and then suit (employing the lessSuit function), as this is what we believed would best help us search for HoldEmRanks within the hand. To start off, 
if the hand size is not 5, we return the undefined rank. We then declare variables to count the number of spades, hearts, clubs, and diamond within 
the hands, and loop through the hand, incrementing the appropriate variables for each card hit. We first check for four of a kind by comparing the 
ranks of the different cards (keeping in mind the sorted property of the hand), and if appropriate return fourofakind. We then check for a fullhouse 
in a similar manner, and if appropriate return fullhouse. We then check for a flush by checking the four variables declared earlier and seeing if 
any of them equal 5, in which case a flush is present,and we return a flush. We then check for three of a kind by comparing adjacent cards (once 
again keeping in mind the sorted property of the hand), and if appropriate return threeofakind. We then check for twopair by once again chekcing 
adjacent cards in an appropriate manner to check if there are two pairs, and if appropriate return twopair. We then similary check if a single 
pair exists and if so return a pair. It should be noted for both the twopair and pair cases, we do not explicity check that the other cards are 
of differenr ranks, as if they were not the function would have already returned a better rank beforehand (ie.fourofakind, fullhouse). Lastly, 
we check for both a straighflush and a straight. Essentially, we first check if the hand matches the lowest possible straight, and if so we then 
check if all of the cards are of the same suit using the four variables that keep track of suit mentioned earlier (if any of them equal 5 
specifically). If the second condition is fullfiled, we return straighflush, otherwise we just return a straight. After checking this base case, 
we then check if the first cards rank is one less than the seconds,second one less than third, third one less than fourth, , lastly checking if 
the fourth cards rank is one less than the fifth cards rank (again this is possible specifically because our hand is sorted by rank). If this 
condition is met, once again we check the variables that counted suits, and if applicable return straightflush, otherwise we just return a flush. 
Finally, if none of these ranks were ever discovered in the hand, we return an xhigh.

Step 16: HoldEmGame.h/cpp: For this step we created a nested struct inside our HoldEmGame class. This struct conatined info related to a player
and their current hand and ranking of that hand. We created an overloaded < comparison operator for the HandInfo struct. This overloaded < operator
determined if the ranking of the hand of a player was greater or less than the other players hand. For pairs we first get the position of the pair
we then compare the ranks of the pair and if they are the same we compare based on the high card. For two pair we get the position of the two pairs,
compare them, and if they are the same we determine which is greater based on the remaining high card. For three of a kind we get the position of the
three cards and compare them. We then also decided to make our program play by valid poker rules and compare the remaining cards for the high card. For the
straigh we simply compare the 1st card of the sorted straight (to account for ace) to determine their order. For flush we simply recursivly compare based 
on the high card. For the fullhouse we compare based on the 3 cards then we also decided to implement valid poker rules and compare the remaining pair of
the fullhouse. For four of a kind we compare the 4 cards against each other and also we decided to implement valid poker rules and compare the remaining
high cards of the 5 card hand. For the straight flush we compared using the same system as the straight where we looked at the first card (again to account
for aces in the sorted list). The overloaded operator also just returned the comparision of just the ranks if they differed at all.

Step 17: HoldEmGame.h/cpp: For this step we created a function called checkWinner() which will push back all of the player names, hands, and 
an undefined HoldEmHandRank enum value to a vector. The function then pushes back the info from the board, and runs our holdem_hand_evaluation 
function on each hand. Then, all hands are sorted from worst hand to best hand, and printed in that order.

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

6. HOLD_EM_TOTAL_HAND_SIZE (5): Hand size of best combination of player and board.

7. HOLD_EM_PAIR_POS (4): Total number of possible positions for pairs given sorted Hold 'Em 
    array of cards.

8. HOLD_EM_TRIP_POS (3): Total number of possible positions for tripples given sorted Hold 'Em 
    array of cards.

9. HOLD_EM_QUAD_POS (2): Total number of possible positions for four in a row given sorted Hold 'Em 
    array of cards.

10. ADJACENT (1): Adjacency offset in array.

11. SECOND_ADJACENT (2): Adjacency offset for second element in array.

12. TERTIARY_ADJACENT (3): Adjacency offset for third element in array.

13. HOLD_EM_MAX_IDX (4): Maximum index an array of size HOLD_EM_TOTAL_HAND_SIZE can have.

14. PINOCHLE_PLAYER_CT (4): Required number of players for Pinochle.

15. PINOCHLE_MAJOR_CT (2): Count of cards required for the "Major" Pinochle Melds

16. PINOCHLE_MINOR_CT (1): Count of cards required for the "Minor" Pinochle Melds

17. MIN_HOLD_EM_PLAYER_CT (2): The minimum number of players that can play Hold 'Em.

18. MAX_HOLD_EM_PLAYER_CT (9): The maximum number of players that can play Hold 'Em.

19. HOLD_EM_FLOP_SIZE (3): Size of the flop for Hold 'Em. Will most likely never be
    changed.

20. HOLD_EM_NAME_STR ("HoldEm"): Name that a player should pass to the program in order
    to play the game Hold 'Em.

21. PINOCHLE_NAME_STR ("Pinochle") Name that a player should pass to the program in order
    to play the game Pinochle.

------------------------------------------------------------------------------

Errors:
We were fortunate enough not to run into any major errors. The only thing we really had problems with
was the pointer dereferencing for the protected vector pointer. We had to use a scoped pointer. This worked
perfectly. There were no other major errors besides basic syntax errors.

------------------------------------------------------------------------------

Tests:

    Memory leaks were checked using valgrind.

    [e.d.woolbert@linuxlab002 428Lab2]$ valgrind --leak-check=full ./lab2 Pinochle ethan mo libby lowell
    ==2180== Memcheck, a memory error detector
    ==2180== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==2180== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
    ==2180== Command: ./lab2 Pinochle ethan mo libby lowell
    ==2180==

    (Removed program output for conciseness)
    
    ==2180== 
    ==2180== HEAP SUMMARY:
    ==2180==     in use at exit: 0 bytes in 0 blocks
    ==2180==   total heap usage: 51 allocs, 51 frees, 76,257 bytes allocated
    ==2180== 
    ==2180== All heap blocks were freed -- no leaks are possible
    ==2180== 
    ==2180== For lists of detected and suppressed errors, rerun with: -s
    ==2180== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)



    [e.d.woolbert@linuxlab002 428Lab2]$ valgrind --leak-check=full ./lab2 HoldEm ethan mo libby lowell
    ==3228== Memcheck, a memory error detector
    ==3228== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==3228== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
    ==3228== Command: ./lab2 HoldEm ethan mo libby lowell
    ==3228==

    (Removed program output for conciseness)

    ==3228== 
    ==3228== HEAP SUMMARY:
    ==3228==     in use at exit: 0 bytes in 0 blocks
    ==3228==   total heap usage: 93 allocs, 93 frees, 77,237 bytes allocated
    ==3228== 
    ==3228== All heap blocks were freed -- no leaks are possible
    ==3228== 
    ==3228== For lists of detected and suppressed errors, rerun with: -s
    ==3228== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)



    Example Pinochle Outputs:

    Example Output 1:
    [e.d.woolbert@linuxlab002 428Lab2]$ ./lab2 Pinochle a b c d

    PLAYERS
    Player: a
    JS JC KS 
    QD 10C AD 
    AS JH QS 
    10S 10H JD 

    Player: b
    9C KD QH 
    QD AH QC 
    KC 9D QC 
    QS 9H KC 

    Player: c
    10S JS AC 
    10D 9S 9H 
    AH KH 9D 
    JC QH AS 

    Player: d
    10C AC JH 
    AD 9C KS 
    10D 10H KD 
    9S KH JD 

    MELDS
    Player a:
        fortyjacks 40
        pinochle 40
    Player b:
        sixtyqueens 60
    Player c:
    Player d:

    Would you like to end the game? (yes/no): 
    yes

    This output ran correctly given the inputs from the player.

    Example Output 2:
    [e.d.woolbert@linuxlab002 428Lab2]$ ./lab2 Pinochle a b c d

    PLAYERS
    Player: a
    KD QC QD 
    10D AH JH 
    9C JD KH 
    QS AS AC 

    Player: b
    9S QC 9C 
    10H AC KS 
    KC 10C KC 
    10H 10C 9S 

    Player: c
    AS 9H KD 
    QS QD 9D 
    10D QH JC 
    AH JS 9D 

    Player: d
    10S AD KH 
    9H AD JC 
    JS JH 10S 
    JD QH KS 

    MELDS
    Player a:
        pinochle 40
    Player b:
    Player c:
    Player d:
        fortyjacks 40

    Would you like to end the game? (yes/no): 
    no

    PLAYERS
    Player: a
    JS QS AC 
    9H AD KH 
    JH QD 10S 
    10C KS AD 

    Player: b
    AS 10H KS 
    10H 9S QS 
    AS 10D QH 
    9D 9H JC 

    Player: c
    10C KD KH 
    QD KD KC 
    JC 10S AH 
    9C QC QC 

    Player: d
    9S JD JH 
    9D KC JD 
    10D AC JS 
    QH 9C AH 

    MELDS
    Player a:
    Player b:
    Player c:
    Player d:

    Would you like to end the game? (yes/no): 
    yes

    This output also ran correctly given the input from the player



    Example Hold 'Em Outputs:

    Example Output 1:
    [e.d.woolbert@linuxlab002 428Lab2]$ ./lab2 HoldEm a b c d e f g h

    PLAYERS
    Player: a
    10H 5C 

    Player: b
    4H AC 

    Player: c
    9H 4D 

    Player: d
    6S QH 

    Player: e
    QD 3D 

    Player: f
    6H 7S 

    Player: g
    8S KS 

    Player: h
    4S AS 

    BOARD (flop): 10D 9D 6D 

    RANKINGS
    Name: g
    Hand: 8S KS 6D 9D 10D 
    Rank: xhigh

    Name: b
    Hand: 4H AC 6D 9D 10D 
    Rank: xhigh

    Name: h
    Hand: 4S AS 6D 9D 10D 
    Rank: xhigh

    Name: f
    Hand: 6H 7S 6D 9D 10D 
    Rank: pair

    Name: d
    Hand: 6S QH 6D 9D 10D 
    Rank: pair

    Name: c
    Hand: 9H 4D 6D 9D 10D 
    Rank: pair

    Name: a
    Hand: 10H 5C 6D 9D 10D 
    Rank: pair

    Name: e
    Hand: QD 3D 6D 9D 10D 
    Rank: flush

    BOARD (turn): 10D 9D 6D 3S 
    BOARD (river): 10D 9D 6D 3S AH 
    Would you like to end the game? (yes/no): 
    no

    PLAYERS
    Player: a
    3H 8D 

    Player: b
    5C QS 

    Player: c
    AD 8S 

    Player: d
    7S 2H 

    Player: e
    9H JD 

    Player: f
    10C JH 

    Player: g
    10S 3S 

    Player: h
    2S 2D 

    BOARD (flop): 5H 6D AS 

    RANKINGS
    Name: d
    Hand: 7S 2H AS 6D 5H 
    Rank: xhigh

    Name: a
    Hand: 3H 8D AS 6D 5H 
    Rank: xhigh

    Name: g
    Hand: 10S 3S AS 6D 5H 
    Rank: xhigh

    Name: e
    Hand: 9H JD AS 6D 5H 
    Rank: xhigh

    Name: f
    Hand: 10C JH AS 6D 5H 
    Rank: xhigh

    Name: h
    Hand: 2S 2D AS 6D 5H 
    Rank: pair

    Name: b
    Hand: 5C QS AS 6D 5H 
    Rank: pair

    Name: c
    Hand: AD 8S AS 6D 5H 
    Rank: pair

    BOARD (turn): 5H 6D AS 7C 
    BOARD (river): 5H 6D AS 7C KD 
    Would you like to end the game? (yes/no): 
    yes

    The program ran correctly given the input from the user.

    Example Output 2:
    [e.d.woolbert@linuxlab002 428Lab2]$ ./lab2 HoldEm a b c d e f g h

    PLAYERS
    Player: a
    2D KC 

    Player: b
    3D 3S 

    Player: c
    5D 4C 

    Player: d
    6D 7H 

    Player: e
    KD JS 

    Player: f
    9H AS 

    Player: g
    JD 8S 

    Player: h
    2C JH 

    BOARD (flop): 3C 2S AD 

    RANKINGS
    Name: d
    Hand: 6D 7H AD 2S 3C 
    Rank: xhigh

    Name: g
    Hand: JD 8S AD 2S 3C 
    Rank: xhigh

    Name: e
    Hand: KD JS AD 2S 3C 
    Rank: xhigh

    Name: h
    Hand: 2C JH AD 2S 3C 
    Rank: pair

    Name: a
    Hand: 2D KC AD 2S 3C 
    Rank: pair

    Name: f
    Hand: 9H AS AD 2S 3C 
    Rank: pair

    Name: b
    Hand: 3D 3S AD 2S 3C 
    Rank: threeofakind

    Name: c
    Hand: 5D 4C AD 2S 3C 
    Rank: straight

    BOARD (turn): 3C 2S AD 5S 
    BOARD (river): 3C 2S AD 5S 5C 
    Would you like to end the game? (yes/no): 
    yes

    The program ran correctly given the input from the user.



    Testing inpropper input (All inpropper inputs correctly failed to run and output the correct usage message):
        [e.d.woolbert@linuxlab002 428-lab2]$ ./lab2 Pinochle
        Usage: ./lab2 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)
        
        [e.d.woolbert@linuxlab002 428-lab2]$ ./lab2 Pino chle
        Usage: ./lab2 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)
        
        [e.d.woolbert@linuxlab002 428-lab2]$ ./lab2 HoldEm
        Usage: ./lab2 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)
        
        [e.d.woolbert@linuxlab002 428-lab2]$ ./lab2 Hold Em
        Usage: ./lab2 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)
        
        [e.d.woolbert@linuxlab002 428-lab2]$ ./lab2 HoldEm p1
        Usage: ./lab2 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)
        
        [e.d.woolbert@linuxlab002 428-lab2]$ ./lab2 HoldEm p1 p2 p3 p4 p5 p6 p7 p8 p9 p10
        Usage: ./lab2 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)
        
        [e.d.woolbert@linuxlab002 428-lab2]$ ./lab2 Pinochle p1 p2 p3 p4 p5
        Usage: ./lab2 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)

        [k.monish@linuxlab004 428Lab2]$ ./lab2 Pinochle A B C
        Usage: ./lab2 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)

        [k.monish@linuxlab004 428Lab2]$ ./lab2 HoldEm A B C D E F G H I J K L M N O P
        Usage: ./lab2 <gametype> (Pinochle / HoldEm) <player name> for Pinochle Player CT (4) / HoldEm Player CT (2-9)



    Result of echo $? for both programs:
    [e.d.woolbert@linuxlab002 428Lab2]$ ./lab2 Pinochle a b c d

    (Removed program output for conciseness)

    [e.d.woolbert@linuxlab002 428Lab2]$ echo $?
    0



    [e.d.woolbert@linuxlab002 428Lab2]$ ./lab2 HoldEm a b c d e f g h

    (Removed program output for conciseness)

    [e.d.woolbert@linuxlab002 428Lab2]$ echo $?
    0