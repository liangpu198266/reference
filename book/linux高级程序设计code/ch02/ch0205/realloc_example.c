#include <stdio.h>
#include <stdlib.h>

int main (int argc,char* argv[],char* envp[])
{
  int input;
  int n;
  int *numbers1;		//the new pointer
  int *numbers2;		//the old pointer	
  numbers1=NULL;		//init	

  if((numbers2=(int *)malloc(5*sizeof(int)))==NULL)	//numbers2 malloc memory
     {
         printf("malloc memory unsuccessful");
         exit(1);
         }
  for (n=0;n<5;n++) 					//init number2 data	
      {
      *(numbers2+n)=n;
      printf("numbers2's data: %d\n",*(numbers2+n));
      }

  printf("Enter an integer value you want to remalloc ( enter 0 to stop)\n");	//the number add
  scanf ("%d",&input);
     
  numbers1=(int *)realloc(numbers2,(input+5)*sizeof(int));	//realloc memory
  if (numbers1==NULL) { 
         printf("Error (re)allocating memory"); 
         exit (1); 
     }

  for(n=0;n<5;n++)					//this data is copy from numbers2
    {
    printf("the numbers1s's data copy from numbers2: %d\n",*(numbers1+n));
    }

 for(n=0;n<input;n++) 					//the new data
  {
      *(numbers1+5+n)=n*2;
      printf ("nummber1's new data: %d\n",*(numbers1+5+n));
     // numbers1++;
  }
  printf("\n");
  free(numbers1);					//free numbers1
  numbers1=NULL;
//  free(numbers2);					//don't free numbers2
  return 0;
}

