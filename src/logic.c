#include "logic.h"

bool isRookMove(int start, int end)
{
    int x1 = start % 8;
    int y1 = start / 8;
    int x2 = end % 8;
    int y2 = end / 8;

    if (INRANGE(x2, 0, 7) && INRANGE(y2, 0, 7))
    {
        if (x1 == x2 || y1 == y2) return true;
    }
    return false;
}

bool isBishopMove(int start, int end)
{
    int x1 = start % 8;
    int y1 = start / 8;
    int x2 = end % 8;
    int y2 = end / 8;

    if (INRANGE(x2, 0, 7) && INRANGE(y2, 0, 7))
    {
        if (abs(x1-x2) == abs(y1-y2)) return true;
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
        if (abs(x1-x2) + abs(y1-y2) == 3) return true;
    }
    return false;
}

bool isQueenMove(int start, int end)
{
    int x1 = start % 8;
    int y1 = start / 8;
    int x2 = end % 8;
    int y2 = end / 8;

    if (INRANGE(x2, 0, 7) && INRANGE(y2, 0, 7))
    {
        if (x1 == x2 || y1 == y2) return true;
        if (abs(x1-x2) == abs(y1-y2)) return true;
    }
    return false;
}

bool isKingMove(int start, int end)
{
    int x1 = start % 8;
    int y1 = start / 8;
    int x2 = end % 8;
    int y2 = end / 8;

    if (INRANGE(x2, 0, 7) && INRANGE(y2, 0, 7))
    {
        if (MAX(abs(x1-x2), abs(y1-y2)) == 1) return true;
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
    if (board->pieces[start] < 'Z' == 'Z' > board->pieces[end] && board->pieces[end] != ' ') return false; // Prevent taking own pieces
    switch(board->pieces[start])
    {
        case 'r':
            if (board->move) return false;
            return isRookMove(start, end);
            break;
        case 'b':
            if (board->move) return false;
            return isBishopMove(start, end);
            break;
        case 'n':
            if (board->move) return false;
            return isKnightMove(start, end);
            break;
        case 'q':
            if (board->move) return false;
            return isQueenMove(start, end);
            break;
        case 'k':
            if (board->move) return false;
            return isKingMove(start, end);
            break;
        case 'p':
            if (board->move) return false;
            return isBlackPawnMove(board, start, end, enpassant);
            break;
        case 'R':
            if (!board->move) return false;
            return isRookMove(start, end);
            break;
        case 'B':
            if (!board->move) return false;
            return isBishopMove(start, end);
            break;
        case 'N':
            if (!board->move) return false;
            return isKnightMove(start, end);
            break;
        case 'Q':
            if (!board->move) return false;
            return isQueenMove(start, end);
            break;
        case 'K':
            if (!board->move) return false;
            return isKingMove(start, end);
            break;
        case 'P':
            if (!board->move) return false;
            return isWhitePawnMove(board, start, end, enpassant);
            break;
        default: return false;
    }




}