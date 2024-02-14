#include "menu.h"



void drawAndHandlePromotion(board_t* board, int width, int height)
{

    int min = MIN(width, height);

    DrawRectangleRounded(
        (Rectangle){width/2 - min/3, height/2 - min/6, 2*min/3, min/3},
        0.2, 12, COLOUR_BACKGROUND);

    switch(board->move)
    {
        case false:
            DrawTexture(txtQ, width/2 - min/4,      height/2, WHITE);
            DrawTexture(txtR, width/2 - min/8,      height/2, WHITE);
            DrawTexture(txtB, width/2,              height/2, WHITE);
            DrawTexture(txtN, width/2 + min/8,      height/2, WHITE);
            break;
        case true:
            DrawTexture(txtq, width/2 - min/4,      height/2, WHITE);
            DrawTexture(txtr, width/2 - min/8,      height/2, WHITE);
            DrawTexture(txtb, width/2,              height/2, WHITE);
            DrawTexture(txtn, width/2 + min/8,      height/2, WHITE);
            break;
    }
    #define PROMOTIONTEXT "Choose a promotion piece"
    float fontsize = 90 * (float)min / 2048;
    DrawText(PROMOTIONTEXT, width/2 - MeasureText(PROMOTIONTEXT, fontsize)/2, height/2 - min/8, fontsize, WHITE);

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {

        int mouseX = GetMouseX();
        int mouseY = GetMouseY();

        bool inRangeX = INRANGE(mouseX, width/2 - min/2, width/2 + min/2);
        bool inRangeY = INRANGE(mouseY, height/2 - min/2, height/2 + min/2);

        int squareX;
        int squareY;

        if (inRangeX && inRangeY)
        {
            squareX = (mouseX + min/2 - width/2) * 8 / min;
            squareY = (mouseY + min/2 - height/2) * 8 / min;
        }
        else return;

        if (squareY == 4 && INRANGE(squareX, 2, 5))
        {
            switch (squareX - 2 + 4 * board->move) // Yes, here i do arithmetic with a boolean ):
            {
                // white = false because shit got switched in the previous call of handleMoves(), idk why that function name is plural thinking about it
                case 0:
                    board->pieces[board->selectedPiece] = 'Q';
                    break;
                case 1:
                    board->pieces[board->selectedPiece] = 'R';
                    break;
                case 2:
                    board->pieces[board->selectedPiece] = 'B';
                    break;
                case 3:
                    board->pieces[board->selectedPiece] = 'N';
                    break;

                case 4:
                    board->pieces[board->selectedPiece] = 'q';
                    break;
                case 5:
                    board->pieces[board->selectedPiece] = 'r';
                    break;
                case 6:
                    board->pieces[board->selectedPiece] = 'b';
                    break;
                case 7:
                    board->pieces[board->selectedPiece] = 'n';
                    break;
            }
            board->selectedPiece = -1;
            board->promotion = false;
        }
    }
}


