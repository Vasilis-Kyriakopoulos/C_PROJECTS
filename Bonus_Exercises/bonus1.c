/* Kyriakopoulos vasilis
   22/03/19
   AM:2022201810013
*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 5
int main(void)
{
	int i=0,j=0,k=0,l=0,q=0,t=0,flag=0;
	char *array[5],ch;
	int n=0;
	printf("choose size of the array 2nd dimennsion: ");
	scanf("%d",&n);
	getchar();
	for(i=0;i<SIZE;i++)
	{
		array[i]=(char*)malloc(sizeof(char)*n);
		if(array[i]==NULL)
		{
		printf("malloc failed");
		exit(1);
	    }
	}
	i=0;
	while((ch=getchar())!='\n' && ch!=EOF)
	{
		if(ch!=' ')
		{
			array[i][j]=ch;
			i++;
		}
		if(i==5)
		{
			j++;
			i=0;
		}	
	}
	printf("The matrix is\n\n");
	
	for(i=0;i<n;i++)
	{
		
		for(j=0;j<5;j++)
		{
		printf("%3c",array[j][i]);
	    }
         
	    for(k=0;k<5;k++)
	    {
	    	for(l=k+1;l<5;l++)
	    	{
	    		if(array[k][t]==array[l][t])
	    		{
	    	//	printf("Y");
	    		q++;
	    	    }
			}
	    }
		printf(" | ");
		if(q!=0)
		printf("Y");
		else 
		printf("N");
		q=0;
		printf("\n");
		t++;
		
	}
	
	printf("  __ __ __ __ __ ");
	printf("\n");
	
	
	for(i=0;i<SIZE;i++)
	{
		free(array[i]);
	}
    return 0;
}

