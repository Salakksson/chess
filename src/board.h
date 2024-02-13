#ifndef BOARD
#define BOARD

#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "macros.h"

typedef struct
{
    char pieces[64];
    uint32_t move: 1,
         castle_wk: 1,
         castle_wq: 1,
         castle_bk: 1,
         castle_bq: 1,
         enpassant: 6,
         halfmove: 6,
         fullmove: 16;

    bool promotion;

    bool isMouseHeld;
    uint8_t selectedPiece;
} board_t;


void loadBoard(board_t* board, char* FEN);

board_t createBoard();
    

void drawBoard(board_t* board, int width, int height);


#endif