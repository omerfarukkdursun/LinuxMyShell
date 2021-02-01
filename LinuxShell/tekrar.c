#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 

//Arguman listemizin 0. indexindeki ifadeyi,
//argüman listemisin 1. indexindeki sayi kadar tekrarlamamizi saglayan for islemi.

int main(int argc, char const *argv[]) 
{
    for(int i=0; i<atoi(argv[1]);i++) { 

        printf("%s \n", argv[0]);
    }
    return 0;
}
