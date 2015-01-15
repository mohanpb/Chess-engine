#include <gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "chessmove.h"


GtkWidget * make_new_frame(int f);

Board cboard;

Board chessboard[1000];
int movesmade;

GtkWidget *window;
GtkWidget *frame;
int icheck,jcheck;
int ilose;
int x1,x2,z1,z2;
int noofbuttonpressed=0;
int x1,x2,z1,z2;
char s[64][5];

GdkPixbuf *create_pixbuf(const gchar * filename)
{
   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);
   if(!pixbuf) {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}

void chess_back_end()
{
	int error=0;
	

	if(checkforinducedcheck(x1,z1,x2,z2,cboard))
	{ 
		cboard.inducedcheck=1;
		error=1;
	}
	else cboard.inducedcheck=0;

	if(cboard.check==1)
	{
		Board cboardforcheck=cboard;
		cboardforcheck=make_move(cboard,x1,x2,z1,z2,&error,1,0);
		cboardforcheck.move=cboardforcheck.move==W ? B : W;
		cboard.check=checkforcheck(cboardforcheck,cboard.icheck,cboard.jcheck);
		if(cboard.check==1)
		{
			error=1;
			cboard.stillcheck=1;
		}
		else
			cboard.stillcheck=0;
	}
	
	if(!error)
	{
		cboard=make_move(cboard,x1,x2,z1,z2,&error,1,1);
		cboard.check=checkforcheck(cboard,x2,z2);
		if(cboard.check)printf("Check\n");
		if(cboard.check)
		{
			cboard.check=1;
			cboard.icheck=x2;
			cboard.jcheck=z2;
			cboard.checkmate=checkmate(cboard,x2,z2);
		}
	}
	
	cboard.move= (error==1) ? ((cboard.move==W) ? B :W ) : cboard.move;
	if(error)cboard.invalid=1;
	else cboard.invalid=0;
	
	if(cboard.move==B)	{printf("Player1:  ");cboard.move=W;}
	else	{ printf("Player2:  ");cboard.move=B;}
	int stm=stalemate(cboard);
	printf("%d\n",cboard.move);
	if(stm==1){cboard.stalemate=1;printf("STALEMATE\n");}
	else cboard.stalemate=0;
	
	
	if(cboard.checkmate==1)ilose=1;
	if(cboard.move==B && cboard.stalemate==0 && cboard.checkmate==0)
	{
		int gofor,l;
		l= NegaMax( cboard, 4, &gofor,-20000,20000);
		int error=0;
		x1=(gofor/100)%8;
		z1=(gofor/100)/8;
		x2=(gofor%100)%8;
		z2=(gofor%100)/8;

		if(cboard.check==1)
		{
			Board cboardforcheck=cboard;
			cboardforcheck=make_move(cboard,x1,x2,z1,z2,&error,1,0);
			cboardforcheck.move=cboardforcheck.move==W ? B : W;
			cboard.check=checkforcheck(cboardforcheck,cboard.icheck,cboard.jcheck);
			if(cboard.check==1)
			{
				error=1;
				cboard.stillcheck=1;
			}
			else
				cboard.stillcheck=0;
		}
	
		if(!error)
		{
			cboard=make_move(cboard,x1,x2,z1,z2,&error,1,1);
			cboard.check=checkforcheck(cboard,x2,z2);
			if(cboard.check)printf("Check\n");
			if(cboard.check)
			{
				cboard.check=1;
				cboard.icheck=x2;
				cboard.jcheck=z2;
				cboard.checkmate=checkmate(cboard,x2,z2);
			}
		}
	
		cboard.move= (error==1) ? ((cboard.move==W) ? B :W ) : cboard.move;
		if(error)cboard.invalid=1;
		else cboard.invalid=0;
	
		if(cboard.move==B)	{printf("Player1:  ");cboard.move=W;}
		else	{ printf("Player2:  ");cboard.move=B;}
		int stm=stalemate(cboard);
		printf("%d\n",cboard.move);
		if(stm==1){cboard.stalemate=1;printf("STALEMATE\n");}
		else cboard.stalemate=0;
	}
}


void new_game( GtkWidget *widget,gpointer   data )
{
	cboard=init_board();
	movesmade=0;
	ilose=0;
	//stillcheck2=0,inducedcheck2=0,check2=0,invalid2=0,draw2=0,checkmate2=0,stalemate2=0,notyourturn2=0; 
	gtk_container_remove(GTK_CONTAINER(window), frame);
	frame=make_new_frame(1);
	gtk_container_add(GTK_CONTAINER(window), frame);
	gtk_widget_show_all(frame);
}
	

void Undo( GtkWidget *widget,gpointer   data )
{
	if(movesmade>1)
	{
		movesmade--;
		cboard=chessboard[movesmade-1];
		gtk_container_remove(GTK_CONTAINER(window), frame);
		frame=make_new_frame(1);
		gtk_container_add(GTK_CONTAINER(window), frame);
		gtk_widget_show_all(frame);
	}
	else
	new_game(widget,data);
}



/* Our usual callback function */
void callback( GtkWidget *widget,gpointer   data )
{
	if(cboard.stalemate==0 && cboard.checkmate==0)
	{
		int place;
		place=atoi((char *)data);
		if(noofbuttonpressed==0)
		{
			x1=place%8;
			z1=place/8;
			noofbuttonpressed=1;
			int a[30];int i,len;
			len=possiblemovepoints(cboard,a,x1,z1);
			for(i=0;i<len;i++)
				printf("%d ",a[i]);
			printf("\n");
		}
		else{x2=place%8;z2=place/8;noofbuttonpressed=0;}
		if(noofbuttonpressed==0){chess_back_end();if(cboard.invalid==0){chessboard[movesmade]=cboard;movesmade++;}print_board(cboard);}
		gtk_container_remove(GTK_CONTAINER(window), frame);
		frame=make_new_frame(1);
		gtk_container_add(GTK_CONTAINER(window), frame);
		gtk_widget_show_all(frame);
	}
}

GtkWidget * make_new_frame(int f)
{
	GtkWidget *label;
	GtkWidget *invalid;
	GtkBorder * b;
	GtkWidget *globalframe;
	GtkWidget *button[8][8];
	GdkColor color;
	GtkWidget *buttonImage;

	int i,j,l;
	int a[30];
	int len;
	if(noofbuttonpressed==1)
		len=possiblemovepoints(cboard,a,x1,z1);
	globalframe = gtk_fixed_new();
	l=0;
	for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)
		{
			button[i][j] = gtk_button_new();
			gtk_widget_set_size_request(button[i][j], 70, 70);
			sprintf(s[i+8*j],"%d",i+8*j);
			if((i+j)%2!=0)
	  		{
				color.red = 26000;
				color.blue = 0;
				color.green = 13056;
				gtk_widget_modify_bg (GTK_WIDGET(button[i][j]), GTK_STATE_NORMAL, &color);
			}
			else
			{
				//gdk_color_parse ("greenyellow", &color);
				color.red = 65535;
				color.blue = 41112;
				color.green = 55568;
				gtk_widget_modify_bg (GTK_WIDGET(button[i][j]), GTK_STATE_NORMAL, &color);
			}
			if(f && noofbuttonpressed==1 && len>l && a[l]==8*j+i)
			{
				color.red = 65000;
				color.blue = 0;
				color.green = 0;
				if(f)gtk_widget_modify_bg (GTK_WIDGET(button[i][j]), GTK_STATE_NORMAL, &color);
				l++;
			}
			if(f && x1==i && z1==j && noofbuttonpressed==1)
			{
				color.red = 0;
				color.blue = 0;
				color.green = 65000;
				gtk_widget_modify_bg (GTK_WIDGET(button[i][j]), GTK_STATE_NORMAL, &color);
			}
			buttonImage = gtk_image_new();
			if(cboard.place[8*j+i]==bP) gtk_image_set_from_file(GTK_IMAGE(buttonImage),"Chess_pawn_black.png");
			if(cboard.place[8*j+i]==bK) gtk_image_set_from_file(GTK_IMAGE(buttonImage),"Chess_king_black.png");
			if(cboard.place[8*j+i]==bR) gtk_image_set_from_file(GTK_IMAGE(buttonImage),"Chess_rook_black.png");
			if(cboard.place[8*j+i]==bB) gtk_image_set_from_file(GTK_IMAGE(buttonImage),"Chess_bishop_black.png");
			if(cboard.place[8*j+i]==bN) gtk_image_set_from_file(GTK_IMAGE(buttonImage),"Chess_knight_black.png");
			if(cboard.place[8*j+i]==wP) gtk_image_set_from_file(GTK_IMAGE(buttonImage),"Chess_pawn_white.png");
			if(cboard.place[8*j+i]==wK) gtk_image_set_from_file(GTK_IMAGE(buttonImage),"Chess_king_white.png");
			if(cboard.place[8*j+i]==wR) gtk_image_set_from_file(GTK_IMAGE(buttonImage),"Chess_rook_white.png");
			if(cboard.place[8*j+i]==wB) gtk_image_set_from_file(GTK_IMAGE(buttonImage),"Chess_bishop_white.png");
			if(cboard.place[8*j+i]==wN) gtk_image_set_from_file(GTK_IMAGE(buttonImage),"Chess_knight_white.png");
			if(cboard.place[8*j+i]==wQ) gtk_image_set_from_file(GTK_IMAGE(buttonImage),"Chess_queen_white.png");
			if(cboard.place[8*j+i]==bQ) gtk_image_set_from_file(GTK_IMAGE(buttonImage),"Chess_queen_black.png");
			
			gtk_button_set_image((GtkButton *)button[i][j], buttonImage);
			gtk_fixed_put(GTK_FIXED(globalframe), button[i][j], 70*i+30, 70*j+90);
			if(f)gtk_signal_connect (GTK_OBJECT (button[i][j]), "clicked",GTK_SIGNAL_FUNC (callback), (gpointer) s[i+8*j]);
		}
	}
	
	GtkWidget* image_viewer;
	image_viewer = gtk_image_new_from_file("c17186.jpg");
	gtk_fixed_put(GTK_FIXED(globalframe), image_viewer, 200,10);
	
	GtkWidget *undo=gtk_button_new();
	gtk_widget_set_size_request(undo, 80, 35);
	color.red = 0;
	color.blue = 65535;
	color.green = 0;
	gtk_widget_modify_bg (GTK_WIDGET(undo), GTK_STATE_NORMAL, &color);
	color.red = 65;
	color.blue = 0;
	color.green = 65000;
	GtkWidget * label3;
	label3=gtk_label_new("Undo");
	//label1=gtk_button_get_label(GTK_BUTTON(undo));
	gtk_widget_modify_fg (GTK_WIDGET(label3), GTK_STATE_NORMAL, &color);
	gtk_container_add (GTK_CONTAINER (undo), label3);
	gtk_fixed_put(GTK_FIXED(globalframe), undo, 900,550);
	gtk_signal_connect (GTK_OBJECT (undo), "clicked",GTK_SIGNAL_FUNC (Undo), NULL);
	
	GtkWidget *newgame=gtk_button_new();
	gtk_widget_set_size_request(newgame, 100, 35);
	color.red = 0;
	color.blue = 65535;
	color.green = 0;
	gtk_widget_modify_bg (GTK_WIDGET(newgame), GTK_STATE_NORMAL, &color);
	color.red = 65;
	color.blue = 0;
	color.green = 65000;
	GtkWidget * label4;
	label4=gtk_label_new("New game");
	gtk_widget_modify_fg (GTK_WIDGET(label4), GTK_STATE_NORMAL, &color);
	gtk_container_add (GTK_CONTAINER (newgame), label4);
	gtk_fixed_put(GTK_FIXED(globalframe), newgame, 650,550);
	gtk_signal_connect (GTK_OBJECT (newgame), "clicked",GTK_SIGNAL_FUNC (new_game), NULL);
	
	GtkWidget *quit=gtk_button_new();
	gtk_widget_set_size_request(quit, 80, 35);
	color.red = 0;
	color.blue = 65530;
	color.green = 0;
	gtk_widget_modify_bg (GTK_WIDGET(quit), GTK_STATE_NORMAL, &color);
	color.red = 65;
	color.blue = 0;
	color.green = 65000;
	GtkWidget * label5;
	label5=gtk_label_new("Quit");
	gtk_widget_modify_fg (GTK_WIDGET(label5), GTK_STATE_NORMAL, &color);
	gtk_container_add (GTK_CONTAINER (quit), label5);
	gtk_fixed_put(GTK_FIXED(globalframe), quit, 780,550);
	gtk_signal_connect (GTK_OBJECT (quit), "clicked",GTK_SIGNAL_FUNC (gtk_main_quit), NULL);
	
	if(cboard.invalid){invalid = gtk_label_new("INVALID");
	gtk_label_set_markup(GTK_LABEL(invalid), "<span font=\"25\" background=\"yellow\" foreground=\"red\" ><b>INVALID""</b></span>");
	gtk_fixed_put(GTK_FIXED(globalframe), invalid, 650, 350); 
	}
	
	if(cboard.checkmate)
	{
		if(ilose==1)
		{
			GtkWidget *ilose;
			gtk_label_set_markup(GTK_LABEL(ilose), "<span font=\"25\" background=\"yellow\" foreground=\"red\" ><b>You Win""</b></span>");
			gtk_fixed_put(GTK_FIXED(globalframe), invalid, 650, 50); 
		}
		else
		{
			GtkWidget *ilose;
			gtk_label_set_markup(GTK_LABEL(ilose), "<span font=\"25\" background=\"yellow\" foreground=\"red\" ><b>You Win""</b></span>");
			gtk_fixed_put(GTK_FIXED(globalframe), invalid, 650, 50); 
		}
	}
	
	if(cboard.check && cboard.checkmate==0){
	
		GtkWidget *check;
		check = gtk_label_new("CHECK");
		gtk_label_set_markup(GTK_LABEL(check), "<span font=\"25\" background=\"yellow\" foreground=\"red\" ><b>Check""</b></span>");
		gtk_fixed_put(GTK_FIXED(globalframe), check, 650, 270); 
	}

	GtkWidget *stillcheck;
	if(cboard.stillcheck){stillcheck = gtk_label_new("In Check so ");
	gtk_widget_modify_fg (GTK_WIDGET(stillcheck), GTK_STATE_NORMAL, &color);
	gtk_fixed_put(GTK_FIXED(globalframe), stillcheck, 620, 330); 
	}

	GtkWidget *turn;
	turn = gtk_label_new("Your Turn");
	gtk_label_set_markup(GTK_LABEL(turn), "<span font=\"25\" background=\"black\" foreground=\"white\" ><b>Your Turn""</b></span>");
	gtk_fixed_put(GTK_FIXED(globalframe), turn, 630, 150);

	GtkWidget *checkmate;
	if(cboard.checkmate){checkmate = gtk_label_new("CHECKMATE");
	gtk_label_set_markup(GTK_LABEL(checkmate), "<span font=\"25\" background=\"black\" foreground=\"white\" ><b>CHECKMATE""</b></span>");
	gtk_fixed_put(GTK_FIXED(globalframe), checkmate, 650, 250); 
	}

	GtkWidget *stalemate;
	if(cboard.stalemate && !cboard.checkmate){stalemate = gtk_label_new("STALEMATE");
	gtk_label_set_markup(GTK_LABEL(stalemate), "<span font=\"25\" background=\"black\" foreground=\"white\" ><b>STALEMATE""</b></span>");
	gtk_fixed_put(GTK_FIXED(globalframe), stalemate, 650, 250); 
	}
	
	GtkWidget *draw;
	if(cboard.draw){draw = gtk_label_new("DRAW");
	color.red = 65535;
	color.blue = 0;
	color.green = 0;
	gtk_widget_modify_fg (GTK_WIDGET(draw), GTK_STATE_NORMAL, &color);
	gtk_fixed_put(GTK_FIXED(globalframe), draw, 650, 270); 
	}
	return globalframe;	
}
	
	

int main(int argc, char** argv) {
	GdkColor color;
	gtk_init(&argc, &argv);
	cboard=init_board();
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 1350, 800);
	gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("images.jpg"));
	gtk_window_set_title(GTK_WINDOW(window), "chess game");
	frame=make_new_frame(1);
	gtk_container_add(GTK_CONTAINER(window), frame);
	//gdk_color_parse ("lightblue", &color);
	//gtk_widget_modify_bg (GTK_WIDGET(window), GTK_STATE_NORMAL, &color);
	gtk_widget_show_all(window);
	g_signal_connect(window, "destroy",G_CALLBACK (gtk_main_quit), NULL);
	gtk_main();
	return 0;
}
