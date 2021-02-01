#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define clear() printf("\033[H\033[J")

int degerAl(char *str) //Kullanıcidan degerleri almamizi saglayan fonksiyon.
{
    char *buffer;
    buffer = readline("\n myshell>> ");
    if (strlen(buffer) != 0)
    {
        strcpy(str, buffer);
        return 0;
    }
    else
    {
        return 1;
    }
}

int dikParcala(char *str, char **strpiped) // | işaretine göre komutları bölüyor.
{
    int i;
    for (i = 0; i < 2; i++)
    {
        strpiped[i] = strsep(&str, "|");
        if (strpiped[i] == NULL)
            break;
    }

    if (strpiped[1] == NULL)
        return 0; 
    else
    {
        return 1;
    }
}

void boslukParcala(char *str, char **parsed) // Boşluklara göre komutlari bölüyor.
{
    int i;
    for (i = 0; i < 100; i++)
    {
        parsed[i] = strsep(&str, " ");

        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
}

int komutCalistir(char *argv[]) //Verilen parametrelere göre komutları çalıştırır.
{
    char *dizi[4];
    dizi[0] = argv[1];
    dizi[1] = argv[2];
    dizi[2] = argv[3];
    dizi[3] = NULL;

    int i = fork();
    int k;

    if (i == 0)
    {
        k = execv(argv[0], dizi);
        perror("Yanlis Bir Komut Girdiniz");
    }
    else
    {
        wait(&k);
    }
}

int catCalistir(char *argv[]) //Linuxun cat programini çalıştırır.
{

    int i = fork();
    int k;
    if (i == 0)
    {
        k = execv("/bin/cat", argv);
        perror("Yanlis Bir Komut Girdiniz");
    }
    else
    {
        wait(&k);
    }
}

int uzunluk(char *x[]) //Arrayin Uzunluğunu bulur.
{

    int a = 0;
    for (int i = 0; x[i] != '\0'; i++)
    {
        a++;
    }

    return a;
}

int kontrol(char *argv[]) //Kontroller icin Uzunluk Tutar.
{
    int i = 0;
    int count = 0;
    while (argv[i] != NULL)
    {
        count++;
        i++;
    }
    return count;
}

int main(int argc, char const *argv[])
{
    //komutlar "|" karakterine gore ayrilan komutları tutuyor.
    //kelimeler bosluklara göre ayrilan komut parametlerini tutuyor.

    char liste[150], *kelimeler[100] = {NULL}, *komutlar[100], *komutlarim[5]; 

    komutlarim[0] = "tekrar";
    komutlarim[1] = "islem";
    komutlarim[2] = "cat";
    komutlarim[3] = "exit";
    komutlarim[4] = "clear";

    int cikislar = 1;
    int bulundumu = 0;
    while (cikislar)
    {
        degerAl(liste);
        dikParcala(liste, komutlar); 
        for (int i = 0; i < uzunluk(komutlar); i++) // Kullanıcı birden fazla komut girebileceği için komutlar dönülür.
        {
            boslukParcala(komutlar[i], kelimeler); //boşluklara göre kelimlere atar.
            for (int j = 0; j < 5; j++)//girilen komutun shell uygulamamızda olup olmadığına bakar.
            {
                if (strcmp(komutlar[0], komutlarim[j]) == 0) //iki string aynıysa komutu bulur.
                {

                    bulundumu = 1;
                    break;
                }
            }
            if (bulundumu == 0) //Bir komut bulunmadiginda dongunun basina dönülür.
            {
                printf("Yanlis Komut Girdiniz \n");
                bulundumu = 0;
                break;
            }

            if (strcmp(kelimeler[0], "clear") == 0)
            {
                clear();
            }
            else if (strcmp(kelimeler[0], "exit") == 0)
            {

                cikislar = 0;
            }
            else if (strcmp(kelimeler[0], "cat") == 0)
            {
                catCalistir(kelimeler);
            }

            else
            {
                if (strcmp(kelimeler[0], "tekrar") == 0)
                {
                    if (kontrol(kelimeler)!=3) // 3 den farkli parametre varsa hata verir.
                    {
                        printf("Yanlis Komut Girdiniz \n");
                        break;
                    }
                    
                }
                else if (strcmp(kelimeler[0], "islem") == 0) // 4 den farkli parametre varsa hata verir.
                {
                    if (kontrol(kelimeler)!=4)
                    {
                        printf("Yanlis Komut Girdiniz \n");
                        break;
                    }
                    
                }

                komutCalistir(kelimeler);
            }
        }
    }

    return 0;
}
