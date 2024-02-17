#ifndef BOT
#define BOT

#include "board.h"

board_t boardAfterMove(board_t* board, int start, int end);

int evaluateStatic(board_t* board);

int evaluateDepth(board_t* board, int depth);





#endif