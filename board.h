#ifndef CHESS_H
#define CHESS_H

enum { EMPTY, wP, wR, wN, wB, wQ, wK, bP, bR, bN, bB, bQ, bK  };

enum {
  A1=0, B1, C1, D1, E1, F1, G1, H1,
  A2, B2, C2, D2, E2, F2, G2, H2,
  A3, B3, C3, D3, E3, F3, G3, H3,
  A4, B4, C4, D4, E4, F4, G4, H4,
  A5, B5, C5, D5, E5, F5, G5, H5,
  A6, B6, C6, D6, E6, F6, G6, H6,
  A7, B7, C7, D7, E7, F7, G7, H7,
  A8, B8, C8, D8, E8, F8, G8, H8
};

enum{ W, B};

typedef struct board
{
	int move;
	
	int place[64];
	
	int bking;
	int wking;
	
	int stillcheck;
	int inducedcheck;
	int check;
	int invalid;
	int draw;
	int checkmate;
	int stalemate;
		
	int enpas; //cell at which en pasant is occured value lies between 24 to 39 else default value is -1
	int enpascount;
	
	int fiftymove; //move count
	int piececount;
	
	int bkcastle; //castling 1 for possible
	int bqcastle;
	int wkcastle;
	int wqcastle;
	
	int icheck;
	int jcheck;

}Board;

int checkforinducedcheck(int i1,int j1,int i2,int j2,Board cboard);
int pawn_validate(int x,int y,int turn,Board cb,int *enpas,int*enpasmove);
int rook_validate(int x,int y,Board cb);
int knight_validate(int x,int y);
int bishop_validate(int x,int y,Board cb);
int queen_validate(int x,int y,Board cb);
int king_validate(int x,int y);
Board init_board();
void print_board(Board cboard);
void movetoint(char* cmd,int* i1,int *i2,int* j1,int *j2,int * error);
Board makepawntoother(Board chessb,int y,int turn);
int checkforcheck(Board cboard,int i2,int j2);
int stalemate(Board cboard);
int castling(Board chessb,int x,int y,int *wk,int *wq,int* bk,int *bq,int qcastle,int kcastle);
Board make_move(Board chessb,int i1,int i2,int j1,int j2,int *error,int temp,int flag);
int checkmate(Board cboard,int i1,int j1);
int possiblemovepoints(Board cboard,int *a,int i,int j);
int NegaMax(Board b, int depth, int* gofor,int alpha,int beta);
int evaluate(Board chessb);
#endif
