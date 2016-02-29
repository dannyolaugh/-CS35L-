It took me multiple tries to figure out how to implement solution for
multithreading. After I finished writing what I thought was
a correct solution that would successfully multithread SRT, I found that my
code was only correct for 1 thread. For 2, 4, and 8 threads the output
was gibberish and not a recognizable graphic. In order to fix this, I ran my
program in gdb, and found that a major issue within my code involved
the way I was printing the pixel information. In order to fix this I
printed in main and employed the use of a three-dimensional array by
adding the coordinates px and py to the existing one-dimensional array.
This was literally the first time I've ever employed the use of a
three-dimensional array, but these changes were able to fix my problem
and allow successful execution not just
for a single thread, but for 2, 4, and 8 threads as well.

Comparing program performance between 1, 2, and 4 threads, I believe that
my implementation of SRT displayed considerable improvement. When running
with two threads, my program displayed a nearly 2 times performance
improvement. When running with 4 threads my program displayed a 3 times
performance improvement, and when running with 8 threads my program
displayed a 5 times performance improvement.

