#include<stdio.h>
#include "misfn.h"

#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

// ------------------- VALIDACIONES CARACTER -------------------
//valida el ingreso de un caracter, PARAMETRO: 4 caracteres en mayuscula(con lo que valida) , RETORNA: lo que el usuario ingreso
char validarCuatroChar (char char1, char char2, char char3, char char4){
    char tipo;
    int validoFlag=0;

    while(validoFlag==0){
        scanf("%c", &tipo);
        fflush(stdin);
        tipo = toupper(tipo);
        if(tipo == char1 || tipo == char2 || tipo == char3 || tipo == char4){
            return tipo;
        }else{printf("\nError: Opci%cn inv%clida:   ",162,160);}
    }
}

//valida el ingreso de un caracter, PARAMETRO: 2 caracter en mayuscula(con lo que valida) ,RETORNA: lo que el usuario ingreso
char validarDosChar (char char1, char char2){
    char tipo;
    int validoFlag=0;
    printf("Ingrese %c / %c \n", char1, char2);

    while(validoFlag==0){
        scanf("%c", &tipo);
        fflush(stdin);
        tipo = toupper(tipo);
        if(tipo == char1 || tipo == char2){
            return tipo;
        }else{printf("\nError: Opci%cn inv%clida:   ",162,160);}
    }
}


// ------------------- VALIDACIONES NUMERICAS -------------------
// PARAMTRO: un numero en strig,
// RETORNA: 0 si hay un caracter que no sea un digito
// o RETORNA: 1 si el string es solo digitos numericos
int validaNum(char num[]){
    for(int i=0; i<strlen(num); i++){
        if((!isdigit(num[i])) && (num[i]!= '.') ){
            printf("\n\tIngrese un N%cmero:    ", 163);
            return 0;
        }
    }
    return 1;
}

// valida el ingreso de un numero,
// RETORNA: el numero positivo que ingreso el usuario
int validaPositivo(){
    int valor, valido=0;
    char valorString[10];

    while(valido==0){
        scanf("%s", valorString);
        fflush(stdin);
        valido = validaNum(valorString);
        if(valido==1){
            valor = atoi(valorString);
            if(valor<0){
                printf("\nError: No es un N%cmero Positivo:    ",163);
                valido=0;
            }else{
                return valor;
            }
        }
    }
}

// valida el ingreso de un numero float,
// RETORNA: el numero positivo float que ingreso el usuario
float validaPositivoFloat(){
    int valido=0;
    float valor;
    char valorString[10];

    while(valido==0){
        scanf("%s", valorString);
        fflush(stdin);
        valido = validaNum(valorString);
        if(valido==1){
            valor = atof(valorString);
            if(valor<0){
                printf("\nError: No es un N%cmero Positivo:    ",163);
                valido=0;
            }else{
                return valor;
            }
        }
    }
}

// valida el ingreso de un a�o
// PARAMETRO: el a�o actual
// RETORNA: el anio en formato numerico YYYY
int validaAnio(int hoy){
    int year;
    printf("\n\tIngrese A%co:    ",164);
    year = validaPositivo();

    while(year>hoy){
        printf("\nError: A%co Inv%clido  ",164,160);
        year=validaPositivo();
    }

    hoy -= 2000;

    if(year<1900){
        if(year < hoy){         // si el a�o que ingreso el usuario es menor a 22 le sumo 2000 y queda 2022
            year += 2000;
        }else{
            year += 1900;
        }
    }
    return year;
}

// valida el dia que sea positivo y no mayor que 31
// RETORNA: el dia
int validaDia(){
    int date;
    printf("\n\tIngrese D%ca:    ", 161);
    date = validaPositivo();
    while(date>31){
        printf("\nError: N%cmero inv%clido:  ",163,160);
        date = validaPositivo();
    }
    return date;
}

// usuario ingresa un numero de mes.
// PARAMETRO: el string donde guardara el mes
void validarMes(char a[]){
    int numMes;
    printf("\n\tIngrese el n%cmero de mes (Ejemplo: 1 para Enero):  ", 163);
    numMes = validaPositivo();
    while(numMes>12){
        printf("\nError: N%cmero Inv%clido",163,160);
        numMes = validaPositivo();
    }

    switch (numMes){
        case 1: strcpy(a, "ene");
                break;
        case 2: strcpy(a, "feb");
                break;
        case 3: strcpy(a, "mar");
                break;
        case 4: strcpy(a, "abr");
                break;
        case 5: strcpy(a, "may");
                break;
        case 6: strcpy(a, "jun");
                break;
        case 7: strcpy(a, "jul");
                break;
        case 8: strcpy(a, "ago");
                break;
        case 9: strcpy(a, "sep");
                break;
        case 10: strcpy(a, "oct");
                break;
        case 11: strcpy(a, "nov");
                break;
        case 12: strcpy(a, "dic");
                break;
    }
}


// ------------------- FUNCIONES UTILES -------------------

// Identifica el a�o actual.
// RETORNA: el a�o actual o 0 si hay un error
int esteAnio(){
    int valor;
    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    char year[5];
    char *formato = "%Y";
    int escrito = strftime(year, sizeof year, formato, &tiempoLocal);
    if(escrito!=0){
        valor = atoi(year);
        return valor;
    }else{return 0;}
}

//mayusculizador y minusculizador, PARAMTRO: cadena de caracteres a trabajar
void toUpperCase(char a[]){
    for(int i=0; i<strlen(a); i++){
        a[i] = toupper(a[i]);
    }
}
void toLowerCase(char a[]){
    for(int i=0; i<strlen(a); i++){
        a[i] = tolower(a[i]);
    }
}


