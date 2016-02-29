#include <stdio.h>

int main(int argc, char* argv[])
{
  int x = 0;
  int arglength1 = 0;//check for duplicates within argv[1]
  int arglength2 = 0;
  while(argv[1][x] != '\0')
  {
    arglength1++;
    x++;
  }
  int z = 0;
  while(argv[2][z] != '\0')
  {
    arglength2++;
    z++;
  }
  if(arglength1 != arglength2)
  {
    fprintf(stderr, "Arguments are different lengths");
    return 1; 
  }
  for(int i = 0; i < arglength1; i++)
  {
    for(int j = i+1; j < arglength1; j++)
      {
	if(argv[1][i] == argv[1][j])
	  {
	    fprintf(stderr, "Duplicates in argument1");
	    return 1;
	  }
      }
  }
  		
  int boolean = 1;
  int character = ' ';
  while(boolean)
    {
      character = getchar();
      if(character == EOF)
	break;
      int i = 0;
      while(i < arglength1)
	{
          if(character == argv[1][i])
	    {
	      //change this character
	      character = argv[2][i];
	      break;
	    }
	  i++;  //otherwise check to see if a character is matching the
	      //next one in the arg
        }
      putchar(character);    //then just output whatever character was 

      //then we end this iteration and go on to the next character using
      //getchar at the beginning of the loop   
    }
}
