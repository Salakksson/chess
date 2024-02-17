#include "logic.h"

int sign(int num)
{
    if (num > 0) 
    {
        return 1;
    } 
    else if (num < 0) 
    {
        return -1;
    } 
    else 
    {
        return 0;
    }
}

bool isRookMove(board_t* board, int start, int end)
{
    int x1 = start % 8;
    int y1 = start / 8;
    int x2 = end % 8;
    int y2 = end / 8;

    if (INRANGE(x2, 0, 7) && INRANGE(y2, 0, 7))
    {
        if (x1 == x2)
        {
            for (int y = MIN(y1, y2) + 1; y < MAX(y1, y2); y++)
            {
                if (getPiece(board, x1, y) != ' ') return false;
            }
            return true;
        }
        else if (y1 == y2)
        {
            for (int x = MIN(x1, x2) + 1; x < MAX(x1, x2); x++)
            {
                if (getPiece(board, x, y1) != ' ') return false;
            }
            return true;
        }
        
    }
    return false;
}

bool isBishopMove(board_t* board, int start, int end)
{
    int x1 = start % 8;
    int y1 = start / 8;
    int x2 = end % 8;
    int y2 = end / 8;

    if (INRANGE(x2, 0, 7) && INRANGE(y2, 0, 7))
    {
        if (abs(x1-x2) == abs(y1-y2))
        {
            int dx = x2-x1; int dy = y2-y1;

            int x = x1+sign(dx);
            int y = y1+sign(dy);
            while (x != x2)
            {
                if (getPiece(board, x, y) != ' ')
                {
                    return false;

                }

                x += sign(dx);
                y += sign(dy);
            }
            return true;
        }
    }
    return false;
}

bool isKnightMove(int start, int end)
{
    int x1 = start % 8;
    int y1 = start / 8;
    int x2 = end % 8;
    int y2 = end / 8;

    if (INRANGE(x2, 0, 7) && INRANGE(y2, 0, 7))
    {
        if (MAX(abs(y1-y2), abs(x1-x2)) == 2 && MIN(abs(y1-y2), abs(x1-x2)) == 1) return true;
    }
    return false;
}

bool isQueenMove(board_t* board, int start, int end)
{
    return (isRookMove(board, start, end) ||isBishopMove(board, start, end));
}

bool isKingMove(board_t* board, int start, int end, bool* castle)
{
    int x1 = start % 8;
    int y1 = start / 8;
    int x2 = end % 8;
    int y2 = end / 8;

    if (INRANGE(x2, 0, 7) && INRANGE(y2, 0, 7))
    {
        if (MAX(abs(x1-x2), abs(y1-y2)) == 1) return true;
        // Check for castling
        if (board->pieces[start] == 'K') {
            // White king-side castling
            if (start == 60 && end == 62 && board->castle_wk) {
                *castle = true;
                return true;
            }
            // White queen-side castling
            if (start == 60 && end == 58 && board->castle_wq) {
                *castle = true;
                return true;
            }
        } else if (board->pieces[start] == 'k') {
            // Black king-side castling
            if (start == 4 && end == 6 && board->castle_bk) {
                *castle = true;
                return true;
            }
            // Black queen-side castling
            if (start == 4 && end == 2 && board->castle_bq) {
                *castle = true;
                return true;
            }
        }
    }
    return false;
}

bool isBlackPawnMove(board_t* board, int start, int end, bool* enpassant)
{
    int x1 = start % 8;
    int y1 = start / 8;
    int x2 = end % 8;
    int y2 = end / 8;

    if (y1 == 1 && x1 == x2 && y2 == 3) // Double move on first
    {
        if (getPiece(board, x1, 2) == ' ' && getPiece(board, x1, 3) == ' ') return true;
    }
    if ((y2-y1 == 1) && x1 == x2 && getPiece(board, x2, y2) == ' ') return true;     // Regular pawn moves
    if ((abs(x1-x2) == 1) && (y2 - y1) == 1)            // Captures
    {
        if (board->pieces[end] != ' ' || end == board->enpassant) { *enpassant = end == board->enpassant; return true;};  // Evil syntax abuse
    }

    return false;
}

bool isWhitePawnMove(board_t* board, int start, int end, bool* enpassant)
{
    int x1 = start % 8;
    int y1 = start / 8;
    int x2 = end % 8;
    int y2 = end / 8;

    *enpassant = end == board->enpassant;
    if (y1 == 6 && x1 == x2 && y2 == 4) // Double move on first
    {
        if (getPiece(board, x1, 5) == ' ' && getPiece(board, x1, 4) == ' ') return true;
    }
    if ((y1-y2 == 1) && x1 == x2 && getPiece(board, x2, y2) == ' ') return true;     // Regular pawn moves
    if ((abs(x1-x2) == 1) && (y1 - y2) == 1)            // Captures
    {
        if (board->pieces[end] != ' ' || end == board->enpassant) { *enpassant = end == board->enpassant; return true;}; // Evil syntax abuse
    }

    return false;
}

bool isPseudolegal(board_t* board, int start, int end)
{
    if (start > 63 || end > 63) return false;
    bool discard;
    if (board->pieces[start] < 'Z' == 'Z' > board->pieces[end] && board->pieces[end] != ' ') return false; // Prevent taking own pieces
    switch(board->pieces[start])
    {
        case 'r':
            return isRookMove(board, start, end);
            break;
        case 'b':
            return isBishopMove(board, start, end);
            break;
        case 'n':
            return isKnightMove(start, end);
            break;
        case 'q':
            return isQueenMove(board, start, end);
            break;
        case 'k':
            return isKingMove(board, start, end, &discard);
            break;
        case 'p':
            return isBlackPawnMove(board, start, end, &discard);
            break;
        case 'R':
            return isRookMove(board, start, end);
            break;
        case 'B':
            return isBishopMove(board, start, end);
            break;
        case 'N':
            return isKnightMove(start, end);
            break;
        case 'Q':
            return isQueenMove(board, start, end);
            break;
        case 'K':
            return isKingMove(board, start, end, &discard);
            break;
        case 'P':
            return isWhitePawnMove(board, start, end, &discard);
            break;
        default: return false;
    }
}

bool isWhiteInCheck(board_t* board)
{
    for (int i = 0; i < 63; i++)
    {
        if (board->pieces[i] == 'K')
        {
            for (int j = 0; j < 63; j++)
            {
                if (isPseudolegal(board, j, i)) return true;
            }
            return false;
        }
    }
    return false;
}

bool isBlackInCheck(board_t* board)
{
    for (int i = 0; i < 63; i++)
    {
        if (board->pieces[i] == 'k')
        {
            for (int j = 0; j < 63; j++)
            {
                if (isPseudolegal(board, j, i)) return true;
            }
            return false;
        }
    }
    return false;
}

bool isValidMove(board_t* board, int start, int end, bool* enpassant, bool* castle)
{
    if (start > 63 || end > 63) return false;
    if (board->pieces[start] < 'Z' == 'Z' > board->pieces[end] && board->pieces[end] != ' ') return false; // Prevent taking own pieces
    board_t nextBoard = *board;
    nextBoard.pieces[end] = nextBoard.pieces[start];
    nextBoard.pieces[start] = ' ';
    *enpassant = false;
    *castle = false;
    switch(board->pieces[start])
    {
        case 'r':
            if (isBlackInCheck(&nextBoard)) return false;

            if (board->move) return false;
            return isRookMove(board, start, end);
            break;
        case 'b':
            if (isBlackInCheck(&nextBoard)) return false;
            
            if (board->move) return false;
            return isBishopMove(board, start, end);
            break;
        case 'n':
            if (isBlackInCheck(&nextBoard)) return false;
            
            if (board->move) return false;
            return isKnightMove(start, end);
            break;
        case 'q':
            if (isBlackInCheck(&nextBoard)) return false;
            
            if (board->move) return false;
            return isQueenMove(board, start, end);
            break;
        case 'k':
            if (isBlackInCheck(&nextBoard)) return false;
            
            if (board->move) return false;
            return isKingMove(board, start, end, castle);
            break;
        case 'p':
            if (isBlackInCheck(&nextBoard)) return false;
            
            if (board->move) return false;
            return isBlackPawnMove(board, start, end, enpassant);
            break;
        case 'R':
            if (isWhiteInCheck(&nextBoard)) return false;
            
            if (!board->move) return false;
            return isRookMove(board, start, end);
            break;
        case 'B':
            if (isWhiteInCheck(&nextBoard)) return false;
            
            if (!board->move) return false;
            return isBishopMove(board, start, end);
            break;
        case 'N':
            if (isWhiteInCheck(&nextBoard)) return false;
            
            if (!board->move) return false;
            return isKnightMove(start, end);
            break;
        case 'Q':
            if (isWhiteInCheck(&nextBoard)) return false;
            
            if (!board->move) return false;
            return isQueenMove(board, start, end);
            break;
        case 'K':
            if (isWhiteInCheck(&nextBoard)) return false;
            
            if (!board->move) return false;
            return isKingMove(board, start, end, castle);
            break;
        case 'P':
            if (isWhiteInCheck(&nextBoard)) return false;
            
            if (!board->move) return false;
            return isWhitePawnMove(board, start, end, enpassant);
            break;
        default: return false;
    }
}