#include "board.h"
#include <stdlib.h>

bool isValidMove(board_t* board, int start, int end, bool* enpassant, bool* castle);

char getPiece(board_t* board, int x, int y)
{
    return board->pieces[y * 8 + x];
}

void setPiece(board_t* board, int x, int y, char c)
{
    board->pieces[y * 8 + x] = c;
}

void loadBoard(board_t* board, char* FEN)
{

#ifdef DEBUG
    printf("Loading FEN: %s\n", FEN);
#endif

    int x = 0;
    int y = 0;
    
    for (int i = 0; i < 64; i++)
    {
        board->pieces[i] = ' ';
    }

    char* fen = FEN;
    while (*fen != ' ')
    {
        char current = *fen;
        switch(current)
        {
            case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8':
            {
                int num = atoi(fen);
                x += num;
                fen ++;
                break;
            }
            case '/':
            {
                y++;
                x = 0;
                fen++;
                break;
            }
            case 'p':
            {
                setPiece(board, x, y, 'p');
                x++;
                fen++;
                break;
            }
            default:
            {
                char c = current;
                if (!((c-'r')*(c-'n')*(c-'b')*(c-'q')*(c-'k')*(c-'p')*  // Evil arithmetic trick
                      (c-'R')*(c-'N')*(c-'B')*(c-'Q')*(c-'K')*(c-'P'))) // Its slower but looks nice
                {                                               // and was easier to read than a shit ton of switches
                    setPiece(board, x, y, current);
                    x++;
                    fen++;
                }
                else 
                {
                    printf("Failed to parse FEN, unknown character '%c'\n", c);
                    return;
                }
                break;
            }
        }
    }

    if (x!= 8 || y != 7)
    {
        printf("Failed to parse FEN string: %s\n", FEN);
    }
    
    char move;
    char castle_wk;
    char castle_wq;
    char castle_bk;
    char castle_bq;
    char enpessantcolumn = '-';
    int enpessantrow = 0;
    int halfmove;
    int fullmove;

    // Parsing remaining fields
    sscanf(fen, " %c %c%c%c%c %c%d %d %d", &move, &castle_wk, &castle_wq, &castle_bk, &castle_bq, &enpessantcolumn, &enpessantrow, &halfmove, &fullmove);

    // Assigning parsed values to the board struct
    board->move = (move == 'w') ? 1 : 0;
    board->castle_wk = (castle_wk == '-') ? 0 : 1;
    board->castle_wq = (castle_wq == '-') ? 0 : 1;
    board->castle_bk = (castle_bk == '-') ? 0 : 1;
    board->castle_bq = (castle_bq == '-') ? 0 : 1;
    board->enpassant = (enpessantcolumn == '-') ? 0 : ((enpessantcolumn - 'a') + (enpessantrow - 1) * 8); // Calculate en passant square index
    board->halfmove = halfmove;
    board->fullmove = fullmove;
    return;
}

board_t createBoard()
{
    board_t board;
    
    loadBoard(&board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    
    board.isMouseHeld = false;
    board.selectedPiece = -1;
    board.promotion = false;
    board.flipped = false;

    board.quit = false;

    return board;
}

void drawBoard(board_t* board, int width, int height)
{
    
    int min = MIN(width, height);

    for(int i = 0; i < 64; i++)
    {
        int x = i % 8;
        int y = i / 8;
        if (board->flipped) x = 7-x;
        if (board->flipped) y = 7-y;
        struct Color colour = ((x+y)%2) ? COLOUR_DARK : COLOUR_LIGHT;

        bool discard;
        if (isValidMove(board, board->selectedPiece, i, &discard, &discard)) colour = ((x+y)%2) ? COLOUR_HIGHLIGHT_DARK : COLOUR_HIGHLIGHT_LIGHT;
        int squareSize = min/8;

        //if (i == board->enpassant) colour = COLOUR_BACKGROUND;
        DrawRectangle((width-min)/2 + x * squareSize, (height-min)/2 + y * squareSize, squareSize, squareSize, colour);
    #ifdef NUMBERS
        char number[5];
        snprintf(number, 4, "%d", i);
        DrawText(number, (width-min)/2 + x * squareSize, (height-min)/2 + y * squareSize, 24, BLACK);
    #endif
    }
}




