#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned char* noise(unsigned char* photo,int size)
{
	int i,k,pixel,blackorwhite;
	double d,pixels;
	pixels=((double) rand() / ( (double) RAND_MAX));
	pixel=(int)(size*pixels)/10;
	for(i=0;i<=pixel;i++)
	{	
	   d = (double) rand() / ( (double) RAND_MAX);
       d = d * size + 1;
       k = (int) d; 
       d = (double) rand() / ( (double) RAND_MAX);
       d=d*2 ;
       blackorwhite=(int)d;
	   if(blackorwhite==1)
       photo[k]=255;
       else
       photo[k]=0;
	}
	return photo;
}
