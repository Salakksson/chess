#ifndef LOGIC
#define LOGIC

#include <stdbool.h>

#include "board.h"

int sign(int num);

bool isRookMove(board_t* board, int start, int end);

bool isBishopMove(board_t* board, int start, int end);

bool isKnightMove(int start, int end);

bool isQueenMove(board_t* board, int start, int end);

bool isKingMove(board_t* board, int start, int end, bool* castle);

bool isBlackPawnMove(board_t* board, int start, int end, bool* enpassant);

bool isWhitePawnMove(board_t* board, int start, int end, bool* enpassant);

bool isValidMove(board_t* board, int start, int end, bool* enpassant, bool* castle);

bool isWhiteInCheck(board_t* board);

bool isBlackInCheck(board_t* board);






#endif
