#include "pieces.h"

Texture2D txtr;
Texture2D txtn;
Texture2D txtb;
Texture2D txtq;
Texture2D txtk;
Texture2D txtp;

Texture2D txtR;
Texture2D txtN;
Texture2D txtB;
Texture2D txtQ;
Texture2D txtK;
Texture2D txtP;

void drawPieces(board_t* board, int width, int height)
{
    
    int min = MIN(width, height);

    for(int i = 0; i < 64; i++)
    {
        int x = i % 8;
        int y = i / 8;
        int squareSize = min/8;

        Texture txt;
        switch(board->pieces[i])
        {
        case 'r': txt=txtr; break;
        case 'n': txt=txtn; break;
        case 'b': txt=txtb; break;
        case 'q': txt=txtq; break;
        case 'k': txt=txtk; break;
        case 'p': txt=txtp; break;
                          
        case 'R': txt=txtR; break;
        case 'N': txt=txtN; break;
        case 'B': txt=txtB; break;
        case 'Q': txt=txtQ; break;
        case 'K': txt=txtK; break;
        case 'P': txt=txtP; break;
        default: break;
        }
        
        if (board->pieces[i] != ' ')
        {
            txt.width = squareSize;
            txt.height = squareSize;
            if (i == board->selectedPiece)
            {
                int mouseX = GetMouseX();
                int mouseY = GetMouseY();
                DrawTexture(txt, mouseX - squareSize/2, mouseY - squareSize/2, WHITE);
            }
            else DrawTexture(txt, (width-min)/2 + x * squareSize, (height-min)/2 + y * squareSize, WHITE);
        }
    }
}

void handleMoves(board_t* board, int width, int height)
{
   if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
   {
        // Picking up piece
        if (!board->isMouseHeld)
        {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();
            int min = MIN(width, height);
            bool inRangeX = INRANGE(mouseX, width/2 - min/2, width/2 + min/2);
            bool inRangeY = INRANGE(mouseY, height/2 - min/2, height/2 + min/2);

            if (inRangeX && inRangeY)
            {
                int squareX = (mouseX + min/2 - width/2) * 8 / min;
                int squareY = (mouseY + min/2 - height/2) * 8 / min;
                int square = squareX + 8 * squareY;
            #ifdef DEBUG
                printf("Picking up from square %d: x: %d y: %d\n", square, squareX, squareY);
            #endif

                board->selectedPiece = square;
            }

            board->isMouseHeld = true;
        }

   }
   else
   {
        // Dropping piece
        if (board->isMouseHeld)
        {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();
            int min = MIN(width, height);
            bool inRangeX = INRANGE(mouseX, width/2 - min/2, width/2 + min/2);
            bool inRangeY = INRANGE(mouseY, height/2 - min/2, height/2 + min/2);

            if (inRangeX && inRangeY)
            {
                int squareX = (mouseX + min/2 - width/2) * 8 / min;
                int squareY = (mouseY + min/2 - height/2) * 8 / min;
                int square = squareX + 8 * squareY;
            #ifdef DEBUG
                printf("Dropping to square %d: x: %d y: %d\n", square, squareX, squareY);
            #endif
                bool enpassant;
                bool castle;
                if(isValidMove(board, board->selectedPiece, square, &enpassant, &castle))
                {
                    board->enpassant = 0;
                    if (board->pieces[board->selectedPiece] == 'p')
                    {
                        if (board->selectedPiece - square == -16) board->enpassant = square-8;
                        if (enpassant) board->pieces[square-8] = ' ';
                    }
                    else if (board->pieces[board->selectedPiece] == 'P')
                    {
                        if (board->selectedPiece - square == 16) board->enpassant = square+8;
                        if (enpassant) board->pieces[square+8] = ' ';
                    }

                    board->pieces[square] = board->pieces[board->selectedPiece];
                    board->pieces[board->selectedPiece] = ' ';

                    if (board->move == false) board->fullmove++;
                    board->move = !board->move;
                #ifdef DEBUG
                    printf("Valid move: %d to %d\n", board->selectedPiece, square);
                #endif
                }
            #ifdef DEBUG
                else printf("Invalid move: %d to %d\n", board->selectedPiece, square);
            #endif
                board->selectedPiece = -1;
                if ((board->pieces[square] == 'p' && squareY == 7) || (board->pieces[square] == 'P' && squareY == 0))
                {
                    printf("tf 2.0\n");
                    
                    drawPieces(&board, width, height);

                    DrawFPS(0, 0);
                    EndDrawing();
                    while(!WindowShouldClose())
                    {
                        BeginDrawing();
                        DrawRectangle(0, 0, width, height, COLOUR_BACKGROUND);
        
                        drawBoard(&board, width, height);
                        drawPieces(&board, width, height);

                        DrawRectangleRounded((Rectangle){width/2 - min/4, height/2 - min/4, min/2, min/2},
                                                0.5f, 20, COLOUR_BACKGROUND);
                        DrawFPS(0, 0);

                        EndDrawing();
                    }
                    BeginDrawing();
                }
            }

            board->isMouseHeld = false;
        }

   }






}