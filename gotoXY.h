#include <stdio.h>
#include <unistd.h>

void gotoXY(int x, int y) {

     printf("\033[%d;%df",y,x);

     fflush(stdout);

}
