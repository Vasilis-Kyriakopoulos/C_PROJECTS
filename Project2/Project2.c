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
#define BUFFER 10000

int elem=0;// for print function
int doc=0;//for \\maketitle

typedef struct typesettingStack
{
 char tps[12];
 int param1;
 int param2;
 char *text;
 struct typesettingStack *prev;
} tpsStack;
void show(tpsStack *stack_pointer,char buf[]);
tpsStack * push(tpsStack *sp);
tpsStack * pop(tpsStack *sp);
tpsStack *  choice(char buf[],tpsStack* stack_pointer,int *title,int *abstract);
void print(tpsStack *stack_pointer);
void save(tpsStack* stack_pointer,char buf[],int end);
 tpsStack * filep(tpsStack *stack_pointer);

int main(void)
{ 
    int i,len,len2,p;
    int title=0,abstract=0;
    char *tmp,cho,buf[BUFFER]={0};
     FILE *lat;
     tpsStack * stack_pointer=NULL;
     stack_pointer=choice(buf,stack_pointer,&title,&abstract);
    
     title++;
     while(1)
	 {
     	stack_pointer=choice(buf,stack_pointer,&title,&abstract);
     	//while(getchar()!='\n');
     	
		 if(stack_pointer==NULL)
		 {
		 continue ;  
       	}
       	if(stack_pointer->prev==NULL)
		 {
		 	title=1;
		 }
     	if(!strcmp(stack_pointer->tps,"newAbstract"))
     	abstract++;
     
	  }
		   
  return 0;
}
 tpsStack * push(tpsStack *sp)
{
	tpsStack *tmp;
	tmp=(tpsStack*)malloc(sizeof(tpsStack));
		if(tmp==NULL)
	  { 
	     printf("Something Went Wrong...\n");
	     exit(1);
	  }
	 if(sp==NULL)
	{
	  tmp->prev=NULL;
	 return tmp;
	}	   
	tmp->prev=sp;
    return tmp;
 } 
 tpsStack * pop(tpsStack *sp)
 {
 	if(sp==NULL)
 	{
 		return sp;
	}
 	tpsStack *tmp;
    tmp=sp->prev;
    free(sp->text);
    free(sp);
    return tmp;
 }

tpsStack* choice(char buf[],tpsStack* stack_pointer,int *title,int *abstract)
{
	int len,len2,i=0,sum=0,j=0,sum2=0,len4=0,flag=0,end=0,coma=0,rem=0;
	FILE *fp;
	char *sect=NULL;
	if (*title==0){
	 do
	  {
	  	
	  	  if(j>0)
   {
   	while(getchar()!='\n');
   }
   j++;
	  	printf("Give a new title for the article: ");
	  	scanf("%s",buf);
	  	if(!strcmp(buf,"exit"))
	   {
		 while(stack_pointer!=NULL)
		 {
		 	stack_pointer=pop(stack_pointer);
		  } 	
         exit(0);
     }
	  	len=strlen(buf)-1;//for \n
      }while(strcmp(buf,"newTitle"));	
	}
else {
	
	j=0;
  do
 { 
  if(j>0)
   {
   	while(getchar()!='\n');
   }
   j++;
   
   printf("\n\nAvailable Actions:\n1.newAuthor 2.newAbstract\n3.newSection 4.newTable\n5.newIlist 6.newElist\n7.undo 8.print 9.show\n10.load 11.save 12.exit\n\n");
   scanf("%s",buf);
   if(!strcmp(buf,"exit"))
   {
   	while(stack_pointer!=NULL)
		 {
		 	stack_pointer=pop(stack_pointer);
		  } 
      exit(0);
    }
   if(!strcmp(buf,"newTitle"))
	{
		printf("\nYou have already gave a title\n");
	}
   len=strlen(buf)-1;//for \n
   if(*abstract!=0 &&!strcmp(buf,"newAbstract") )
   {
   printf("You have already used newAbstract action\n");
   while(getchar()!='\n');
   return stack_pointer;
   }
  }while(strcmp(buf,"newAuthor") &&strcmp(buf,"newAbstract")&&strcmp(buf,"newSection")&&strcmp(buf,"newTable")&&strcmp(buf,"newIlist")&&strcmp(buf,"newElist")&&strcmp(buf,"undo")&&strcmp(buf,"print")&&strcmp(buf,"show")&&strcmp(buf,"load")&&strcmp(buf,"save"));
       if(!strcmp(buf,"undo"))
       {
       	if(stack_pointer->prev==NULL)
       	{
       		*title=0;
		   }
		if(!strcmp(stack_pointer->tps,"newAbstract"))
       	{
       		*abstract=0;
		}
       printf("Your last Insert has been successfully deleted\n");
       	stack_pointer=pop(stack_pointer);
       	return stack_pointer;
	   }
	   if(!strcmp(buf,"load"))
	   {
	   	stack_pointer=filep(stack_pointer);
	   	return stack_pointer;
	   }
	   if(!strcmp(buf,"show"))
	   {
	   	show(stack_pointer,buf);
	   	return stack_pointer;
	   }
	   if(!strcmp(buf,"save"))
	  {
	  	 scanf("%s",&buf[len+2]);
	  	 strcat(&buf[len+2],".tex");
	  	 save(stack_pointer,&buf[len+2],end);
	  	 return stack_pointer;
	   } 
	  if(!strcmp(buf,"print"))
	  {
	  	scanf("%d",&elem);
	  	print(stack_pointer);
	  	while(getchar()!='\n');
	  	return stack_pointer;
	   } 
     if(!strcmp(buf,"newSection"))
     {
     	 scanf("%s",&buf[len+2]);
     	 buf[len+2]=atoi(&buf[len+2]);
       	    if(buf[len+2]!=1&&buf[len+2]!=2&&buf[len+2]!=3)
       	    {
       	    	printf("You should give parameter from 1 to 3 first\n");
       	    	while(getchar()!='\n');
       	    	return stack_pointer;
		     }
			sum=buf[len+2];
       
       
	  }
       
       else if(!strcmp(buf,"newElist")||!strcmp(buf,"newIlist"))
       {
       	    scanf("%s",&buf[len+2]);
             if(!isdigit(buf[len+2]))
             {
            printf("You should give a number first\n");
            return stack_pointer;
			 }
       	    
		 
       	     sum =atoi(&buf[len+2]);   
	   }
	   else if(!strcmp(buf,"newTable"))
       {
       
       	   scanf("%s",&buf[len+2]);

	    if(!isdigit(buf[len+2]))
	    {
	        printf("You should give two numbers first and after the text\n");
	        return stack_pointer;
		}
         sum =atoi(&buf[len+2]);
	     
       	    scanf("%s",&buf[len+2]);
       	 if(!isdigit(buf[len+2]))
       	   {
       	   	printf("You should give two numbers first and after the text\n");
	        return stack_pointer;
		    }
		    
		   sum2 =atoi(&buf[len+2]);
		  
		       
	   }
        }
        
        
		 gets(&buf[len+2]);
		 
		 for(i=0;buf[len+2+i]!='\0';i++)
		 {
		 	if(buf[len+2+i]==',')
		 	coma++;
		 }
		 if(coma!=sum-1&&(!strcmp(buf,"newIlist")||!strcmp(buf,"newElist")))
		{
			printf("You should separate the elements of the list with ','\n");
			return stack_pointer;
		}
		 if(coma!=sum-1&&!strcmp(buf,"newTable"))
		 {
		 	printf("You should separate the text with ',' as many times as the first dimension of the array-1\n");
		 	return stack_pointer;
		 }
		 if(!strcmp(buf,"newSection"))
		 {
		    if(strstr(&buf[len+2]," & ")==NULL) 
		   {
		   	 printf("You should give '&' between Introduction and text:");
		   	 return stack_pointer;
		   } 
		 }
		 stack_pointer=push(stack_pointer);
        stack_pointer->param1=sum;
        if(!strcmp(buf,"newTable"))
        {
        	stack_pointer->param2=sum2;
		}
        
        strcpy(stack_pointer->tps,buf);
        len2=strlen(&buf[len+2])-1;//for \n
		 stack_pointer->text=(char *)malloc(sizeof(char)*len2); 
		  if(stack_pointer->text==NULL)
		{
			printf("Something Went Wrong\n");
			exit(1);
		} 
		 strcpy(stack_pointer->text,&buf[len+3]);
		 for(i=0;i<BUFFER;i++)//to clean the buffer
		      buf[i]=0;
		 return stack_pointer;
 }
 void print(tpsStack *stack_pointer)
 {
 	if(stack_pointer==NULL)
 	{
 		return;
	 }
 	else if(stack_pointer->prev==NULL)
 	{
 		printf("\n%s %s",stack_pointer->tps,stack_pointer->text);
 		elem--;
 		return ;
	 }
	 else 
	 {
	 	print(stack_pointer->prev);
	 	 
	 	 
	 	 
	 	if(elem>0)
	 	{
	 	if(!strcmp(stack_pointer->tps,"newSection")||!strcmp(stack_pointer->tps,"newIlist")||!strcmp(stack_pointer->tps,"newElist"))
	 	{
	 	printf("\ntps:%s param1:%d text:%s",stack_pointer->tps,stack_pointer->param1,stack_pointer->text);
	    }
	    else if(!strcmp(stack_pointer->tps,"newTable"))
	 	{
	 	printf("\ntps:%s param1:%d param2:%d text:%s",stack_pointer->tps,stack_pointer->param1,stack_pointer->param2,stack_pointer->text);
	    }
	    else
	    {
	    printf("\ntps:%s text:%s",stack_pointer->tps,stack_pointer->text);
        }
        elem--;
      }
        
	 	return;
	 }
 }
 void show(tpsStack *stack_pointer,char buf[])
 {
 	  int i;
 	scanf("%s",buf);
 
     for(i=0;buf[i]!='\0';i++) 
 	   buf[i]=tolower(buf[i]);
 	
 	  
 	while(stack_pointer!=NULL)
    {
    	stack_pointer->tps[3]=tolower(stack_pointer->tps[3]);
    	 if(strstr(stack_pointer->tps,buf)!=NULL)
    	{
    		stack_pointer->tps[3]=toupper(stack_pointer->tps[3]);
    		if(!strcmp(stack_pointer->tps,"newSection")||!strcmp(stack_pointer->tps,"newIlist")||!strcmp(stack_pointer->tps,"newElist"))
    		
	 	{
	 		
	 	printf("\ntps:%s param1:%d text:%s",stack_pointer->tps,stack_pointer->param1,stack_pointer->text);
	 	
	    }
	    else if(!strcmp(stack_pointer->tps,"newTable"))
	 	{

	 	printf("\ntps:%s param1:%d param2:%d text:%s",stack_pointer->tps,stack_pointer->param1,stack_pointer->param2,stack_pointer->text);
	 
	    }
	    else
	    {

	    printf("\ntps:%s text:%s",stack_pointer->tps,stack_pointer->text);
	  
        }
    	}
    	 
		stack_pointer=stack_pointer->prev;
		
	}
 	return;
 }
 tpsStack * filep(tpsStack *stack_pointer)
 {
 	int num=0,i=0,len=0;
 	char c;
 	FILE *fp=NULL;
 	
 	char tmp[10000]={0},tmp2[10000]={0};
 	int para1=0,para2=0;
 	scanf("%d",&num); 
 	scanf("%s",tmp);
 	fp = fopen(tmp,"r");
 	if(fp==NULL)
 	{
 		printf("File could not open\n");
 		return stack_pointer;
	 } 
 	while(1&&num!=0)
 	{
      
        if(fgets(tmp,BUFFER,fp)==NULL)
        break;
        len=strlen(tmp)-1;
        if(tmp[len]=='\n')
        tmp[len]='\0';
       // len=strlen(tmp)-1;
       i=0;
        while(1)
        {
        	if(tmp[i]==' ')
        	{
        	tmp[i]='\0';
        	break;
            }
        	i++;
		}
	    len=strlen(tmp);
        if(!strcmp(tmp,"newAbstract")||!strcmp(tmp,"newTitle")||!strcmp(tmp,"newAuthor"))
        {
        	strcpy(tmp2,&tmp[len+1]);
        //	len = strlen(tmp2)-1;
		//   tmp2[len]=0;
		}
        else if(!strcmp(tmp,"newSection")||!strcmp(tmp,"newIlist")||!strcmp(tmp,"newElist"))
        {
        
        i=0;
        while(1)
        {
        	if(tmp[i]==' ')
        	{
        	tmp[i]='\0';

        	break;
            }
        	i++;
		}
		   para1=atoi(&tmp[len+1]);
		   len=len+1+strlen(&tmp[len+1]);
		   strcpy(tmp2,&tmp[len+1]);
		 //  len = strlen(tmp2)-1;
		 //  tmp2[len]=0;

		}
        else if(!strcmp(tmp,"newTable"))
        {
        	i=0;
        while(1)
        {
        	if(tmp[i]==' ')
        	{
        	tmp[i]='\0';

        	break;
            }
        	i++;
		}
        	para1=atoi(&tmp[len+1]);
		   len=len+1+strlen(&tmp[len+1]);
		   para2=atoi(&tmp[len+1]);
		   i=0;
        while(1)
        {
        	if(tmp[i]==' ')
        	{
        	tmp[i]='\0';

        	break;
            }
        	i++;
		}
		   len=len+1+strlen(&tmp[len+1]);
		   strcpy(tmp2,&tmp[len+1]);
		  // len = strlen(tmp2)-1;
		 //  tmp2[len]=0;
		   
		   //	printf("%s",tmp2);
		}
		else
		{
			printf("\nSome parameters in the file are wrong\n");
			return stack_pointer;
		}
		stack_pointer=push(stack_pointer);
 		strcpy(stack_pointer->tps,tmp);
 		if(!strcmp(stack_pointer->tps,"newSection")||!strcmp(stack_pointer->tps,"newIlist")||!strcmp(stack_pointer->tps,"newElist")||!strcmp(stack_pointer->tps,"newTable"))
 		{
 			stack_pointer->param1=para1;
		 }
		 if(!strcmp(stack_pointer->tps,"newTable"))
		 {
		 	stack_pointer->param2=para2;
		 }
		 stack_pointer->text=(char*)malloc(sizeof(char)*(strlen(tmp2)));
		 if(stack_pointer->text==NULL)
	    {
	    	 printf("Something Went Wrong\n");
	    	 exit(1);
		}
		 strcpy(stack_pointer->text,tmp2);
	num--;
	 }
 	fclose(fp);
 	return stack_pointer;
 }
  void save(tpsStack* stack_pointer,char buf[],int end)
 {
 	int i=0,j=0,count=0;
 	char *sect=NULL;
 	if(stack_pointer!=NULL)
 	{
 		end++;
	 save(stack_pointer->prev,buf,end);
	 sect=NULL;
 	 FILE* fp=NULL;
 	 fp=fopen(buf,"a");
 	
 	 
 	
 		 if(!strcmp(stack_pointer->tps,"newTitle"))
 		 {
 		 	 fprintf(fp,"\\documentclass{article}\n");
 		 	 fprintf(fp,"\\title{%s}\n",stack_pointer->text);
 		 }
		     
		  
		  if(!strcmp(stack_pointer->tps,"newAuthor"))
		{
			 fprintf(fp,"\\author{%s}\n",stack_pointer->text); 
	    }
	     if(!strcmp(stack_pointer->tps,"newSection")||!strcmp(stack_pointer->tps,"newIlist")||!strcmp(stack_pointer->tps,"newElist")||!strcmp(stack_pointer->tps,"newAbstract")||!strcmp(stack_pointer->tps,"newElist")||!strcmp(stack_pointer->tps,"newTable"))
	     {
	     if(doc==0)
			 {
			 fprintf(fp,"\\begin{document}\n");
			 fprintf(fp,"\\maketitle\n");
			 doc++;
		      }	
		 }
	     if(!strcmp(stack_pointer->tps,"newAbstract"))
		{
		    
		   fprintf(fp,"\\abstract{%s}\n",stack_pointer->text);	
		}	 
	   if(!strcmp(stack_pointer->tps,"newSection")) // thelei ftiaksimo
	 {
	 	 if(stack_pointer->param1==1)
	 	{
	 		sect=strstr(stack_pointer->text," & ");
	 		*sect=0;
	 		sect+=3;
	 		 fprintf(fp,"\\section{%s}\n%s\n",stack_pointer->text,sect);	
		  } 
		  if(stack_pointer->param1==2)
	 	{  
	 	     sect=strstr(stack_pointer->text," & ");
	 		*sect=0;
	 		sect+=3;
	 		 fprintf(fp,"\\subsection{%s}\n%s\n",stack_pointer->text,sect);
		 } 
		  if(stack_pointer->param1==3)
	 	{
	 		sect=strstr(stack_pointer->text," & ");
	 		*sect=0;
	 		sect+=3;
	 		 fprintf(fp,"\\subsubsection{%s}\n%s\n",stack_pointer->text,sect);
		} 
	 } 

	  if(!strcmp(stack_pointer->tps,"newElist"))
	 {
	 	fprintf(fp,"\\begin{enumerate}\n");
	 	fprintf(fp,"\\item ");
	 	for(i=0;stack_pointer->text[i];i++)
	 	
	 	{
	 		if(stack_pointer->text[i]==',')
	 		fprintf(fp,"\n\\item ");
	 		else
	 		fprintf(fp,"%c",stack_pointer->text[i]);
		}
	 	
	 	fprintf(fp,"\n\\end{enumerate}\n");
	 }
     if(!strcmp(stack_pointer->tps,"newIlist"))
	 {
	 	fprintf(fp,"\\begin{itemize}\n");
	 	fprintf(fp,"\\item ");
	 	for(i=0;stack_pointer->text[i];i++)
	 	
	 	{
	 		if(stack_pointer->text[i]==',')
	 		fprintf(fp,"\n\\item ");
	 		else
	 		fprintf(fp,"%c",stack_pointer->text[i]);
		 }
	 	
	 	fprintf(fp,"\n\\end{itemize}\n");
	 }
	 count=0;
	  if(!strcmp(stack_pointer->tps,"newTable"))
	  {
	  	   for(i=0;stack_pointer->text[i]!=',';i++)
	  	  {
			printf("%c",stack_pointer->text[i]);	
	  	  	if(stack_pointer->text[i]=='&')
	  	   { 
		     
	  	    count++;
		  }
		   }
		   
	  	fprintf(fp,"\\begin{table}\n");
	  	 fprintf(fp,"\\centering\n");
	  	 fprintf(fp,"\\begin{tabular}{c|");
	  	 
	  	  
	  	 for(i=1;i<=count;i++)
	  	{
	  		 if(i==count)
	  	  	 fprintf(fp,"c}\n");
	  	  	 else 
	  	  	 fprintf(fp,"c|");
		}   

    
		  for(i=0;stack_pointer->text[i]!='\0';i++)
		 {  
		   if(stack_pointer->text[i]==',')
		   {
		   	   fprintf(fp,"\\\\\n");
			 }
			  else  
		 	fprintf(fp,"%c",stack_pointer->text[i]);
		 }  
           fprintf(fp,"\n"); 
	  	 fprintf(fp,"\\end{tabular}\n");
	  	 fprintf(fp,"\\end{table}\n");
	  }
	  if(end==1)
	  {
	   fprintf(fp,"\\end{document}");
      }
 	 fclose(fp);
     
 }
     else
     return;
  } 
