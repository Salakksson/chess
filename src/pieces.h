#ifndef PIECES
#define PIECES

#include <raylib.h>

#include "board.h"
#include "logic.h"
#include "macros.h"

extern Texture2D txtr;
extern Texture2D txtn;
extern Texture2D txtb;
extern Texture2D txtq;
extern Texture2D txtk;
extern Texture2D txtp;
                 
extern Texture2D txtR;
extern Texture2D txtN;
extern Texture2D txtB;
extern Texture2D txtQ;
extern Texture2D txtK;
extern Texture2D txtP;

#endif

void drawPieces(board_t* board, int width, int height);

void handleMoves(board_t* board, int width, int height);


