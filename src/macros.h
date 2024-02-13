#ifndef MACROS
#define MACROS


#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define INRANGE(X, L, H) (X-L)*(X-H) <= 0 ? 1 : 0

#define DEBUG
   
#define COLOUR_DARK (Color){128, 161, 181, 255}
#define COLOUR_LIGHT (Color){204, 218, 224, 255}
#define COLOUR_BACKGROUND (Color){26, 27, 38, 255}





#endif
