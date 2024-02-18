#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"
unsigned char* mirror(unsigned char photo[],int line,int col,int choice)
{
	int i,j,k,mid=line/2,s=0;
	unsigned char temp[col][line],temp1;
	if(choice==1)
	{
       for(i=0;i<col;i++)
       {
       	for(j=0;j<line;j++)
       	{
           temp[i][j]=photo[s];
           s++;
		}
	   }
	   for(i=0;i<col;i++)
       {
       	k=line-1;
       	for(j=0;j<mid;j++)
       	{
       	  		temp1=temp[i][j];
       	  		temp[i][j]=temp[i][k];
       	  		//printf("%d %d\n",j,k);
       	  		temp[i][k]=temp1;	
					 --k; 
       	}
       }
        s=0;
       for(i=0;i<col;i++)
       {
       	for(j=0;j<line;j++)
       	{
       		photo[s]=temp[i][j];
       		s++;
       	}
       }
   }
   else
   {
   	for(i=0;i<col;i++)
       {
       	for(j=0;j<line;j++)
       	{
           temp[i][j]=photo[s];
           s++;
		}
	   }
	   //line=640=steiles
	   //col=480=grammes
	   for(i=0;i<line;i++)
       {
       	k=col-1;
       	for(j=0;j<col/2;j++)
       	{
       	  		temp1=temp[j][i];
       	  		temp[j][i]=temp[k][i];
       	  		temp[k][i]=temp1;	
					 --k; 
       	}
       }
        s=0;
       for(i=0;i<col;i++)
       {
       	for(j=0;j<line;j++)
       	{
       		photo[s]=temp[i][j];
       		s++;
       	}
       }
   }
	return photo;
}
