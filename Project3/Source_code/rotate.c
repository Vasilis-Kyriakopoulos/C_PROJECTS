#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"
unsigned char* rotate(unsigned char photo[],int col,int line,int choice)
{
	int i,j,mid=(line*col)/2,s=0,c,t;
	unsigned char temp[line][col],temp1;
	unsigned char temp2[col][line];
	double k;
	for(i=0;i<line;i++)
       {
       	for(j=0;j<col;j++)
       	{
       		temp[i][j]=photo[s];
       		s++;
       	}
       }
       
       switch(choice)
       {
       	case 1:
       	case 6:
       		j=0;
       	  for(i=0;i<line;i++)
       	  {
       	  	for(j=0;j<col;j++)
       	  	{
       	  		temp2[j][line-1-i]=temp[i][j];
			}
		  }
		  
       	break;
       	
       	case 2:
       	case 5:
       		c=(int)line/2;
       		k=(double)line/2;
       		for(i=0;i<c;i++)
       	  {
       	  	
       	  	for(j=0;j<col;j++)
       	  	{
       	  	  temp1=temp[i][j];
			  temp[i][j]=temp[line-1-i][col-1-j];
			  temp[line-1-i][col-1-j]=temp1;  
			}
		  }
		 
	        if(k-c!=0.0)
       		{
       			
       			t=col-1;
       	     for(j=0;j<col/2;j++)
       	      {
       	  		temp1=temp[c][j];
       	  		temp[c][j]=temp[c][t];
       	  		temp[c][t]=temp1;	
					 --t; 
       	      }
            }
       	break;
       	
       	case 3:
       	case 4:
       		j=0;
       	  for(i=0;i<line;i++)
       	  {
       	  	for(j=0;j<col;j++)
       	  	{
       	  		temp2[col-1-j][i]=temp[i][j];
			}
		  }	
       	break;
	   }
	   s=0;
	   if(choice==1||choice==3||choice==4||choice==6)
	   {
       for(i=0;i<col;i++)
       {
       	for(j=0;j<line;j++)
       	{
       		photo[s]=0;
       		photo[s]=temp2[i][j];
       		s++;
       	}
       }
       }
       else
       {
       	for(i=0;i<line;i++)
       {
       	for(j=0;j<col;j++)
       	{
       		photo[s]=temp[i][j];
       		s++;
       	}
       }
	   }
	return photo;
}

