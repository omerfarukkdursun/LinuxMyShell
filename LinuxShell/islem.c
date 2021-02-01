#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 

//Toplama ve Cikartma işlemlerinin yonetildiği bolumdur.

int main(int argc, char const *argv[])
{
    char *dizi[3];
    dizi[0]=argv[1];
    dizi[1]=argv[2];
    dizi[2]=NULL;

    
    int i=fork(); 
    int k;
    if (i==0)
    {
        
        k = execv(argv[0],dizi); //Aladığım parametrelere göre processin çalışmasıdır.
        
        
    }
    else
    {
        wait(&k);
    }
    
    
    

}
