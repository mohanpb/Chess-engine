#include<stdio.h>
#include "chessmove.h"



int PawnTable[64] =
{
  0,  0,  0,  0,  0,  0,  0,  0,
 50, 50, 50, 50, 50, 50, 50, 50,
 10, 10, 20, 30, 30, 20, 10, 10,
  5,  5, 10, 27, 27, 10,  5,  5,
  0,  0,  0, 25, 25,  0,  0,  0,
  5, -5,-10,  0,  0,-10, -5,  5,
  5, 10, 10,-25,-25, 10, 10,  5,
  0,  0,  0,  0,  0,  0,  0,  0
};

int PawnTableInitial[64] =
{
  0,  0,  0,  0,  0,  0,  0,  0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 30, 20, 20, 0, 0, 0, 0,
  10,  20, 10, 40, 10, 0, 0 , 0 ,
  0,  0,  0, 5, 15,  0,  0,  0,
  5, 5, 0,  0,  0,0, 5, 5,
  0, 0, 0,5,5, 0, 0,  5,
  0,  0,  0,  0,  0,  0,  0,  0
};

int BishopTableInitial[64] =
{
  0,  0,  0,  0,  0,  0,  0,  0,
 0, 0, 0, 50, 0, 0, 50, 0,
 10, 10, 20, 30, 30, 20, 10, 10,
  5,  5, 10, 27, 27, 10,  5,  5,
  20,  0,  0, 0, 0,  0,  0,  20,
  0, 5,10,  0,  0,0, 5,  5,
  5, 10, 10,15,15, 10, 10,  5,
  0,  0,  0,  0,  0,  0,  0,  0
};

int KnightTableInitial[64] =
{
  0,  0,  0,  0,  0,  0,  0,  0,
 0, 0, 0, 50, 50, 0, 0, 0,
 10, 10, 60, 30, 30, 60, 10, 10,
  5,  5, 10, 27, 27, 10,  5,  5,
  0,  20,  0, 25, 25,  0,  20,  0,
  5, 5,0,  0,  0,0, 5,  5,
  5, 10, 10,25,25, 10, 10,  5,
  0,  0,  0,  0,  0,  0,  0,  0
};



int RookTable[64] = 
{
 -50,-50,-30,-30,-30,-30,-50,-50,
 -40,-20,  0,  0,  0,  0,-20,-40,
 -30,  0, 10, 15, 15, 10,  0,-30,
 -30,  5, 15, 20, 20, 15,  5,-30,
 -30,  0, 15, 20, 20, 15,  0,-30,
 -30,  5, 10, 15, 15, 10,  5,-30,
 -40,-20,  0,  5,  5,  0,-20,-40,
 -50,-40,-20,-30,-30,-20,-40,-50
};

int QueenTable[64] = 
{
 -50,-40,-30,-10,-10,-30,-40,-50,
 -40,-15,  10,  5,  5,  0,-15,-20,
 -30,  0, 10, 15, 15, 10,  0,-30,
 -10,  5, 20, 40, 40, 20,  5,-10,
 -10,  0, 20, 40, 40, 20,  0,-10,
 -30,  5, 10, 15, 15, 10,  5,-30,
 -40,-20,  10,  5,  5,  0,-20,-40,
 -50,-40,-20,-10,-10,-20,-40,-50
};


int KnightTable[64] = 
{
 -50,-40,-30,-30,-30,-30,-40,-50,
 -40,-20,  0,  0,  0,  0,-20,-40,
 -30,  0, 10, 15, 15, 10,  0,-30,
 -30,  5, 15, 20, 20, 15,  5,-30,
 -30,  0, 15, 20, 20, 15,  0,-30,
 -30,  5, 10, 15, 15, 10,  5,-30,
 -40,-20,  0,  5,  5,  0,-20,-40,
 -50,-40,-20,-30,-30,-20,-40,-50
};

int BishopTable[64] =
{
 -20,-10,-10,-10,-10,-10,-10,-20,
 -10,  0,  0,  0,  0,  0,  0,-10,
 -10,  0,  5, 10, 10,  5,  0,-10,
 -10,  5,  5, 10, 10,  5,  5,-10,
 -10,  0, 10, 10, 10, 10,  0,-10,
 -10, 10, 10, 10, 10, 10, 10,-10,
 -10,  5,  0,  0,  0,  0,  5,-10,
 -20,-10,-40,-10,-10,-40,-10,-20
};

int KingTable[64] = 
{
  -30, -40, -40, -50, -50, -40, -40, -30,
  -30, -40, -40, -50, -50, -40, -40, -30,
  -30, -40, -40, -50, -50, -40, -40, -30,
  -30, -40, -40, -50, -50, -40, -40, -30,
  -20, -30, -30, -40, -40, -30, -30, -20,
  -10, -20, -20, -20, -20, -20, -20, -10, 
   20,  20,   0,   0,   0,   0,  20,  20,
   20,  30,  10,   0,   0,  10,  30,  20
};

int KingTableEndGame[64] =
{
 -50,-40,-30,-20,-20,-30,-40,-50,
 -30,-20,-10,  0,  0,-10,-20,-30,
 -30,-10, 20, 30, 30, 20,-10,-30,
 -30,-10, 30, 40, 40, 30,-10,-30,
 -30,-10, 30, 40, 40, 30,-10,-30,
 -30,-10, 20, 30, 30, 20,-10,-30,
 -30,-30,  0,  0,  0,  0,-30,-30,
 -50,-30,-30,-30,-30,-30,-30,-50
};

int attackdefend(Board b,int p)
{
	int i;
	int error;
	int count=0;
	for(i=0;i<64;i++)
	{
		if(b.place[i]>EMPTY && b.place[i]<bP)
		{
			Board c=b;
			error=0;
			c=make_move(c,i%8,p%8,i/8,p/8,&error,1,0);
			if(!error)
				count--;
		}
		else if(b.place[i]>wK)
		{
			Board c=b;
			error=0;
			c.move=W;
			c=make_move(c,i%8,p%8,i/8,p/8,&error,1,0);
			if(!error)
				count++;
		}
	}
	return count;
}

int evaluate(Board chessb)
{
	int i;
	int score=0;
	int count=0;
	for(i=0;i<64;i++)
	{
		switch(chessb.place[i])
		{
			case bP : score+=100;count++;score+=PawnTable[63-i];
							break;
			case bR : score+=500;count++;score+=RookTable[63-i];//score+=50*attackdefend(chessb,i);
							break;
			case bB : score+=325;count++;score+=BishopTable[63-i];//score+=30*attackdefend(chessb,i);
							break;
			case bN : score+=320;count++;score+=KnightTable[63-i];//score+=30*attackdefend(chessb,i);
							break;
			case bQ : score+=975;count++;score+=QueenTable[63-i];//score+=90*attackdefend(chessb,i);
							break;
			case bK : /*score+=10000;count++;*/score+=KingTable[63-i];
							break;
			case wP : score-=100;count++;//score+=PawnTable[i];
							break;
			case wR : score-=500;count++;//score+=RookTable[i];
							break;
			case wB : score-=325;count++;//score+=BishopTable[i];
							break;
			case wN : score-=320;count++;//score+=KnightTable[i];
							break;
			case wQ : score-=975;count++;//score+=QueenTable[i];
							break;
			/*case wK : score-=10000;count++;//score+=KingTable[i];
							break;*/
		}
	}if(count>27)
	{
	score=0;
	for(i=0;i<64;i++)
	{
		switch(chessb.place[i])
		{
			case bP : score+=100;score+=PawnTableInitial[i];
							break;
			case bR : score+=500;//score+=RookTable[63-i];
							break;
			case bB : score+=325;score+=BishopTableInitial[i];
							break;
			case bN : score+=320;score+=KnightTableInitial[i];
							break;
			case bQ : score+=975;//score+=QueenTable[63-i];
							break;
			//case bK : score+=10000;//score+=KingTable[63-i];
			case wP : score-=100;//score+=PawnTable[i];
							break;
			case wR : score-=500;//score+=RookTable[i];
							break;
			case wB : score-=325;//score+=BishopTable[i];
							break;
			case wN : score-=320;//score+=KnightTable[i];
							break;
			case wQ : score-=975;//score+=QueenTable[i];
							break;
			//case wK : score-=10000;//score+=KingTable[i];
		}
	}
	}
	return score;
}


int NegaMax(Board b, int depth, int* gofor,int alpha,int beta) {
	/*if (GameOver(b) or depth>MaxDepth)
		return sign[color]*Analysis(b)
	int max = -infinity
	for each legal move m in board b {
		copy b to c
		make move m in board c
		int x= - NegaMax(c, depth+1, 1-color)  //Note the "-" before "NegaMax"
		if (x>max) max = x
	}
	return max
	*/
	if(depth==0)
		return evaluate(b);
	Board b1;
	int len=0,error,gofor2,x,i,j;
	int a[30];
	int max=-10000;
	if(depth!=4)
		b.move= b.move==W ? B : W;
	for(i=0;i<64;i++)
	{
		if(b.move==W && b.place[i]<bP && b.place[i]>EMPTY)
		{
			len=possiblemovepoints(b,a,i%8,i/8);
			for(j=0;j<len;j++)
			{
				b1=b;
				b1=make_move(b1,i%8,a[j]%8,i/8,a[j]/8,&error,1,0);
				x= NegaMax(b1,depth-1,&gofor2,-beta,-alpha) ;
				if(alpha<x)
				{
					alpha=x;
					if(depth ==4)
						*gofor=100*i+a[j];
					else
						*gofor=100*i+a[j];
				}
				if(x>=beta) { //printf("%d %d %d %d %d %d %d\n",depth,i,a[j],*gofor,beta,x,max);
				return x;}
			}
		}
		if(b.move==B && b.place[i]>wK )
		{
			
			len=possiblemovepoints(b,a,i%8,i/8);
			for(j=0;j<len;j++)
			{
				b1=b;
				b1=make_move(b1,i%8,a[j]%8,i/8,a[j]/8,&error,1,0);
				x= NegaMax(b1,depth-1,&gofor2,-beta,-alpha) ;
				if(alpha<x)
				{
					alpha=x;
					if(depth ==4)
						*gofor=100*i+a[j];
					else
						*gofor=100*i+a[j];
				}
				if(x>=beta) { //printf("%d %d %d %d %d %d %d\n",depth,i,a[j],*gofor,beta,x,max);
				return x;}
			}
		}
	}
	return alpha;
}
