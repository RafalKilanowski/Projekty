#include "SDL/SDL.h"
#include <math.h>
#include "primlib.h"
#define NUM_OF_VERT 5
#define PI 			3.1415
#define ANG_OF_ROT 	0.00001
#define MAX_ANG		360
#define RADIUS		150
#define ANGLE		2*PI/NUM_OF_VERT
#define X	screenWidth()/2 		// X center of rotpoly
#define Y	screenHeight()/2		// Y center of rotpoly

void draw_rotpoly(float rad,float temp_ang);
int main()
{
	float temp_angle=0;
	float rad=RADIUS;
	float temporary =0.05;
	initGraph();
	while(pollkey()==(-1))
	{
		rad=rad+temporary;
		if(rad>200)
			temporary =-0.05;
		if(rad<130)
			temporary=0.05;
		temp_angle+=MAX_ANG*ANG_OF_ROT;
		if(temp_angle>360)
			temp_angle=temp_angle-360;
		textout(screenWidth()/2.8,10,"FOR EXIT PRESS ANY KEY",2);
		draw_rotpoly(rad,temp_angle);
		SDL_Delay(0.4);
	}
	return 0;
}

void draw_rotpoly(float rad,float temp_ang)
{
	int i = 0;
	filledRect(1,1,screenWidth()-1,screenHeight()-1,0);
	for(i=0;i<NUM_OF_VERT;i++)
	{
	
	line(X+rad*cos(i*ANGLE+temp_ang),Y+rad*sin(i*ANGLE+temp_ang),X+rad*cos((i+1)*ANGLE+temp_ang),Y+rad*sin((i+1)*ANGLE+temp_ang),2);
	}
	updateScreen();
}