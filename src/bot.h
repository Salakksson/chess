#ifndef BOT
#define BOT

#include "board.h"
#include "logic.h"
#include <ctype.h>

typedef struct
{
    int start;
    int end;
    
    float eval;

} move_t;

move_t mkmv(int start, int end, float eval);

void bubble_sort(move_t arr[], int n);

board_t performMove(board_t* board, int start, int end);


float squareValue(board_t* board, int x, int y);


float evaluateStatic(board_t* board);

int evaluateDepth(board_t* board, int depth);

move_t bestMove(board_t* board);



#endif