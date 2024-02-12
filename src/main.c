#include <raylib.h>
#include <stdio.h>

#include "board.h"
#include "pieces.h"

int main(int argc, char** argv)
{
    
    InitWindow(1920, 1080, "Chess");

    txtr = LoadTexture("assets/r.png");
    txtn = LoadTexture("assets/n.png");
    txtb = LoadTexture("assets/b.png");
    txtq = LoadTexture("assets/q.png");
    txtk = LoadTexture("assets/k.png");
    txtp = LoadTexture("assets/p.png");
                      
    txtR = LoadTexture("assets/R.png");
    txtN = LoadTexture("assets/N.png");
    txtB = LoadTexture("assets/B.png");
    txtQ = LoadTexture("assets/Q.png");
    txtK = LoadTexture("assets/K.png");
    txtP = LoadTexture("assets/P.png");


    board_t board = createBoard();

    while(!WindowShouldClose())
    {
        BeginDrawing();
        
        if(IsKeyDown(KEY_Q)) CloseWindow();
        
        int width = GetScreenWidth();
        int height = GetScreenHeight();
         
        DrawRectangle(0, 0, width, height, COLOUR_BACKGROUND);
        
        drawBoard(&board, width, height);

        handleMoves(&board, width, height);
        drawPieces(&board, width, height);

        DrawFPS(0, 0);
        EndDrawing();
        
    }

#ifdef DEBUG
    loadBoard(&board, "rn1qkbr1/pp3p1p/2p1b2n/3pp1p1/PPB1P1P1/5N1P/2PP1P2/RNBQK1R1 b Qq b3 0 8");
    for (int i = 0; i < 64; i++)
    {
        if (!(i % 8)) putc('\n', stdout); 
        putc(board.pieces[i], stdout);
    }
    putc('\n', stdout);
    printf("values: %u %u%u%u%u %u %u %u\n", board.move, board.castle_wk, board.castle_wq, board.castle_bk, board.castle_bq, board.enpassant, board.halfmove, board.fullmove);
#endif

    return 0;
}
