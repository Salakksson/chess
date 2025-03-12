#include "bot.h"
#include "logic.h"

move_t mkmv(int start, int end, float eval)
{
    move_t move;
    move.start = start;
    move.end = end;
    move.eval = eval;
    return move;
}

void bubble_sort(move_t arr[], int n) {
    int i, j;
    move_t temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].eval > arr[j + 1].eval) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


// Asserts that the move is valid
board_t performMove(board_t* prevBoard, int start, int end)
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

    board.move = !board.move;
    return board;

}

float pawnValue(int x, int y)
{
    float value = 1.0f;
    value *= pow(2.0f, ((float)y)/2.0f) * 0.7f;
    value *= (1.1f - (pow(((float)x)-3.5f, 2.0f))/32.0f);
    //printf("%f\n", value);
    return value;
}

float squareValue(board_t* board, int x, int y)
{
    float value = 0;
    switch(board->pieces[x + 8*y])
    {
        case 'r':
            value -= 5.0f;
            break;
        case 'b':
            value -= 3.2f;
            break;
        case 'n':
            value -= 3.0f;
            break;
        case 'q':
            value -= 9.0f;
            break;
        case 'p':
            value = -pawnValue(x, y);
            //printf("pawn value on %d %d: %f\n", x, y, value);
            break;
        case 'R':
            value += 5.0f;
            break;
        case 'B':
            value += 3.2f;
            break;
        case 'N':
            value += 3.0f;
            break;
        case 'Q':
            value += 9.0f;
            break;
        case 'P':
            value = pawnValue(x, 7-y);
            //printf("pawn value on %d %d: %f\n", x, y, value);
            break;
        default: break;
    
    }

    return value;
}



float evaluateStatic(board_t* board)
{

    float value = 0.0f;

    for (int i = 0; i < 64; i++)
    {
        value += squareValue(board, i % 8, i / 8);
    }

    if (isWhiteInCheck(board)) value--;
    if (isBlackInCheck(board)) value++;

    return value;
}

int evaluateDepth(board_t* board, int depth)
{




}

move_t bestMove(board_t* board)
{
    move_t* moves = malloc(218*sizeof(move_t));
    bool bin;
    int mv = 0;
    int (*isActivePiece)(int) = board->move ? isupper : islower;
    for (int i = 0; i < 64; i++)
    {
        if (isActivePiece(board->pieces[i]))
        {
            printf("poopy\n");
            for (int j = 0; j < 64; j++)
            {
                if (isValidMove(board, i, j, &bin, &bin))
                {
                    board_t newBoard = performMove(board, i, j);
                    moves[mv] = mkmv(i, j, evaluateStatic(&newBoard));
                    mv++;
                }
            }
        }
    }
    printf("%d\n", mv);
    bubble_sort(moves, mv);
    move_t ret = moves[board->move * (mv-1)];
    free(moves);
    return ret;
    
}



