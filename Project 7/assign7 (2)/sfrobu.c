#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int comparisons = 0;
int frobcmp (const char *a, const char *b);

int wrapper(const void *a, const void *b)
{
    const char const *p1 = *(const char**)a;
    const char const *p2 = *(const char**)b;
    return (frobcmp(p1,p2));
}
int main()
{
    char const *a = "*{_CIA\030\03 ";
    //char const *b = "*`_GZY\v ";
    char const *b = "*{_CIA\030\031 ";

    char character;
    int count = 0;   //to tell when I need to reallocate
    int size_array1 = 2048;
    int read_status;
    struct stat filename;
    fstat(0, &filename);
    int file_size =  filename.st_size;
    char *array1 =(char*) malloc(size_array1*sizeof(char));
    //allocate bytes 2048 if hits 2048 allocate more

    if(S_ISREG(filename.st_mode))
      {
	if(array1 == NULL)
	  {
	    fprintf(stderr, "Error: cannot allocate memory");
	    exit(1);
	  }
	
	while(count < file_size)
	  {
	    array1[count] = character;
	    count++;

	    if(count == size_array1) //this means you have to reallocate
	      {
		array1 = (char*) realloc(array1, size_array1*2);
		if(array1 == NULL)
		  {
		    fprintf(stderr, "Error: memory could not be allocated");
		    exit(1);
		  }
		size_array1 = size_array1*2;
	      }
	    fstat(0, &filename);
	    file_size = filename.st_size;
	  }
      }
    else
      {
	while(1)
	  {
	    read_status = read(0, &character, 1);
	    if(read_status == 0)
	      {
		break;
	      }

	    array1[count] = character;
	    count++;

	    if(count == size_array1) //reallocate
	      {
		array1 = (char*) realloc(array1, size_array1*2);
		if(array1 == NULL)
		  {
		    fprintf(stderr, "Error: memory could not be allocated");
		    exit(1);
		  }
		size_array1 = (size_array1*2);
	      }
	  }
      }

    
    if(array1[count-1] != ' ')  //if there isn't a space add a space
      {
	array1[count] = ' ';
	count++;
      }
    
    //count the number of spaces
    int space_count = 0;
    
    int c = 0;
    for(c = 0; c < count; c++)  //count is the last index so < count+1 will run to the last index
    {
        if (array1[c] == ' ')
        {
            space_count++;
        }
    }
    
    //make an array of space_count pointers
    char **array2 = (char**) malloc(sizeof(char*) * space_count);
    if(array2 == NULL)
    {
	fprintf(stderr, "Error: cannot allocate memory");
	exit(1);
    }
    array2[0] = &array1[0];
    int array2_count = 1;
    int v = 1;
    for(; v < count; v++)
    {
        if(array2_count < space_count) //take care of end space situation
        {
            if(array1[v] == ' ')  //if space that means next position is a word
            {
                array2[array2_count] = &array1[v+1];
                array2_count++;
            }
        }
    }
    
    
    
    int test = (frobcmp(a, b));
    qsort(array2, space_count, sizeof(char*), wrapper);
    //printf ("%d", test);
    int n = 0;
    for(; n < space_count; n++)
    {
        int k = n;
        while(*array2[n] != ' ')
        {
            printf ("%c", *array2[n]); //print the char
            array2[n]++;    //iterate to the next char in the word
        }
        printf("%c", ' ');
        
    }
    free(array1);    //free dynamically allocated memory
    free(array2);
    fprintf(stderr, "Comparisons: %d\n", comparisons); 
    return 0;
}

int frobcmp (const char *a, const char *b)  //remember to make the wrapper
{
    while(1)
    {
        if(*a == ' ' && *b == ' ')  //a and b are equal
        {
            return 0;
        }
        else if(*a == ' ' && *b != ' ')  //b is greater than a (a is a prefix of b)
        {
            return -1;
        }
        else if(*a != ' ' && *b == ' ') //a is greater than b (b is a prefix of a)
        {
            return 1;
        }
        else if((*a ^ 42) > (*b ^ 42))  //a is greater than b
        {
            return 1;
        }
        else if((*a ^ 42) < (*b ^ 42)) //b is greater than a
        {
            return -1;
        }
        a++;
        b++;
    }
    
}
