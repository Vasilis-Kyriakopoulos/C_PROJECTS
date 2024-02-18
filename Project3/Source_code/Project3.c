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
#include <string.h>
#include <time.h>
#include "header.h"
int main(int argc, char *argv[])
{
	srand(time(NULL));
	char com[100]={0},code[4]={0},tmp[20]={0},tmp2[20]={0};
	int line=0,col=0,j=0,len,temp3=0;
	unsigned char clr,color[4]={0},*photo=NULL;
	if(argc!=4)
	{
		printf("Wrong parameteres\n");
		return 0;
	}
	int i=0;
	char space=0;
	FILE* f1=NULL,*f2=NULL;
	char v2[100];
	strcpy(v2,argv[2]);
	strcat(v2,".pgm");
    strcat(argv[3],".pgm");
	f1=fopen(v2,"rb");
	if(f1==NULL)
	{
	   printf("File for reading could not open\n");
	   return 0;
	}
	f2=fopen(argv[3],"wb");
	if(f2==NULL)
	{
	   printf("File for Writing could not open\n");
	   return 0;
	}
	i=0;
	if(fread(code,sizeof(char),3,f1)!=3)
			{
				    printf("Something Went Wrong with the file\n");
					fclose(f1);
	                 fclose(f2);
	                 exit(1);         
			}
	i=0;
         if(fread(com,sizeof(char),1,f1)!=1)
			{
				printf("Something Went Wrong with the file\n");
					fclose(f1);
	                 fclose(f2);
	                 exit(1);
	                    
			}
			
			if(com[0]=='#')
			{
				while(com[i]!='\n')
				{
					i++;
					if(fread(com+i,sizeof(char),1,f1)!=1)
			       {
				     printf("Something Went Wrong with the file\n");
					 fclose(f1);
	                 fclose(f2);
	                 exit(1);
				    }
				}
			}
			else
			{
				tmp[0]=com[0];
			}
			i=0;
			if(com[0]=='#')
			{
			
			if(fread(tmp,sizeof(char),1,f1)!=1)
			{
				printf("Something Went Wrong with the file\n");
					fclose(f1);
	                 fclose(f2);   
					 exit(1);      
			}
		   }
		while(tmp[i]!='\n')
		{
			i++;
		if(fread(tmp+i,sizeof(char),1,f1)!=1)
			{
				printf("Something Went Wrong with the file\n");
					fclose(f1);
	                 fclose(f2);   
					 exit(1);      
			}	
		
		}
		tmp[i]='\0';
		int mem;
		mem=i;
	    line=atoi(tmp);
	   
	    i=0;
	    while(1)
	    {
	    	if(tmp[i]!=' ')
	    	i++;
	    	else
	    	break;
		}
		col =atoi(tmp+i+1);
		 //printf("%d %d",line,col);
		tmp[mem]='\n';
		i=0;
	while(1)
	{
		if(fread(color+i,sizeof(char),1,f1)!=1)
			{
			    printf("Something Went Wrong with the file\n");
					fclose(f1);
	                 fclose(f2);   
					 exit(1);      
			}
			if(color[i]=='\n')
			{
			break;
		    }
		    i++;
	}
    clr=atoi(color);
    photo=(unsigned char*)malloc(sizeof(unsigned char)*(col*line));
    if(photo==NULL)
    {
    	printf("Malloc Failed\n");
    	exit(1);
	}
    for(i=0;i<line*col;i++)
    {
	 	if(fread(&photo[i],sizeof(char),1,f1)!=1)
	 	{
	 		fclose(f1);
	 		fclose(f2);
	       free(photo);
	       printf("Something Went Wrong with the file\n");
	       exit(1);
		 }
    }
    if(!strcmp("-n",argv[1]))
    {
    	noise(photo,line*col);
	}
	 else if(!strcmp("-fH",argv[1]))
	 {
	 	mirror(photo,line,col,1);
	 }
	 else if(!strcmp("-fV",argv[1]))
	 {
	 	mirror(photo,line,col,0);
	 }
	else if(!strcmp("-rR1",argv[1]))
	{
		
		rotate(photo,line,col,1);
		
	}
	else if(!strcmp("-rR2",argv[1]))
	{
		rotate(photo,line,col,2);
		
	}
	else if(!strcmp("-rR3",argv[1]))
	{
		rotate(photo,line,col,3);
	}
	//No need for rR4 because its the same picture
	else if(!strcmp("-rL1",argv[1]))
	{
		rotate(photo,line,col,4);
	}
	else if(!strcmp("-rL2",argv[1]))
	{
		rotate(photo,line,col,5);
	}
	else if(!strcmp("-rL3",argv[1]))
	{
		rotate(photo,line,col,6);
	}
	//No need for rL4 because its the same picture
    len=strlen(code);
    fwrite(code,sizeof(char),len,f2);
    if(com[0]=='#')
	{
    len=strlen(com);
    fwrite(com,sizeof(char),len,f2);
    }
    if(!strcmp("-rR1",argv[1])||!strcmp("-rR3",argv[1])||!strcmp("-rL1",argv[1])||!strcmp("-rL3",argv[1]))
    {
    	i=0;
      while(1)
	    {
	    	if(tmp[i]!=' ')
	    	i++;
	    	else
	    	break;
		}
		len=strlen(tmp+i+1)-1;
		fwrite(tmp+i+1,sizeof(unsigned char),len,f2);
		tmp[i+1]=' ';
		fwrite(&tmp[i+1],sizeof(unsigned char),1,f2);
		tmp[i]='\0';
		len=strlen(tmp)+1;
		tmp[i]='\n';
		fwrite(tmp,sizeof(unsigned char),len,f2);	
	}
	else
	{
    len=strlen(tmp);
    fwrite(tmp,sizeof(char),len,f2);
    }
    len=strlen(color);
    fwrite(color,sizeof(unsigned char),len,f2);
    fwrite(photo,sizeof(unsigned char),line*col,f2);
	free(photo);
	fclose(f1);
	fclose(f2);
	return 0;
}


