/* 
Vasilis Kyriakopoulos
AM : 2022201800103
dit18103@uop.gr
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct person
 {
        char name[20];
		  int age;
  }person ;
  int main(void){
  	double c;
  	srand(time(NULL));
  	int k,i,l,j;
  	int size,snum;
  	person *human;
  	printf("Give me the dimension of the array :");
  	scanf("%d",&size);
  	human = (person*)malloc(sizeof(person)*size);
  	if(human==NULL){
  		printf("\nmemory allocation failed\n");
  		exit(1);
	  }
	/*c=(double)rand()/((double)RAND_MAX+1);
	printf("%f\n",c);
	c=c*19;
	printf("%f\n",c);Gia kapoio logo mou petage sunexeia ton idio ari8mo
    k=1+(int)c;
	printf("%d",k);*/

	for(i=0;i<size;i++)
	{
			k= 1+ rand()%19;
		for(j=0;j<k;j++)
		{
		human[i].name[j]= 97 + rand()%26;
		}
		human[i].name[k]='\0';
	}
	for (i=0;i<size;i++)
	{
		human[i].age=1+ rand()%50;
		printf("%s, %d\n",human[i].name,human[i].age);
	}
	free(human);
	
  	return 0;
  }
