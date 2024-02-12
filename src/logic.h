#ifndef LOGIC
#define LOGIC

#include <stdbool.h>

#include "board.h"



bool isRookMove(int start, int end);

bool isBishopMove(int start, int end);

bool isKnightMove(int start, int end);

bool isQueenMove(int start, int end);

bool isKingMove(int start, int end);

bool isBlackPawnMove(board_t* board, int start, int end, bool* enpassant);

bool isWhitePawnMove(board_t* board, int start, int end, bool* enpassant);

bool isValidMove(board_t* board, int start, int end, bool* enpassant, bool* castle);







#endif