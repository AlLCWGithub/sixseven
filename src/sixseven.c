#include <stdlib.h>
#include <time.h>

void seedrand(){
srand(time(NULL));
}

int ssint(int min, int max){
return (rand() % max - min + 1) + min;
}
