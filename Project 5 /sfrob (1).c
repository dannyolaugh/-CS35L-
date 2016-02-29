#include <stdio.h>
#include <stdlib.h>
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
    
    int size_array1 = 2048;
    char *array1 =(char*) malloc(2048*sizeof(char)); //allocate bytes 2048 if hits 2048 allocate more
    if(array1 == NULL)
    {
	fprintf(stderr, "Error: cannot allocate memory");
	exit(1);
    }
    
    
    int character;
    int count = 0;
    for(; count < size_array1; count++)
    {
        character = getchar();  //use getchar for standard input
        if(count == 0 && character == EOF)
        {
            break;
        }
        if (character == EOF)
        {
            if(array1[count-1] != ' ')
            {
                //add a space at this position in the array
                array1[count] = ' ';
                count++;
            } 
            break;
        }
        if(count == size_array1)
        {
            array1 = (char*) realloc(array1, 2*size_array1);
	    if(array1 == NULL)
	    {
		fprintf(stderr, "Error: cannot allocate memory");
	    }
            size_array1 = 2*size_array1;
        }
        
        array1[count] = (char)character;
    }
    
    //count the number of spaces
    int space_count = 0;
    
    
    for(int i = 0; i < count; i++)  //count is the last index so < count+1 will run to the last index
    {
        if (array1[i] == ' ')
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
    for(int i = 1; i < count; i++)
    {
        if(array2_count < space_count) //take care of end space situation
        {
            if(array1[i] == ' ')  //if space that means next position is a word
            {
                array2[array2_count] = &array1[i+1];
                array2_count++;
            }
        }
    }
    
    
    
    int test = (frobcmp(a, b));
    qsort(array2, space_count, sizeof(char*), wrapper);
    //printf ("%d", test);
    
    for(int i=0; i < space_count; i++)
    {
        int k = i;
        while(*array2[i] != ' ')
        {
            printf ("%c", *array2[i]); //print the char
            array2[i]++;    //iterate to the next char in the word
        }
        printf("%c", ' ');
        
    }
    free(array1);    //free dynamically allocated memory
    free(array2);
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
