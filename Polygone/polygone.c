#include "SDL/SDL.h"
#include <math.h>
#include "primlib.h"
#define NUM_OF_VERT 5
#define ANG_OF_ROT 	0.001
#define MAX_ANG		2*M_PI
#define RADIUS		150
#define ANGLE		2*M_PI/NUM_OF_VERT
#define X	screenWidth()/2 		// X center of rotpoly
#define Y	screenHeight()/2+30		// Y center of rotpoly

void draw_rotpoly(float rad,float temp_ang);
int main()
{
	float temp_angle=0;
	float rad=RADIUS;
	float temporary =0.1;
	initGraph();
	while(pollkey()==(-1))
	{
		/*rad=rad+temporary;
		if(rad>200)
			temporary =-0.1;
		else if(rad<100)
			temporary=0.1;*/
		temp_angle+=MAX_ANG*ANG_OF_ROT;
		if(temp_angle>=MAX_ANG)
			temp_angle=temp_angle-MAX_ANG;
			
			draw_rotpoly(rad,temp_angle);	
			
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
	textout(screenWidth()/3,10,"FOR EXIT PRESS ANY KEY",2);
	updateScreen();
}