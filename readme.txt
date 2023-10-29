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
