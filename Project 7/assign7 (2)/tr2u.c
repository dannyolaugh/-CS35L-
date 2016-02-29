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
  int i;
  int j;
  for(i = 0; i < arglength1; i++)
    {
      for(j = i+1; j < arglength1; j++)
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
  int g;
  while(boolean)
    {
      g = read(0, &character, 1);
      if(g == 0)
	break;

       if(g < 0)
      	{
	  fprintf(stderr,"Error with reading the file");
	  return 1;
	}
      int d = 0;
      while(d < arglength1)
	{
	  if(character == argv[1][d])
	    {
	      //change this character
	      character = argv[2][d];
	      break;
	    }
	  d++;  //otherwise check to see if a character is matching the
	  //next one in the arg #include <stdio.h>

	}
      write(1,&character,1);    //then just output whatever character was

      //then we end this iteration and go on to the next character using
      //getchar at the beginning of the loop
    }
}
		    
