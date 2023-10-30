#pragma once

// Argv index of the program name
const int CMD_PROG_IDX = 0;

// Argv index of the game name
const int CMD_GAME_IDX = 1;

// Argv index of input player names
const int CMD_START_IDX = 2;

/*
    Hand size of each player for Pinochle and
    Hold'em games respectively.
*/
const int PINOCHLE_DEAL_SIZE = 3;
const int HOLD_EM_HAND_SIZE = 2;
const int HOLD_EM_TOTAL_HAND_SIZE = 5;

// Number of players that can play Pinochle
const int PINOCHLE_PLAYER_CT = 4;

// Count of cards required for the "Major" Pinochle Melds
const int PINOCHLE_MAJOR_CT = 2;

// Count of cards required for the "Minor" Pinochle Melds
const int PINOCHLE_MINOR_CT = 1;

/*
    Minimum and maximum number of players that can
    play Hold'em at any given time.
*/
const int MIN_HOLD_EM_PLAYER_CT = 2;
const int MAX_HOLD_EM_PLAYER_CT = 9;

// Size of flop for Hold'em
const int HOLD_EM_FLOP_SIZE = 3;

/*
    Strings that the player should input
    if they want to play Pinochle or Hold'em
*/
inline const char *HOLD_EM_NAME_STR = "HoldEm";
inline const char *PINOCHLE_NAME_STR = "Pinochle";

/*
    Definition of enum for unique return values for
    the program.
*/
enum ReturnValues
{
    SUCCESS,
    IMPROPER_GAME_INPUT,
    GAME_MAKE_FAILURE,
    GAME_PLAY_FAILURE
};