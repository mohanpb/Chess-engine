#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"chessmove.h"




int pawn_validate(int x,int y,int turn,Board cb,int *enpas,int* enpasmove)
{
	int i1,i2,j1,j2;
	i1=x%8;
	i2=y%8;
	j1=x/8;
	j2=y/8;
	if( i1==i2 )
	{
		if(((j1==j2+1 && turn==W) || (j2==j1+1 && turn==B)) && cb.place[y]==EMPTY) 
			return 1;
		else 
		{
			if((( j1==j2+2 && turn==W && j1==6) || ( j2==j1+2 && turn==B && j1==1)) && cb.place[y]==EMPTY )
			{
				if(cb.place[(j1+j2)*4+i1]==EMPTY)
				{
					*enpas=(j1+j2)*4+i1;
					return 1;
				}
				else
					return 0;
			}
			else
				return 0;
		}
	}
	else
	{
		if(cb.place[y]!=EMPTY || cb.enpas==y)
		{
			if( (turn==W && (i1==i2+1 || i1==i2-1) && j1==j2+1) || (turn==B && (i1==i2+1 || i1==i2-1) && j2==j1+1) )
			{	
				if(cb.enpas==y)*enpasmove=1;
				return 1;
			}
			else return 0;
		}
		else return 0;
	}
}

int rook_validate(int x,int y,Board cb)
{
	int i1,i2,j1,j2;
	i1=x%8;
	i2=y%8;
	j1=x/8;
	j2=y/8;
	int p=1;
	if( i1==i2 || j2==j1 )
	{
		int i=i1;int j=j1;
		int k=90;
		int initial=1;
		while(k!=y)
		{
			if(initial)
			{	
				if(i1==i2) j=j1>j2 ? j-1 : j+1;
				else i=i1>i2 ? i-1 : i+1;
				initial=0;
			}
			k=8*j+i;if(k==y) break;
			if(cb.place[k]!=EMPTY)
			{
				p=0;
				break;
			}
			if(i1==i2) j=j1>j2 ? j-1 : j+1;
			else i=i1>i2 ? i-1 : i+1;
		}
		if(p) return 1;
		else return 0;
	}
	else
		return 0;
}
	
int knight_validate(int x,int y)
{
	int i1,i2,j1,j2;
	i1=x%8;
	i2=y%8;
	j1=x/8;
	j2=y/8;
	if((( i1-i2==2 || i2-i1==2 ) && ( j1-j2==1 || j2-j1==1 )) || ( ( i1-i2==1 || i2-i1==1 ) && ( j1-j2==2 || j2-j1==2 ) ) )
		return 1;
	else
		return 0;
}

int bishop_validate(int x,int y,Board cb)
{
	int i1,i2,j1,j2;
	i1=x%8;
	i2=y%8;
	j1=x/8;
	j2=y/8;
	int p=1;
	int k=90;
	int initial=1;
	if( i1-i2==j1-j2 ||  i1-i2==j2-j1 )
	{
		int i=i1;int j=j1;
		while(k!=y)
		{
			if(initial)
			{
				if(i1>i2 && j1>j2) {i--;j--;}
				if(i1<i2 && j1>j2) {i++;j--;}
				if(i1>i2 && j1<j2) {i--;j++;}
				if(i1<i2 && j1<j2) {i++;j++;}
				initial=0;
			}
			k=8*j+i;if(k==y) break;
			if(cb.place[k]!=EMPTY)
			{
				p=0;
				break;
			}
			if(i1>i2 && j1>j2) {i--;j--;}
			if(i1<i2 && j1>j2) {i++;j--;}
			if(i1>i2 && j1<j2) {i--;j++;}
			if(i1<i2 && j1<j2) {i++;j++;}
		}
		if(p) return 1;
		else return 0;
	}
	else 
		return 0;
}

int queen_validate(int x,int y,Board cb)
{
	int i1,i2,j1,j2;
	i1=x%8;
	i2=y%8;
	j1=x/8;
	j2=y/8;
	int p=1;
	int k=90;
	int initial=1;
	if( i1-i2==j1-j2 ||  i1-i2==j2-j1 )
	{
		int i=i1;int j=j1;
		while(k!=y)
		{
			if(initial)
			{
				if(i1>i2 && j1>j2) {i--;j--;}
				if(i1<i2 && j1>j2) {i++;j--;}
				if(i1>i2 && j1<j2) {i--;j++;}
				if(i1<i2 && j1<j2) {i++;j++;}
				initial=0;
			}
			k=8*j+i;if(k==y) break;
			if(cb.place[k]!=EMPTY)
			{
				p=0;
				break;
			}
			if(i1>i2 && j1>j2) {i--;j--;}
			if(i1<i2 && j1>j2) {i++;j--;}
			if(i1>i2 && j1<j2) {i--;j++;}
			if(i1<i2 && j1<j2) {i++;j++;}
		}
		if(p) return 1;
		else return 0;
	}
	else 
	{
		if( i1==i2 || j2==j1 )
		{
			int i=i1;int j=j1;
			while(k!=y)
			{
				if(initial)
				{	
					if(i1==i2) j=j1>j2 ? j-1 : j+1;
					else i=i1>i2 ? i-1 : i+1;
					initial=0;
				}
				k=8*j+i;if(k==y) break;
				if(cb.place[k]!=EMPTY)
				{
					p=0;
					break;
				}
				if(i1==i2) j=j1>j2 ? j-1 : j+1;
				else i=i1>i2 ? i-1 : i+1;
			}
			if(p) return 1;
			else return 0;
		}
		else
			return 0;
	}
}

int king_validate(int x,int y)
{
	int i1,i2,j1,j2;
	i1=x%8;
	i2=y%8;
	j1=x/8;
	j2=y/8;
	if( (i1==i2 || i1-i2==1 || i2-i1==1 ) && (j1==j2 || j1-j2==1 || j2-j1==1 ) )
		return 1;
	else		
		return 0;
}

Board init_board()
{
	Board chessb;
	int i;
	for(i=16;i<48;i++)
		chessb.place[i]=EMPTY;
	for(i=8;i<16;i++)
		chessb.place[i]=bP;
	for(i=48;i<56;i++)
		chessb.place[i]=wP;
	chessb.place[0]=bR;chessb.place[7]=bR;
	chessb.place[56]=wR;chessb.place[63]=wR;
	chessb.place[1]=bN;chessb.place[6]=bN;
	chessb.place[57]=wN;chessb.place[62]=wN;
	chessb.place[2]=bB;chessb.place[5]=bB;
	chessb.place[58]=wB;chessb.place[61]=wB;
	chessb.place[3]=bQ;chessb.place[4]=bK;
	chessb.place[59]=wQ;chessb.place[60]=wK;	
	
	chessb.bking=E1;
	chessb.wking=E8;
	
	chessb.stillcheck=0;
	chessb.inducedcheck=0;
	chessb.check=0;
	chessb.invalid=0;
	chessb.draw=0;
	chessb.checkmate=0;
	chessb.stalemate=0;
	
	chessb.enpas=-1;
	chessb.enpascount=0;
	chessb.fiftymove=0;
	
	chessb.bkcastle=1;
	chessb.bqcastle=1;
	chessb.wkcastle=1;
	chessb.wqcastle=1;
	
	chessb.move=W;
	
	chessb.icheck=-1;
	chessb.jcheck=-1;
	
	return chessb;
}

void print_board(Board cboard)
{
	int i,j;
	int * board=cboard.place;
	printf("\n     %c %c %c %c %c %c %c %c\n\n",'A','B','C','D','E','F','G','H'); 
	for(i=0;i<8;i++)
	{
		printf("  %d  ",i+1);
		for(j=0;j<8;j++)
		{
			switch(board[8*i+j])
			{
				case EMPTY: printf("%c ",'.');break;
				case wP: printf("%c ",'+');break;
				case wR: printf("%c ",'R');break;
				case wN: printf("%c ",'N');break;
				case wB: printf("%c ",'B');break;
				case wQ: printf("%c ",'Q');break;
				case wK: printf("%c ",'K');break;
				case bP: printf("%c ",'*');break;
				case bR: printf("%c ",'r');break;
				case bN: printf("%c ",'n');break;
				case bB: printf("%c ",'b');break;
				case bQ: printf("%c ",'q');break;
				case bK: printf("%c ",'k');break;
			}
		}
		printf("\n");
	}
}

Board makepawntoother(Board chessb,int y,int turn)
{
	int a;if(turn==B){chessb.place[y]=bQ;return chessb;}
	printf("Choose from the following:\n1.Queen\n2.Rook\n3.Knight\n4.Bishop\n5.Don't change\n");
	scanf("%d",&a);
	if(a==1)chessb.place[y]=turn==W ? wQ : bQ;
	if(a==2)chessb.place[y]=turn==W ? wR : bR;
	if(a==3)chessb.place[y]=turn==W ? wN : bN;
	if(a==4)chessb.place[y]=turn==W ? wB : bB;
	return chessb;
}

void movetoint(char* cmd,int* i1,int *i2,int* j1,int *j2,int * error)
{
	*i1=cmd[0]-'a';
	*i2=cmd[2]-'a';
	*j1=cmd[1]-'1';
	*j2=cmd[3]-'1';
	if(*i1<0 || *i1>7 || *i2<0 || *i2>7 || *j1<0 || *j1>7 || *j2<0 || *j2>7)
	{
		*error=1;
	}
}

int castling(Board chessb,int x,int y,int *wk,int *wq,int* bk,int *bq,int qcastle,int kcastle)
{
	if(chessb.move==W && chessb.check==0)
	{
		if(x==60 && 60==chessb.wking && chessb.wkcastle && y==x+2 && kcastle && chessb.place[61]==EMPTY && chessb.place[62]==EMPTY)
			{*wk=1;return 1;}
		else *wk=0;
		if(x=60 && 60==chessb.wking && chessb.wqcastle && y==x-2 && qcastle && chessb.place[57]==EMPTY && chessb.place[58]==EMPTY && chessb.place[59]==EMPTY)
			{*wq=1;return 1;}
		else *wq=0;
	}
	if(chessb.move==B && chessb.check==0)
	{
		if(x==4 && 4==chessb.bking && chessb.bkcastle && y==x+2 && kcastle && chessb.place[5]==EMPTY && chessb.place[6]==EMPTY)
			{*bk=1;return 1;}
		else *bk=0;
		if(x==4 && 4==chessb.bking && chessb.bqcastle && y==x-2 && qcastle && chessb.place[3]==EMPTY && chessb.place[2]==EMPTY && chessb.place[1]==EMPTY)
			{*bq=1;return 1;}
		else *bq=0;
	}
	return 0;
}
	
Board make_move(Board chessb,int i1,int i2,int j1,int j2,int *error,int temp,int flag)
{
	int x,y,t,p,q,castle,enpasmove;
	enpasmove=0;
	if(chessb.enpas!=-1 && chessb.enpascount==1)
	{
		chessb.enpas=-1;
		chessb.enpascount=0;
	}
	if(chessb.enpas!=-1 && chessb.enpascount==0)
		chessb.enpascount=1;

	int wk=0,wq=0,bk=0,bq=0;
	x=j1*8+i1;
	y=j2*8+i2;
	q=chessb.place[y];
	p=chessb.place[x];
	int g=0,h=0;
	if((p==EMPTY) || (chessb.move==W && p>wK) || (chessb.move==B && p<=wK))
	{
		*error=1;
	}
	else
	{
		if((p>wK && q>wK) || (p<=wK && q<=wK && q>0))
		{
			*error=1;
		}
		else
		{
			switch(p)
			{
				case wP: t=pawn_validate(x,y,W,chessb,&chessb.enpas,&enpasmove);if(t==1 && y<8)g=1;break;
				case wR: t=rook_validate(x,y,chessb);if(x==56)chessb.wqcastle=0;if(x==63)chessb.wkcastle=0;break;
				case wN: t=knight_validate(x,y);break;
				case wB: t=bishop_validate(x,y,chessb);break;
				case wQ: t=queen_validate(x,y,chessb);break;
				case wK: t=king_validate(x,y);if(t==1){chessb.wkcastle=0;chessb.wqcastle=0;chessb.wking=y;}
														else 
														{  castle=castling(chessb,x,y,&wk,&wq,&bk,&bq,chessb.wqcastle,chessb.wkcastle);
														chessb.wkcastle=0;chessb.wqcastle=0;*error=1;}
														break;
				case bP: t=pawn_validate(x,y,B,chessb,&chessb.enpas,&enpasmove);if(t==1 && y>55)h=1;break;
				case bR: t=rook_validate(x,y,chessb);if(x==0)chessb.bqcastle=0;if(x==7)chessb.bkcastle=0;break;
				case bN: t=knight_validate(x,y);break;
				case bB: t=bishop_validate(x,y,chessb);break;
				case bQ: t=queen_validate(x,y,chessb);break;
				case bK: t=king_validate(x,y);if(t==1){chessb.bkcastle=0;chessb.bqcastle=0;chessb.bking=y;}
														else {  castle=castling(chessb,x,y,&wk,&wq,&bk,&bq,chessb.bqcastle,chessb.bkcastle);
														chessb.bkcastle=0;chessb.bqcastle=0;*error=1;}
														break;
			}
			if(t==1)
			{
				if(temp==1)
				{
					chessb.place[y]=p;
					chessb.place[x]=EMPTY;
					if(flag){if(g==1) chessb=makepawntoother(chessb,y,W);
					if(h==1) chessb=makepawntoother(chessb,y,B);}
				}
			}
			else
			{
				*error=1;
			}
			if(castle && wk)
			{
				*error=0;
				chessb.place[62]=wK;
				chessb.place[61]=wR;
				chessb.place[63]=EMPTY;
				chessb.place[60]=EMPTY;
				chessb.wking=62;
			}
			if(castle && wq)
			{
				*error=0;
				chessb.place[58]=wK;
				chessb.place[59]=wR;
				chessb.place[56]=EMPTY;
				chessb.place[60]=EMPTY;
				chessb.wking=58;
			}
			if(castle && bk)
			{
				*error=0;
				chessb.place[6]=bK;
				chessb.place[5]=bR;
				chessb.place[7]=EMPTY;
				chessb.place[4]=EMPTY;
				chessb.bking=6;
			}
			if(castle && wk)
			{
				*error=0;
				chessb.place[2]=bK;
				chessb.place[3]=bR;
				chessb.place[0]=EMPTY;
				chessb.place[4]=EMPTY;
				chessb.bking=2;
			}
			if(enpasmove)
			{
				if(chessb.enpas<32)
					chessb.place[chessb.enpas+8]=EMPTY;
				else
					chessb.place[chessb.enpas-8]=EMPTY;
			}
		}
	}					
	return chessb;
}

int checkforcheck(Board cboard,int i2,int j2)
{
	int check=0,i;
	Board ctemp;
	check=0;
	for(i=0;i<64;i++)
	{
		check=0;
		if(cboard.move==W && cboard.place[i]<bP && cboard.place[i]>EMPTY)
		{
			ctemp=make_move(cboard ,i%8,cboard.bking%8,i/8,cboard.bking/8, &check,0,0);
			if(check==0)return 1;
		}
		else if(cboard.move==B && cboard.place[i]>wK)
		{
			ctemp=make_move(cboard ,i%8,cboard.wking%8,i/8,cboard.wking/8, &check,0,0);
			if(check==0)return 1;
		}
	}
	return  0;
}

int checkforinducedcheck(int i1,int j1,int i2,int j2,Board cboard)
{
	Board ctemp;
	int check=0,i;
	int error=0;
	cboard=make_move(cboard ,i1,i2,j1,j2, &error,1,0);
	if(error==0)
	{
		cboard.move= cboard.move==W ? B : W;
		for(i=0;i<64;i++)
		{
			check=0;
			if(cboard.move==W && cboard.place[i]<bP && cboard.place[i]>EMPTY)
			{
				ctemp=make_move(cboard ,i%8,cboard.bking%8,i/8,cboard.bking/8, &check,0,0);
				if(check==0)return 1;
			}
			else if(cboard.move==B && cboard.place[i]>wK)
			{
				ctemp=make_move(cboard ,i%8,cboard.wking%8,i/8,cboard.wking/8, &check,0,0);
				if(check==0)return 1;
			}
		}
	}
	return  0;
}	
	

int stalemate(Board cboard)
{
	int i,j,oposs=0;
	Board c;
	if(cboard.move==B)
	{
		for(i=0;i<64;i++)
		{
			if( cboard.place[i]>wK )
			{
				for(j=0;j<64;j++)
				{
					oposs=0;
					c=make_move(cboard,i%8,j%8,i/8,j/8,&oposs,0,0);
					if(oposs==0)
					if(oposs==0 && checkforinducedcheck(i%8,i/8,j%8,j/8,cboard)) oposs=1;
					if(oposs==0)
					{
						//printf("move can be made by black = %d %d\n",i,j);
						return 0;
					}
				}
			}
		}
	}
	else
	{
		for(i=0;i<64;i++)
		{
			if( cboard.place[i]<bP && cboard.place[i]>0)
			{
				for(j=0;j<64;j++)
				{
					oposs=0;
					c=make_move(cboard,i%8,j%8,i/8,j/8,&oposs,0,0);
					if(oposs==0)
					if(oposs==0 && checkforinducedcheck(i%8,i/8,j%8,j/8,cboard)) oposs=1;
					if(oposs==0)
					{
						//printf("move can be madeby white = %d %d\n",i,j);
						return 0;
					}
				}
			}
		}
	}
	return 1; /* ///change kiya hai yadd rakhna */
}

int checkmate(Board cboard,int i1,int j1)
{
	Board c;
	int error,i,j,check;
	cboard.move= cboard.move==W ? B : W;
	for(i=0;i<64;i++)
	{
		if(cboard.place[i]<bP && cboard.place[i]>EMPTY)
		{
			for(j=0;j<64;j++)
			{
				error=0;
				c=make_move(cboard,i%8,j%8,i/8,j/8,&error,1,0);
				if(error==0 && checkforinducedcheck(i%8,i/8,j%8,j/8,cboard)) error=1;
				c.move= B ;
				if(error==0)
				{
					check=checkforcheck(c,i1,j1);
					if(check==1)
						continue;
					else
					{
						printf("move can be madeby white = %d %d\n",i,j);
						return 0;
					}
				}
			}
		}
	}
	for(i=0;i<64;i++)
	{
		if(cboard.place[i]>wK)
		{
			for(j=0;j<64;j++)
			{
				error=0;
				c=make_move(cboard,i%8,j%8,i/8,j/8,&error,1,0);
				if(error==0 && checkforinducedcheck(i%8,i/8,j%8,j/8,cboard)) error=1;
				c.move=W;
				if(error==0)
				{
					check=checkforcheck(c,i1,j1);
					if(check==1)
						continue;
					else
					{
						printf("move can be madeby black = %d %d\n",i,j);
						return 0;
					}
				}
			}
		}
	}
	return 1;
}


int possiblemovepoints(Board cboard,int *a,int i,int j)
{
	int error,k,len;
	Board c,cboardforcheck;
	len=0;
	for(k=0;k<64;k++)
	{
		c=cboard;
		error=0;
		if(checkforinducedcheck(i,j,k%8,k/8,c))continue;
		if(c.check==1)
		{
			cboardforcheck=c;
			cboardforcheck=make_move(cboard,i,k%8,j,k/8,&error,1,0);
			cboardforcheck.move=cboard.move==W ? B : W;
			c.check=checkforcheck(cboardforcheck,cboardforcheck.icheck,cboardforcheck.jcheck);
			if(c.check==1)
				continue;
		}
		c=make_move(c,i,k%8,j,k/8,&error,1,0);
		if(error)continue;
		a[len]=k;
		len++;
	}
	return len;
}
