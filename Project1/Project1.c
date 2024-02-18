/* 
   Kyriakopoulos Vasilis
   AM:2022201800103
   dit18103@uop.gr

   Adaloglou Sotiris
   AM:2022201800005
   dit18005@uop.gr
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>//for calculate the score
#define BEST_SCORE 1000000
void random_colors(int**p,int n,int m,int color);
void print(int**p,int n,int m);
int hammer(int**p,int n,int m,int line,int colm,int color);
int  check_hammer(int**p,int n,int m,int line,int colm,int color);
int  bomb (int**p,int n,int m,int line,int colm);
void add(int**p,int line,int colm,int color);
void gravity(int**p,int n,int m);
void push(int**p,int n,int m,char direction);
int** level_up(int**p,int n,int m,int color/*for random_colors function*/);
int score(int**p,int n,int m,char act,int tiles);
int tile=0;//global tile for hammer score
     int  main(void)
 { 
	 srand(time(NULL));
	int n=0,m=0,**p=NULL,i=0,color,line,colm,clr,flag,level=1,j,sco=0,tiles=0;
	char cho,direction;
	   printf("   WELCOME TO THE DEMOLITION MAN\n");
	    printf("  -------------------------------\n");
	do{
	printf("Give me the dimensions of the table separated by space:\nNote:The table must have dimensions between [3,10]:");
	scanf("%d %d",&n,&m);
	while(getchar()!='\n');
      }while(n<3||m<3||n>10||m>10);
      do
     {
     	printf("Give me the  number of  different colors ");
     	scanf("%d",&color);
     	printf("\n");
	  }while(color<2 || color>9);//The number of colors cannot be less than 2  
      
      p=(int**)malloc(sizeof(int*)*n);
      if(p==NULL)
      {
      	printf("Program could not run\n");
      	exit(1);
	  }
	  for(i=0;i<n;i++)
	  {
	  	p[i]=(int*)malloc(sizeof(int)*m);
	  	if(p[i]==NULL)
	  	{
	  		printf("Program could not run\n");
	  		exit(1);
		}
	  }
	  random_colors(p,n,m,color);
	   
	    while(1)
	  {
	  	  print(p,n,m);
	    
	     flag=1;
	  	for(i=0;i<n;i++)
	  	  for(j=0;j<m;j++)
	  	     if(p[i][j]!='.')
	  	    {
	  	    	flag=0;
	  	    	 i=n-1;//to break the first for-loop
	  	    	break;
			}  
	       if(flag)
		  {
		  	for(i=0;i<n;i++)
			   free(p[i]);
			   
			   free(p);	
		  	if(n==10&& m<10)	  
		  	m++;
		     
		  	else if(m==10&& n<10)
		  	 n++;
		  	 else
		  	 {
		  	 	n++;
		  	 	m++;
			   }
		  	 
		  	 if(n>10 && m>10)
			{
				 printf("\nCongratulations you win\n\n");
				 printf("You successfully played %d levels.\n",level);
	             printf("Your Score is %d points\n",sco);
				 return 0;
			}
			 		    
			  p=level_up(p,n,m,color);
			  tile=0;
			  level++; 
			  printf("\nGood job lets go to level %d\n\n",level);
			  print(p,n,m);
		 } 	
	  	        
	    printf("\nAvailiable Actions:\n\nWeapons: h/H-Hammer,b/B-Bomb\n\nCommands: p/P-Push tiles,a/A-Add tiles,x/X-Exit Game\n\n");
	    do {
	         while(getchar()!='\n');//clear memory of the keyboard
	    printf("Level %d.\n\n",level);
		  if(sco!=0)
		   printf("Your score is %d points\n",sco);    
	    printf("Shall I wait more?\nMakeyour move:");
         scanf("%c",&cho);
         if(cho!='h'&&cho!='H'&&cho!='b'&&cho!='B'&&cho!='p'&&cho!='P'&&cho!='a'&&cho!='A'&&cho!='x'&& cho!='X')
           printf("\nThe Move %c Does not Exist\n\n",cho);
         if(cho=='x'||cho=='X')
	   { 
	      printf("You successfully played %d levels.\n",level);
	      printf("Your Score is %d points\n",sco);
	       if(sco> BEST_SCORE||(n==10 && m==10))
	     {
	     	printf("\nYou Did It Great\n");
	    	printf("\nHope You Enjoyed it\nDEMOLITION MAN\n");
		 }
		  else
		 {
		 	 printf("\nYou Need More Practice\n");
		 	 printf("\nHope You Enjoyed it\nDEMOLITION MAN\n");
		  } 
	       for(i=0;i<n;i++)
			   free(p[i]);
			  
			   free(p);
	      return 0;
	    }
	    if(cho=='p'||cho=='P')
	    {
	    	scanf("%c",&direction);
	    	line=1; //to skip do-while 
	    	colm=1; //    -"-
	    }
		 if(cho=='a'||cho=='A')
		 {
		 	scanf(" %d,%d %d",&line,&colm,&clr);
		 	       if(line<1 || line>n || colm<1 || colm>m)
	               { 
	                    printf("\nThe Coordinate (%d,%d) Does not Exist\n\n",line,colm);
		           }
		           if(clr<1||clr>color)
		           {
		           	printf("\nThis color does not exist\n\n");
		           }
		 }
	     if(cho=='h'||cho=='H'||cho=='b'||cho=='B')
	               {
	             scanf(" %d,%d",&line,&colm);
	               if(line<1 || line>n || colm<1 || colm>m)
	                  {
	                  printf("\nThe Coordinate (%d,%d) Does not Exist\n\n",line,colm);
	            	  }
	               }
	    }while(cho!='h'&&cho!='H'&&cho!='b'&&cho!='B'&&cho!='p'&&cho!='P'&&cho!='a'&&cho!='A'|| (line<1 || line>n || colm<1 || colm>m));
	   
	   
	         switch(cho)
	      {
	    	case('h'):
	    	case('H'):	
	    	  if(p[line-1][colm-1]=='.')
	    	 {
			  
	    	   do
			  {
			  	 while(getchar()!='\n');
			    printf("\nThis Tile Is Empty\nGive a Valid Coordinate:");//For Wrong Input At Hammer Action
			    scanf("%d,%d",&line,&colm);
			  }while(p[line-1][colm-1]=='.');  
		     }
		        if(check_hammer(p,n,m,line-1,colm-1,p[line-1][colm-1]))// if check_hammer returns 1 
		       {
		       	  printf("\nYou Don't Play Fair\n\n");
		       	  break;
				} 
		     
		       tiles=hammer(p,n,m,line-1,colm-1,p[line-1][colm-1]);
		        sco+=score(p,n,m,cho,tiles);
	    	     break;
	    	 case('b'):
	    	 case('B'):
	    	 	 if(p[line-1][colm-1]=='.')
	    	  {
			    do
			   {
			  	 while(getchar()!='\n');
			    printf("\nThis Tile Is Empty\nGive a Valid Coordinate:");//For Wrong Input At Hammer Action
			    scanf("%d,%d",&line,&colm);
			   }while(p[line-1][colm-1]=='.');
		     }
		          tile=0;//While player does not use bomb the spree combo in score increases else goes to zero  
			     tiles=bomb(p,n,m,line-1,colm-1);
			     sco+=score(p,n,m,cho,tiles);
		      
			 break;
			 case('p'):
			 case('P'):
			 	   
			 	 while(direction!='l'&&direction!='L'&&direction!='r'&&direction!='R')//For Wrong Input of Pushing Action
			 	{
			 		while(getchar()!='\n');
				 printf("You are pushing with wrong input\nAvailiable Actions:l/L-Left,r/R-Right\n");
			 	 scanf("%c",&direction);
			 	}
			 	 push(p,n,m,direction);
			 
			   break;
			 case('a'):
			 case('A'):
			 	 if(clr<1 || clr>color)
			 	{
				  do
			 	{
			 	  while(getchar()!='\n');
			 	   printf("The Availiable Colors are Between 1-%d\n",color);
				    scanf("%d",&clr);   
				}while(clr<1||clr>color);
		      }
				 if(p[line-1][colm-1]!='.')
	    	  {
			    do
			   {
			  	 while(getchar()!='\n');
			    printf("\nThis Tile Is Full\nGive a Valid Coordinate:");//For Wrong Input At Hammer Action
			    scanf("%d,%d",&line,&colm);
			   }while(p[line-1][colm-1]!='.');
			  }
			      if(sco!=0)
			   {	
			     add(p,line-1,colm-1,clr);
 			   
	  		        if(sco>10)
  			      {
				  if(sco%2==1)
			        sco-=(sco/4)+1;   //instant score calculate for add move
			       else 
			       sco-=(sco/4);
                               }
 			       else 
   			       sco--;
 			    }
  			     else
 			     printf("\nYour score is 0 you must collect some points to add a tile\n\n");
                            break; 
       }
        gravity(p,n,m);
    }
	return 0;
}

  void  random_colors(int**p,int n,int m,int color)//here we give random numbers to array
{
	int i,j;
	double c;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
				c=(double)rand()/(double)(RAND_MAX);
			     c=c*color+1;
	            p[i][j]=(int)c;
	            
		}
	}
	return ;
}
void  print(int**p,int n,int m)//here we print the table
{
	printf("    ");
	int i,j;
	for(j=0;j<m;j++)
	{
		printf("%3d",j+1);
	}
	printf("\n");
	for(j=0;j<3*m+4;j++)//type for first underline
	{
		printf("%c",'-');
	}
	
		for(i=0;i<n;i++)
	    {
		printf("\n");
		if(i>=9)
		{
			printf("%d |",i+1);
		}
		else
		printf("%d  |",i+1);
		
		   for(j=0;j<m;j++)
		   {
			if(p[i][j]=='.')
			printf("%3c",p[i][j]);
			else
			printf("%3d",p[i][j]);
	       }
	    }
	return ;
}

 int hammer(int**p,int n,int m,int line,int colm,int color)
{
	  
	if(color!=p[line][colm])
	{
		return 0 ;
	}
	else 
  {
     p[line][colm]='.';
	 tile++;
	 	 
  }	
     
if((line==0&&colm==0)||(line==n-1&&colm==0)||(line==0&&colm==m-1)||(line==n-1&&colm==m-1))//corners
    {
	 	if(line==0&&colm==0)
	   {
	      hammer(p,n,m,line,colm+1,color);
	      hammer(p,n,m,line+1,colm,color);
	      
	       return tile ;
		             	 
	   }
	    else if(line==n-1&&colm==0)
	   {
	   	    hammer(p,n,m,line-1,colm,color);
	        hammer(p,n,m,line,colm+1,color);       
	         return tile;
	   } 
	    else if(line==0&&colm==m-1)
	   {
	   	         hammer(p,n,m,line,colm-1,color);
	             hammer(p,n,m,line+1,colm,color);
	             return tile;
		}
	    else if(line==n-1&&colm==m-1)
	   {
	   	     hammer(p,n,m,line-1,colm,color);
	         hammer(p,n,m,line,colm-1,color); 
			 return tile;   	 
	   } 
	 	   
	}
   
 else if((line==0&&colm>0)||(line==n-1&&colm>0)||(line>0&&colm==0)||(line>0&&colm==m-1))// line-columns
	{
      if(line==0&&colm>0)
      {
      	   hammer(p,n,m,line,colm+1,color); 
      	   hammer(p,n,m,line,colm-1,color);
      	   hammer(p,n,m,line+1,colm,color);
      	   return tile;
      
	  }
	  if(line==n-1&&colm>0)
      {
         hammer(p,n,m,line-1,colm,color);
         hammer(p,n,m,line,colm+1,color);
         hammer(p,n,m,line,colm-1,color);
         return tile;
	  }
	  if(line>0&&colm==0)
      {
      hammer(p,n,m,line,colm+1,color);
      hammer(p,n,m,line+1,colm,color);
      hammer(p,n,m,line-1,colm,color);
      return tile;
      	
	  }
	  if(line>0&&colm==m-1)
      {
         hammer(p,n,m,line,colm-1,color);
         hammer(p,n,m,line-1,colm,color);
         hammer(p,n,m,line+1,colm,color);
         return tile;
	  }
     }
	  else//mid check
     {
      {
	     hammer(p,n,m,line-1,colm,color);
	     hammer(p,n,m,line+1,colm,color);
	     hammer(p,n,m,line,colm-1,color);
	     hammer(p,n,m,line,colm+1,color);
	     return tile;
	  }
	 
    }
  
  } 
	
	

  int check_hammer(int**p,int n,int m,int line,int colm,int color)
 {
 	 int i,corner=1,mid=1,line_colm=1;
if((line==0&&colm==0)||(line==n-1&&colm==0)||(line==0&&colm==m-1)||(line==n-1&&colm==m-1))//corners
    {
	 	if(line==0&&colm==0)
	   {
	      if(p[line][colm+1]!=color&&p[line+1][colm]!=color)
		          corner=0;    	 
	   }
	    else if(line==n-1&&colm==0)
	   {
	   	  if(p[line-1][colm]!=color && p[line][colm+1]!=color)
	   	        corner=0;   
	   } 
	    else if(line==0&&colm==m-1)
	   {
	   	    if(p[line][colm-1]!=color && p[line+1][colm]!=color)
	   	        corner=0; 
		}
	    else if(line==n-1&&colm==m-1)
	   {
	    if(p[line-1][colm]!=color && p[line][colm-1]!=color)
	   	        corner=0; 	 
	   } 
	 if(corner==0)
	    return 1;	  
	}
	   
 else if((line==0&&colm>0)||(line==n-1&&colm>0)||(line>0&&colm==0)||(line>0&&colm==m-1))// line-columns
	{
      if(line==0&&colm>0)
      {
      	if(p[line][colm-1]!=color && p[line][colm+1]!=color&&p[line+1][colm]!=color)
      	line_colm=0;
	  }
	  if(line==n-1&&colm>0)
      {
      	if(p[line][colm-1]!=color && p[line][colm+1]!=color&&p[line-1][colm]!=color)
      	line_colm=0;
	  }
	  if(line>0&&colm==0)
      {
      	if(p[line][colm+1]!=color && p[line-1][colm]!=color&&p[line+1][colm]!=color)
      	line_colm=0;
	  }
	  if(line>0&&colm==m-1)
      {
      	if(p[line][colm-1]!=color && p[line-1][colm]!=color&&p[line+1][colm]!=color)
      	line_colm=0;
	  }
	  if(line_colm==0)
	    return 1;
	  
	}
else //mid check
  {
     	for(i=-1;i<=1;i+=2)
    {
	   if(color==p[line+i][colm] ||color==p[line][colm+i])//Chek if the tile is alone
	     mid=0;
    }
	    if(mid==1)
	   {
	   	 return 1;
	   }
    }
    return 0;
  } 
  
    int bomb (int**p,int n,int m,int line,int colm)
  {
        int i,j;
    
      if((line==0&&colm==0)||(line==n-1&&colm==0)||(line==0&&colm==m-1)||(line==n-1&&colm==m-1))//corners
    {
	 	if(line==0&&colm==0)
	   {
	      p[line][colm]='.';
	      p[line][colm+1]='.';
	      p[line+1][colm]='.';
	      p[line+1][colm+1]='.';
	      return 4;
		             	 
	   }
	    else if(line==n-1&&colm==0)
	   {
	      p[line][colm]='.';
	      p[line-1][colm]='.';
	      p[line][colm+1]='.';
	      p[line-1][colm+1]='.';   
		   return 4;
	   } 
	    else if(line==0&&colm==m-1)
	   {
	   	  p[line][colm]='.';
	      p[line][colm-1]='.';
	      p[line+1][colm]='.';
	      p[line+1][colm-1]='.';  
		  return 4;   
		}
	    else if(line==n-1&&colm==m-1)
	   {
	   	   p[line][colm]='.';
	      p[line-1][colm]='.';
	      p[line][colm-1]='.';
	      p[line-1][colm-1]='.';   
		  return 4;	 
	   } 
	 	   
	}
   
 else if((line==0&&colm>0)||(line==n-1&&colm>0)||(line>0&&colm==0)||(line>0&&colm==m-1))//line-comls
	{
      if(line==0&&colm>0)
      {
      	  p[line][colm]='.';
	      p[line][colm-1]='.';
	      p[line][colm+1]='.';
	      p[line+1][colm+1]='.';   
          p[line+1][colm-1]='.';
          p[line+1][colm]='.';
          return 6;
          
	  }
	  if(line==n-1&&colm>0)
      {
          p[line][colm]='.';
	      p[line][colm-1]='.';
	      p[line][colm+1]='.';
	      p[line-1][colm+1]='.';   
          p[line-1][colm-1]='.';
          p[line-1][colm]='.';
          return 6;
	  }
	  if(line>0&&colm==0)
      {
          p[line][colm]='.';
	      p[line-1][colm]='.';
	      p[line+1][colm]='.';
	      p[line+1][colm+1]='.';   
          p[line][colm+1]='.';
          p[line-1][colm+1]='.';
          return 6;
      	
	  }
	  if(line>0&&colm==m-1)
      {
          p[line][colm]='.';
	      p[line-1][colm]='.';
	      p[line+1][colm]='.';
	      p[line+1][colm-1]='.';   
          p[line][colm-1]='.';
          p[line-1][colm-1]='.';
          return 6;
	  }
     }
	  else // mid
     {
      
	     for(i=-1;i<=1;i++)
		   for(j=-1;j<=1;j++)
		       p[line+i][colm+j]='.';   
		       
		       
		   return 9;    
	 }
  }  
    
  void add(int**p,int line,int colm,int clr)
 {
 	 p[line][colm]=clr;
 	 return ; 
  } 
  
  void gravity(int**p,int n,int m)
 {
 	int i=0,j=0,k;
    for(i=0;i<m;i++)
    {
    	for(j=n-1;j>0;j--)
    	{
    		for(k=j-1;k>=0;k--)
    		{
    			if(p[j][i]=='.'&&p[k][i]!='.')
    			{
    				p[j][i]=p[k][i];
    				p[k][i]='.';
				}
			}
		}
	}
 	 return;  
  } 
  void push(int**p,int n,int m,char direction)
 { 
     int flag=0,j,i,k;
    for(j=0;j<m;j++)
      if(p[n-1][j]=='.')//At least one column is erased
     {  
	   flag=1;
         break;
	  }
	
     
	  if(flag)
	 {
	   if(direction=='r'||direction=='R')
	   {
	   	for(i=m-1;i>=0;i--)
	   	{
	   		if(p[n-1][i]=='.')
	   		{
	   			 for(j=i-1;j>=0;j--)
	   			 {
	   			 	if(p[n-1][j]!='.')
	   			 	{
	   			 	  for(k=0;k<n;k++)
					  { 
					   p[n-1-k][i]=p[n-1-k][j]; 
					   p[n-1-k][j]='.';	  	
					   
					  } 
					  break;	
					}
				}
			}	
	    }
		}
		else
		{
		   for(i=0;i<m;i++)
	   	{
	   		if(p[n-1][i]=='.')
	   		{
	   			 for(j=i+1;j<m;j++)
	   			 {
	   			 	if(p[n-1][j]!='.')
	   			 	{
	   			 	  for(k=0;k<n;k++)
					  { 
					   p[n-1-k][i]=p[n-1-k][j]; 
					   p[n-1-k][j]='.';	  	
					   
					  } 
					  break;	
					}
				}
			}	
	    }	
	}  
	    
	  
}
      
	 else
	{
		 printf("\nThe Table is Full\n");
		  return ;
	} 
	    	   
 return ;
 	 
} 
   
    int** level_up(int**p,int n,int m,int color/*for random_colors function*/)
  {
  	 int i,j;
  	  
      p=(int**)malloc(n*sizeof(int*));
	   if(p==NULL)
	  {
	  	 printf("\nLevel Up Table Failed\n");
	  	  exit(1);
	   }
	     for(i=0;i<n;i++)
	  {
	     p[i]=(int*)malloc(m*sizeof(int));
		 if(p[i]==NULL)
		{
			 printf("\n Level Up Table Failed\n");
			 exit(1);
		} 	 
	 }
	       
	  random_colors(p,n,m,color); 
			   return p;    	
  }	 
  
   int score(int**p,int n,int m,char act,int tiles)
  {
  	  int sum=0,i,fact=1;
  	 switch(act)
  	{
  	  case('b'):
  	  case('B'):
  	  	 if(tiles==4 || tiles==6)
  	   {
  	   	   
  	     for(i=1;i<=tiles;i++)
  	    
  	       sum+=pow(i,2)*tiles;
	     
		return sum; 	   
  	   }
       else 
         return pow(tiles,3)*2;
  	     break;
  	 
	    case('h'):
  	    case('H'):
  	    
		 if(tiles<=6)
  	     {
		    for(i=1;i<=tiles;i++) //factorial
		       fact*=i;
		 
		   if(tiles<=4)
		     return fact*60;
		    else
		     return fact*10;
  	    }
	   
  	    else
  	   {
  	   	  return pow(tiles,3)*2;
	      
  	   } 
  	     break;	
	} 
	  
 }    
  
