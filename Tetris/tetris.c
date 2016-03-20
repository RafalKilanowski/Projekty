#include <stdio.h>
#include <string.h>
#include "pieces.h"
#include <time.h>
#include <unistd.h>
#include "SDL/SDL.h"
#include "primlib.h"

#define 	WIDTH 	 		10 /* INITIAL WIDTH */
#define 	HEIGHT			20 /* INITIAL HEIGHT */	
#define 	BUCKET_WIDTH	3 /* WIDTH OF BUCKET FRAME */
#define 	BLOCK_SIZE		20*20/HEIGHT /* THE SIZE OF EVERY BRICK ELEMENT */
#define 	SPACE 			1
static int factor = 1;
const int x_p = 100;
const int y_p = 50;

void 	update_game(int game1[HEIGHT][WIDTH][3],char next_piece[4][4],int color);
int 	check_if_poss(int game1[HEIGHT][WIDTH][3],int x, int y, char piece1[4][4], char move);
void 	draw(int game1[HEIGHT][WIDTH][3],int x, int y,char piece1[4][4],int color);
int 	play(int game1[HEIGHT][WIDTH][3],int x, int y,char piece2[4][4][4], int color,int random_piece_temp);
void	delete_rows(int game1[HEIGHT][WIDTH][3]);
void 	check_if_poss_rotation(int game1[HEIGHT][WIDTH][3],int *x,int *y,char piece1[4][4],char piece[4][4][4],int * random_piece_temp,int color);

static int points =0;
int main()
{
	/* SEED */
	srand(time(NULL));
	int iterator1, iterator2;
	int game[HEIGHT][WIDTH][3];
	for(iterator1=0;iterator1<HEIGHT;iterator1++)
	{
		for(iterator2=0;iterator2<WIDTH;iterator2++)
		{
			game[iterator1][iterator2][0]=x_p+iterator2*BLOCK_SIZE;
			game[iterator1][iterator2][1]=y_p+iterator1*BLOCK_SIZE;
			game[iterator1][iterator2][2]=0;
		}
	}
	int random_piece,random_piece2,random_color,random_next_piece,random_next_piece2,random_next_color;
	
	random_piece=rand()%7;
	random_piece2=rand()%4;
	random_color=rand()%5+1;

	int play_bool = 1;
	
	initGraph();
	while(play_bool)
	{	
		random_next_piece=rand()%7;
		random_next_piece2=rand()%4;
		random_next_color=rand()%6+1;
		update_game(game,pieces[random_next_piece][random_next_piece2],random_next_color);
		usleep(100000);
		if(check_if_poss(game,0,WIDTH/2-1,pieces[random_piece][random_piece2],'d'))
		{
			draw(game,0,WIDTH/2-1,pieces[random_piece][random_piece2],random_color);	
		}
		else
			play_bool=0;
		if(play(game,0,WIDTH/2-1,pieces[random_piece],random_color,random_piece2) == 0)
		{
			play_bool = 0;
		}
		delete_rows(game);
		random_piece=random_next_piece;
		random_piece2=random_next_piece2;
		random_color=random_next_color;
	}
	
	return 0;
}


void 	update_game(int game1[HEIGHT][WIDTH][3],char next_piece[4][4],int color)
{
	int iterator,iterator1;
	filledRect(0,0,screenWidth(),screenHeight(),0);
	textout(0,10,"To rotate the piece press space. To quit press 'q'.",RED);

	filledRect(x_p-5, y_p, x_p-1, y_p+(HEIGHT*BLOCK_SIZE)+4, WHITE);
	filledRect(x_p, y_p+(HEIGHT*BLOCK_SIZE), x_p+(WIDTH*BLOCK_SIZE)-1, y_p+(HEIGHT*BLOCK_SIZE)+4,WHITE);
	filledRect(x_p+(WIDTH*BLOCK_SIZE), y_p, x_p+(WIDTH*BLOCK_SIZE)+4, y_p+(HEIGHT*BLOCK_SIZE)+4, WHITE);
	for(iterator=0;iterator<HEIGHT;iterator++)
	{
		for(iterator1=0;iterator1<WIDTH;iterator1++)
		{
			filledRect(game1[iterator][iterator1][0]+SPACE,game1[iterator][iterator1][1]+SPACE,game1[iterator][iterator1][0]+BLOCK_SIZE-2*SPACE,game1[iterator][iterator1][1]+BLOCK_SIZE-2*SPACE,game1[iterator][iterator1][2]);
		}
	}
	
	textout( x_p+(WIDTH*(BLOCK_SIZE+1)), y_p,"next piece: ",WHITE);
	for(iterator=0;iterator<4;iterator++)
	{
		for(iterator1=0;iterator1<4;iterator1++)
		{
			if ((int) next_piece[iterator][iterator1]!=0)
				filledRect(game1[iterator][iterator1][0]+((WIDTH+1)*BLOCK_SIZE),game1[iterator][iterator1][1]+BLOCK_SIZE,game1[iterator][iterator1][0]+((WIDTH+2)*BLOCK_SIZE-2),game1[iterator][iterator1][1]+2*BLOCK_SIZE-2,color);
		}
	}
	char buffer[20];
	sprintf(buffer,"Points = %d",points);
	textout( x_p+(WIDTH*(BLOCK_SIZE+1)), y_p+game1[4][4][1],buffer,WHITE);
	
	updateScreen();
}





void draw(int game1[HEIGHT][WIDTH][3],int x, int y,char piece1[4][4],int color)
{
	int iterator,iterator1;
	for(iterator=0;iterator<4;iterator++)
	{
		for(iterator1=0;iterator1<4;iterator1++)
		{
			if((int)piece1[iterator][iterator1] !=0)
			{
				if((int)piece1[iterator][iterator1] !=2)
					filledRect(game1[x+iterator][y+iterator1][0]+SPACE,game1[x+iterator][y+iterator1][1]+SPACE,game1[x+iterator][y+iterator1][0]+BLOCK_SIZE-2*SPACE,game1[x+iterator][y+iterator1][1]+BLOCK_SIZE-2*SPACE,color);	
				else if(color == 0)
					filledRect(game1[x+iterator][y+iterator1][0]+SPACE,game1[x+iterator][y+iterator1][1]+SPACE,game1[x+iterator][y+iterator1][0]+BLOCK_SIZE-2*SPACE,game1[x+iterator][y+iterator1][1]+BLOCK_SIZE-2*SPACE,color);	
				else
					filledRect(game1[x+iterator][y+iterator1][0]+SPACE,game1[x+iterator][y+iterator1][1]+SPACE,game1[x+iterator][y+iterator1][0]+BLOCK_SIZE-2*SPACE,game1[x+iterator][y+iterator1][1]+BLOCK_SIZE-2*SPACE,1+color%6);
			}
		}
	}
	updateScreen();
}

int 	check_if_poss(int game1[HEIGHT][WIDTH][3],int x, int y, char piece1[4][4], char move)
{
	int iterator,iterator1;
	switch(move)
	{
		case 'd' : 	x++;
					break;
		case 'r' : 	y++;
					break;
		case 'l' :	y--;
					break;
		case 't' : 	break;
	}
	if(y<0 || y>=WIDTH || x>=HEIGHT || x<0)
		return 0;
	for(iterator=0;iterator<4;iterator++)
	{
		for(iterator1=0;iterator1<4;iterator1++)
		{
			if((int)piece1[iterator][iterator1] != 0 && ((y+iterator1)>=WIDTH || (x+iterator)>=HEIGHT))
				return 0;
			if((int)piece1[iterator][iterator1] != 0 && game1[x+iterator][y+iterator1][2] != 0)
				return 0;
		}
	}
	return 1;
}


int 	play(int game1[HEIGHT][WIDTH][3],int x, int y,char piece2[4][4][4], int color,int random_piece_temp)
{
	char  piece1[4][4];
	memcpy(&piece1,&piece2[random_piece_temp%4],sizeof piece1);
	int bool_play = 1;
	int iterator,iterator1;
	while(bool_play)
	{
		for(iterator=0;iterator<10;iterator++)
		{
			if(isKeyDown(SDLK_q) ==1)
				return 0;
			else
			{
				
				switch(pollkey())
				{	
					case SDLK_RIGHT :
					{
						if(check_if_poss(game1,x,y,piece1,'r'))
						{
							draw(game1,x,y,piece1,0);
							y++;
							draw(game1,x,y,piece1,color);
							updateScreen();
						}
						break;
					}

					case SDLK_LEFT :
					{
						if(check_if_poss(game1,x,y,piece1,'l'))
						{
							draw(game1,x,y,piece1,0);
							y--;
							draw(game1,x,y,piece1,color);
							updateScreen();
						}
						break;
					}
					case SDLK_DOWN :
					{
						while(check_if_poss(game1,x,y,piece1,'d'))
						{
							draw(game1,x,y,piece1,0);
							x++;
							draw(game1,x,y,piece1,color);
							updateScreen();
						}
						break;
					}

					case SDLK_SPACE :
					{
						check_if_poss_rotation(game1,&x,&y,piece1,piece2,&random_piece_temp,color);
						break;
					}

				}
				
			}
		usleep(35000);
		}

	if(check_if_poss(game1,x,y,piece1,'d'))
	{
		draw(game1,x,y,piece1,0);
		x++;
		draw(game1,x,y,piece1,color);
		updateScreen();
	}
	else
		bool_play=0;
	}
	for(iterator=0;iterator<4;iterator++)
	{
		for(iterator1=0;iterator1<4;iterator1++)
		{
			if((int) piece1[iterator][iterator1]!=0)
			game1[x+iterator][y+iterator1][2]=color;
		}
	}
	
	return 1;
}

void	delete_rows(int game1[HEIGHT][WIDTH][3])
{
	int iterator1,iterator2,iterator3,counter,boolean1;
	counter = 0;
	boolean1 = 1;
	for(iterator1=HEIGHT-1;iterator1>=0;iterator1--)
	{
		for(iterator2=0;iterator2<WIDTH;iterator2++)
		{
			if(game1[iterator1][iterator2][2] == 0)
				boolean1 = 0;
		}
		if(boolean1 != 0)
		{
			for(iterator2=0;iterator2<WIDTH;iterator2++)
			{
				game1[iterator1][iterator2][2] = 0;
			}
			for(iterator3=iterator1;iterator3>0;iterator3--)
			{
				for(iterator2=0;iterator2<WIDTH;iterator2++)
					game1[iterator3][iterator2][2]=game1[iterator3-1][iterator2][2];
			}
			iterator1++;
			counter++;
		}
		boolean1=1;
	}
	points = points+counter*counter*10;
}

void 	check_if_poss_rotation(int game1[HEIGHT][WIDTH][3],int *x,int *y,char piece1[4][4],char piece2[4][4][4],int * random_piece_temp,int color)
{
	int x_temporary = 0;
	int y_temporary = 0;
	int x_temporary_new = 0;
	int y_temporary_new = 0;
	int iterator1,iterator2;

	for(iterator1=0;iterator1<4;iterator1++)
	{
		for(iterator2=0;iterator2<4;iterator2++)
		{
			if(piece2[*random_piece_temp][iterator1][iterator2] == 2)
			{
				x_temporary = iterator1;
				y_temporary = iterator2;
			}
			if(piece2[((*random_piece_temp)+1)%4][iterator1][iterator2] == 2)
			{
				x_temporary_new = iterator1;
				y_temporary_new = iterator2;
			}
		}
	}
		int x_difference = x_temporary-x_temporary_new;
		int y_difference = y_temporary-y_temporary_new;
		
		if(check_if_poss(game1,(*x)+x_difference,(*y)+y_difference,piece2[(*random_piece_temp+factor)%4],'t'))
		{
			draw(game1,*x,*y,piece1,0);
			int i,j;
			for(i=0;i<4;i++)
			{
				for(j=0;j<4;j++)
				{
					piece1[i][j] = piece2[((*random_piece_temp)+factor)%4][i][j];
				}
			}
			*x=(*x)+x_difference;
			*y=(*y)+y_difference;
			
			draw(game1,*x,*y,piece1,color);	
			(*random_piece_temp)=((*random_piece_temp)+factor)%4;	
		}
	updateScreen();
}


