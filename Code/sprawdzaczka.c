#include <stdio.h>
#include <stdlib.h>

#define HIGHLIGTHSPACE '_'

int wypisz_plik(char* nazwa){
    FILE *plik;
    char znak;
    plik = fopen(nazwa, "r");
    while((znak = fgetc(plik)) != EOF){
        if(znak == ' '){
            printf("%c", HIGHLIGTHSPACE);
        }else{
            printf("%c", znak);
        }
    }
    fclose(plik);
}

int przetestuj_program(){
    char znak, p;
    int stan = 0;
    FILE *dane_testowe, *przyklad, *result, *out, *compare;
    dane_testowe = fopen("dane_testowe.txt", "r");
    przyklad = fopen("files/przyklad.txt", "w");
    result = fopen("files/result.txt", "w");

    if (dane_testowe == NULL){
        printf("nie mozna otworzyc pliku: <dane_testowe.txt>");
        return 0;
    }
    if (przyklad == NULL){
        printf("nie mozna otworzyc pliku: <przyklad.txt>");
        return 0;
    }
    while((znak = fgetc(dane_testowe)) != EOF){
        if(znak == '*'){
            stan++;
            continue;
        }
        switch(stan){
            case 1:
                fputc(znak, przyklad);
                break;
            case 2:
                fflush(przyklad);
                system("./program < files/przyklad.txt > files/out.txt");
                fputc(znak, result);
                break;
            case 3:
                fflush(result);
                system("diff files/result.txt files/out.txt > files/compare.txt");
                compare = fopen("files/compare.txt", "r");
                if((p = fgetc(compare)) != EOF){
                    printf("error in test case for data:\n");
                    wypisz_plik("files/przyklad.txt");
                    printf("expected result:\n");
                    wypisz_plik("files/result.txt");
                    printf("got result:\n");
                    wypisz_plik("files/out.txt");
                    printf("------------------\n");
                }
                fclose(compare);
                fclose(przyklad);
                fclose(result);
                przyklad = fopen("files/przyklad.txt", "w");
                result = fopen("files/result.txt", "w");
                stan = 0;
                break;
        }
    }
    fclose(przyklad);
    fclose(result);
    fclose(dane_testowe);
    return 0;
}

int main()
{
    przetestuj_program();
    return 0;
}