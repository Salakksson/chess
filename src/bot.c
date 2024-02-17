#include "bot.h"


// Asserts that the move is valid
board_t boardAfterMove(board_t* prevBoard, int start, int end)
{
    board_t board = *prevBoard;

    bool enpassant = false;
    bool castle = false;
    if (!isValidMove(&board, start, end, &enpassant, &castle)) return board;
    
    board.enpassant = 0;
    if (board.pieces[start] == 'p')
    {
        if (start - end == -16) board.enpassant = end-8;
        if (enpassant) board.pieces[end-8] = ' ';
    }
    else if (board.pieces[start] == 'P')
    {
        if (start - end == 16) board.enpassant = end+8;
        if (enpassant) board.pieces[end+8] = ' ';
    }

    if (board.pieces[start] == 'k')
    {
        board.castle_bk = false;
        board.castle_bq = false;
    }
    else if (board.pieces[start] == 'K')
    {
        board.castle_wk = false;
        board.castle_wq = false;
    }

    if (board.pieces[start] == 'r' && start == H8) board.castle_bk = false;
    else if (board.pieces[start] == 'r' && start == A8) board.castle_bq = false;
    else if (board.pieces[start] == 'R' && start == H1) board.castle_wk = false;
    else if (board.pieces[start] == 'R' && start == A1) board.castle_wq = false;

    switch(end)
    {
        case A1:
            board.castle_wq = false;
            break;
        case A8:
            board.castle_bq = false;
            break;
        case H1:
            board.castle_wk = false;
            break;
        case H8:
            board.castle_bk = false;
            break;
        default:
            break;
    }

    if (castle)
    {
        switch(end)
        {
            case G1:
                board.pieces[H1] = ' ';
                board.pieces[F1] = 'R';
                board.castle_wk = false;
                board.castle_wq = false;
                break;
            case C1:
                board.pieces[A1] = ' ';
                board.pieces[D1] = 'R';
                board.castle_wk = false;
                board.castle_wq = false;
                break;
            case G8:
                board.pieces[H8] = ' ';
                board.pieces[F8] = 'r';
                board.castle_bk = false;
                board.castle_bq = false;
                break;
            case C8:
                board.pieces[A8] = ' ';
                board.pieces[D8] = 'r';
                board.castle_bk = false;
                board.castle_bq = false;
                break;

        }
    }

    board.pieces[end] = board.pieces[start];
    board.pieces[start] = ' ';

    if ((board.pieces[end] == 'p' && end > 55) || (board.pieces[end] == 'P' && end < 8))
    {
        board.promotion = true;
    }

    return board;

}




int evaluateStatic(board_t* board);

int evaluateDepth(board_t* board, int depth);



