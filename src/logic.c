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
                    printf("piece %c at %d %d\n", getPiece(board, x, y), x, y);
                    return false;

                }
                printf("x=%d, y=%d\n", x, y);

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

    if (y1 == 1) // Double move on first
    {
        if ((y2 < 4) && x1 == x2) return true;
    }
    else if ((y2-y1 == 1) && x1 == x2) return true;     // Regular pawn moves
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
    if (y1 == 6) // Double move on first
    {
        if ((y2 > 3) && x1 == x2) return true;
    }
    else if ((y1-y2 == 1) && x1 == x2) return true;     // Regular pawn moves
    if ((abs(x1-x2) == 1) && (y1 - y2) == 1)            // Captures
    {
        if (board->pieces[end] != ' ' || end == board->enpassant) { *enpassant = end == board->enpassant; return true;}; // Evil syntax abuse
    }

    return false;
}

bool isValidMove(board_t* board, int start, int end, bool* enpassant, bool* castle)
{
    if (start > 63 || end > 63) return false;
    *enpassant = false;
    *castle = false;
    if (board->pieces[start] < 'Z' == 'Z' > board->pieces[end] && board->pieces[end] != ' ') return false; // Prevent taking own pieces
    switch(board->pieces[start])
    {
        case 'r':
            if (board->move) return false;
            return isRookMove(board, start, end);
            break;
        case 'b':
            if (board->move) return false;
            return isBishopMove(board, start, end);
            break;
        case 'n':
            if (board->move) return false;
            return isKnightMove(start, end);
            break;
        case 'q':
            if (board->move) return false;
            return isQueenMove(board, start, end);
            break;
        case 'k':
            if (board->move) return false;
            return isKingMove(board, start, end, castle);
            break;
        case 'p':
            if (board->move) return false;
            return isBlackPawnMove(board, start, end, enpassant);
            break;
        case 'R':
            if (!board->move) return false;
            return isRookMove(board, start, end);
            break;
        case 'B':
            if (!board->move) return false;
            return isBishopMove(board, start, end);
            break;
        case 'N':
            if (!board->move) return false;
            return isKnightMove(start, end);
            break;
        case 'Q':
            if (!board->move) return false;
            return isQueenMove(board, start, end);
            break;
        case 'K':
            if (!board->move) return false;
            return isKingMove(board, start, end, castle);
            break;
        case 'P':
            if (!board->move) return false;
            return isWhitePawnMove(board, start, end, enpassant);
            break;
        default: return false;
    }




}