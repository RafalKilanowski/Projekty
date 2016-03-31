#include <stdio.h>
#include "primlib.h"
#include "SDL/SDL.h"
#include <time.h>
#include <unistd.h>

#define PEGS 			10
#define DISCS 			10
#define FLOOR			20 	/* WIDTH OF FLOOR */

#if PEGS > 8
#define DISCHEIGHT		3
#define DISCWIDTH		6
#define DIFF 			1
#define PEGWIDTH 		4
#define SPACE 			2
#elif PEGS > 6
#define DISCHEIGHT		5
#define DISCWIDTH		10
#define DIFF 			2
#define PEGWIDTH 		8
#define SPACE 			3
#elif PEGS > 4
#define DISCHEIGHT		8
#define DISCWIDTH		12
#define DIFF 			3
#define PEGWIDTH 		10
#define SPACE 			3
#else
#define DISCHEIGHT		11
#define DISCWIDTH		18
#define DIFF 			4
#define PEGWIDTH 		15
#define SPACE 			4
#endif

#define FDISC			screenHeight()-FLOOR-SPACE
#define CHARTOINT		49

#if (PEGS<1 || DISCS <1 || DISCS>10 || PEGS>10)
	#error "The wrong number of pegs and discs"
#endif

void 	init_game(int game[PEGS][DISCS],int * position);
int 	play (int game[PEGS][DISCS],int * position);
int		check (int game[PEGS][DISCS],int * position,int button,int button1);
void 	move(int game[PEGS][DISCS],int * position,int button,int button1);

int main()
{
	initGraph();
	int game[PEGS][DISCS];
	int position[PEGS];
	init_game(game,position);
	if(play(game,position))
		textout(screenWidth()/3,100,"CONGRATULATIONS!",WHITE);
	else
		textout(screenWidth()/3,100,"BYE,BYE,TRY AGAIN LATER!!",WHITE);
	updateScreen();
	SDL_Delay(2000);
	return 0;
}

void init_game(int game[PEGS][DISCS], int position[PEGS])
{
	int iterator1,iterator2;
	float x_start,x_end,y_start,y_end;
	filledRect(0,screenHeight(),screenWidth(),screenHeight()-FLOOR,GREEN);

	for(iterator1=0 ;iterator1<PEGS;iterator1++)
	{
		filledRect((screenWidth()/(PEGS+1))*(iterator1+1)-PEGWIDTH,screenHeight()-FLOOR,(screenWidth()/(PEGS+1))*(iterator1+1),screenHeight()-FLOOR-DISCS*(SPACE+DISCHEIGHT)-3*SPACE,RED);
	}
	for(iterator1=0;iterator1<PEGS;iterator1++)
	{
		for(iterator2=0;iterator2<DISCS;iterator2++)
		{
			if(iterator1 == 0)
			{
				game[iterator1][iterator2]=iterator2+1;
			}
			else
				game[iterator1][iterator2]=0;
		}
	}
	for(iterator1=0;iterator1<PEGS;iterator1++)
	{
		if(iterator1 == 0)
			position[iterator1] = 0;
		else
			position[iterator1] = DISCS-1;
	}
	for(iterator1=DISCS-1;iterator1>=0;iterator1--)
	{
		x_start = (screenWidth()/(PEGS+1))-PEGWIDTH-DISCWIDTH/2-iterator1*DIFF;
		y_start	= FDISC - (SPACE+DISCHEIGHT)*(DISCS-(iterator1+1));
		x_end 	= (screenWidth()/(PEGS+1))+DISCWIDTH/2+iterator1*DIFF;
		y_end 	= FDISC - (SPACE+DISCHEIGHT)*(DISCS-(iterator1))+SPACE;
		filledRect(x_start,y_start,x_end,y_end,MAGENTA);
	}
	updateScreen();
}

int play (int game[PEGS][DISCS],int position[PEGS])
{
	int boolean = 1;
	int button,button1;
	while(boolean)
	{
		if(position[PEGS-1] == 0 && game[PEGS-1][position[PEGS-1]] == 1)
			return 1;
		button=getkey();
		if(button == SDLK_ESCAPE)
		{
			boolean=0;
			continue;
		}
		button1=getkey();
		if(button1 == SDLK_ESCAPE)
		{
			boolean =0;
			continue;
		}
		if(check(game,position,button-CHARTOINT,button1-CHARTOINT))
			move(game,position,button-CHARTOINT,button1-CHARTOINT);		
	}
	return 0;
	
}

int		check (int game[PEGS][DISCS],int * position,int button,int button1)
{
	if (button >=0 && button < PEGS && button1 >=0 && button1 <PEGS)
	{
		if(position[button] <= DISCS-1 && position[button] >= 0)
		{
	
			if(((game[button][position[button]] < game[button1][position[button1]]) && game[button][position[button]]>0) || (((game[button][position[button]])>0) && (game[button1][position[button1]]) == 0))
				return 1;
			else
				return 0;
		}
	}
	return 0;
}

void 	move(int game[PEGS][DISCS],int * position,int button,int button1)
{
	float start_height 	= FDISC - (SPACE+DISCHEIGHT)*(DISCS-position[button]-1);
	float start_width 	= (screenWidth()/(PEGS+1))*(button+1)-PEGWIDTH-DISCWIDTH/2-(game[button][position[button]]-1)*DIFF;
	float end_width	= (screenWidth()/(PEGS+1))*(button+1)+DISCWIDTH/2+(game[button][position[button]]-1)*DIFF;
	float end_height 	= FDISC - (SPACE+DISCHEIGHT)*(DISCS-(position[button]))+SPACE;
	int temp,temp_position;
	temp=game[button][position[button]];
	temp_position = position[button];

	if(position[button] < DISCS-1)
	{

		game[button][position[button]] = 0;
		position[button]++;
	}
	else
	{
		game[button][position[button]] = 0;
	}
	if((position[button1] == DISCS-1) && (game[button1][position[button1]] == 0))
	{
		game[button1][position[button1]]=temp;	
	}
	else 
	{
		game[button1][position[button1]-1]=temp;
		position[button1]--;
	}
	float height_dest1 = FDISC - DISCS*(SPACE+DISCHEIGHT)-30;

	while(start_height != height_dest1)
	{
		filledRect(start_width-1,start_height+1,end_width+1,end_height,BLACK);
		filledRect((screenWidth()/(PEGS+1))*(button+1)-PEGWIDTH,FDISC - (SPACE+DISCHEIGHT)*(DISCS-temp_position-1)+2,(screenWidth()/(PEGS+1))*(button+1),screenHeight()-FLOOR-DISCS*(SPACE+DISCHEIGHT)-3*SPACE,RED);
		start_height-=1;
		end_height-=1;
		filledRect(start_width,start_height,end_width,end_height,MAGENTA);
		updateScreen();
		SDL_Delay(2);
	}
	float width_dest = (screenWidth()/(PEGS+1))*(button1+1)-PEGWIDTH-DISCWIDTH/2-(game[button1][position[button1]]-1)*DIFF;
	
	if(button<button1)
		while(start_width!=width_dest)
		{
			filledRect(start_width,start_height,end_width,end_height,BLACK);
			start_width+=1;
			end_width+=1;
			filledRect(start_width,start_height,end_width,end_height,MAGENTA);
			updateScreen();
			SDL_Delay(2);
		}
	else
		while(start_width!=width_dest)
		{
		filledRect(start_width,start_height,end_width,end_height,BLACK);

		start_width-=1;
		end_width-=1;
		filledRect(start_width,start_height,end_width,end_height,MAGENTA);
		updateScreen();
		SDL_Delay(2);
		}
	
	float height_dest2 = FDISC - (SPACE+DISCHEIGHT)*(DISCS-position[button1]-1);
	while(start_height<=height_dest2)
	{
		filledRect(start_width,start_height,end_width,end_height,BLACK);
		filledRect((screenWidth()/(PEGS+1))*(button1+1)-PEGWIDTH,FDISC - (SPACE+DISCHEIGHT)*(DISCS-position[button1]-1),(screenWidth()/(PEGS+1))*(button1+1),screenHeight()-FLOOR-DISCS*(SPACE+DISCHEIGHT)-3*SPACE,RED);
		start_height+=1;
		end_height+=1;
		filledRect(start_width,start_height,end_width,end_height,MAGENTA);
		updateScreen();
		SDL_Delay(2);
	}
	}