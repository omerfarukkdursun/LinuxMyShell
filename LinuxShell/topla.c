#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 

//Toplama icin aldığım 2 paremetrenin sonucunu gösteriyorum.

int main(int argc, char* argv[]) 
{
   int a = atoi(argv[0]);
   
   int b = atoi(argv[1]);
   int c= a+b;

    printf("%d + %d = %d\n",a,b,c);
    return 0;
}


