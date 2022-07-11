// Autora: Higa Denise Mayra
// Fecha de entrega: 22 de junio de 2022
// Programa principal: main.c
// Libreria: misfn.h  y  misfn.c
// Archivos: concesionaria.dat  y  concesionaria_bajas.dat

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include "misfn.h"   // ------------------- FUNCIONES DE LA LIBRERIA -------------------
//ValidaCuatroChar() --> valida el ingreso de un caracter, PARAMETRO: 4 caracteres en mayuscula(con lo que valida) , RETORNA: lo que el usuario ingreso

//validarDosChar() --> valida el ingreso de un caracter, PARAMETRO: 2 caracter en mayuscula(con lo que valida) ,RETORNA: lo que el usuario ingreso

//validaNum(char num[]) --> // PARAMTRO: un numero en strig, RETORNA: 0 si hay un caracter que no sea un digito o RETORNA: 1 si el string es solo digitos numericos

//int validaPositivo() --> valida el ingreso de un numero,RETORNA: el numero positivo que ingreso el usuario

//float validaPositivoFloat() --> valida el ingreso de un numero float,RETORNA: el numero positivo float que ingreso el usuario

//int esteAnio() --> Identifica el año actual. RETORNA: el año actual o 0 si hay un error

//int validaAnio(int hoy) --> valida el ingreso de un año. PARAMETRO: el año actual. RETORNA: el anio en formato numerico YYYY

//int validaDia() --> valida el dia que sea positivo y no mayor que 31. RETORNA: el dia

//void validarMes(char a[]) --> usuario ingresa un numero de mes.PARAMETRO: el string donde guardara el mes

//toUpperCase(char a[]) // toLowerCase(char a[]) -->mayusculizador y minusculizador, PARAMTRO: cadena de caracteres a trabajar

// ------------------- STRUCT -------------------
struct fecha{
    char mes[3];
    int dia;
    int anio;
};
struct producto{
    int id;
    char marca[20];
    char modelo[20];
    char color[15];
    char tipo;
    char estado;
    struct fecha ingreso;
    int anio_fab;
    int km;
    float precio;
    int act;
};

// ------------------- IMPRIMIR -------------------
void printMenu();
void printTipo();
void printListar();
void printModificar();


// ------------------- FUNCIONES DEL MENU -------------------
// se fija si el archivo existe y consulta si el usuario quiere reescribirlo, si no existe lo crea
void crearArchivo(){
    char continua;
    FILE *pArchivo;

    pArchivo = fopen("concesionaria.dat","rb");     //abro modo lectura para analizar si el archivo existe
    if(pArchivo!=NULL){
        printf("El archivo ya existe, si lo crea nuevamente se perderan los datos, desea continuar?  ");
        continua = validarDosChar ('S', 'N');

        if(continua=='S'){
            fclose(pArchivo);
            pArchivo = fopen("concesionaria.dat","wb");     //reescribo el archivo
            for(int i=0; i<10; i++){
                struct producto unProd={0,"0", "0","0",'0','0',{"0"}};
                fwrite(&unProd, sizeof(struct producto),1,pArchivo);
            }
            printf("-- Archivo creado exitosamente! --");
            fclose(pArchivo);
        }
    }else{
        fclose(pArchivo);
        pArchivo = fopen("concesionaria.dat","wb");         //si no existe lo creo
        for(int i=0; i<10; i++){
            struct producto unProd={0,"0", "0","0",'0','0',{"0"}};
            fwrite(&unProd, sizeof(struct producto),1,pArchivo);
        }
        printf("-- Archivo creado exitosamente! --");
        fclose(pArchivo);
    }
}

// pide un id al usuario, analiza si ese id es 0 (esta vacio) y comienza la carga de un nuevo producto
// de lo contrario sale un error y pide otro id
void altaDeProducto(){
    int id, cantidad, hoy;

    hoy=esteAnio();     //funcion devuelve el anio actual sirve para validar el anio mas adelante

    struct producto new;
    FILE *pArchivo;

    printf("\n\n\tIngrese el ID:   ");
    id = validaPositivo();

    pArchivo = fopen("concesionaria.dat","rb+");
    if(pArchivo!=NULL){
    //analizo la cantidad de items (vacios o no) en el archivo
        fseek(pArchivo,0,SEEK_END);
        cantidad = ftell(pArchivo)/sizeof(struct producto);

    //si el id supera la cantidad total agrego items vacios hasta llegar a la posicion del id
    //si no lo supera analizo si el item ya fue cargado, comparando si el id es distinto de 0
        if(id>cantidad){
            for(int i=0; i<(id-cantidad); i++){
                struct producto unProd={0,"0", "0","0",'0','0',{"0"}};
                fwrite(&unProd, sizeof(struct producto),1,pArchivo);
            }
        }else{

            fseek(pArchivo,0,SEEK_SET);
            fseek(pArchivo, (id-1)*sizeof(struct producto), SEEK_CUR);      //busco y leo el struct
            fread(&new, sizeof(struct producto),1,pArchivo);

            while (new.id != 0) {
                printf("\nError: Campo completo. Ingrese ID nuevamente:  ");        //uno de los manejos de errores en validaciones y a continuacion hay mas
                id = validaPositivo();
                fseek(pArchivo,0,SEEK_SET);
                fseek(pArchivo, (id-1)*sizeof(struct producto), SEEK_CUR);
                fread(&new, sizeof(struct producto),1,pArchivo);
            }

        }

 // comienza la carga de un nuevo producto
        new.id = id;
        printf("\n\tIngrese Marca:  ");
        gets(new.marca);
        fflush(stdin);
        toUpperCase(new.marca);

        printf("\n\tIngrese Modelo:  ");
        gets(new.modelo);
        fflush(stdin);
        toUpperCase(new.modelo);

        printTipo();
        new.tipo= validarCuatroChar('A', 'S','P', 'U');

        printf("\n\tIngrese Fecha de Ingreso");

        new.ingreso.dia = validaDia();
        validarMes(new.ingreso.mes);        // PARAMETRO: donde se va a guardar
        if(hoy!=0){
            new.ingreso.anio = validaAnio(hoy);
        }else{
            printf("\n\tIngrese A%co:    ",164);
            new.ingreso.anio = validaPositivo();
        }

        printf("\n\tIngrese A%co de Fabricaci%cn:  ", 164,162);
         if(hoy!=0){
            new.anio_fab = validaAnio(hoy);
        }else{
            printf("\n\tIngrese A%co:    ",164);
            new.anio_fab = validaPositivo();
        }

        printf("\n\tIngrese Color:  ");
        scanf("%s", new.color);
        fflush(stdin);
        toUpperCase(new.color);

        printf("\n\tIngrese Estado (Nuevo o Usado):  ");
        new.estado=validarDosChar ('N', 'U');

        printf("\n\tIngrese Kilometraje:  ");
        new.km =validaPositivo();

        printf("\n\tIngrese Precio:  ");
        new.precio = validaPositivoFloat();
        new.act=1;

 //guardo el struct en el archivo
        fseek(pArchivo, -sizeof(struct producto), SEEK_CUR);
        fwrite(&new, sizeof(struct producto),1,pArchivo);
        printf("-- Agergado correctamente --");
        fclose(pArchivo);
    }
}

// Modifica el tipo, precio o km del producto buscado por id o por modelo
void modificar(){
    int id, finBuscar=0;  //finBuscar flag=1  si encuentra un prod
    char modelo[20];
    char option, confirma;
    struct producto unProd;
    FILE *pArchivo;

 //opciones de busqueda ID o MODELO
    printf("\n\n\tDesea buscar por Id o por Modelo?  ");
    option = validarDosChar('I','M');
    if(option=='I'){
        printf("\n\tIngrese el ID:   ");
        id = validaPositivo();
    }else{
        printf("\n\tIngrese un modelo:   ");
        scanf("%s", modelo);
        fflush(stdin);
        toUpperCase(modelo);
    }

    pArchivo = fopen("concesionaria.dat","rb+");
    if(pArchivo!=NULL){

 //Muestro el producto encontrado
              printf("\nId  -   Marca    -    Modelo   - Tipo -  Fecha de Ingreso  - Anio-fab -    Color   -  Estado -  Km  -   Precio   - Act \n");
        printf("---------------------------------------------------------------------------------------------------------------- \n");
        while(!feof(pArchivo) && finBuscar==0){
            fread(&unProd, sizeof(struct producto), 1, pArchivo);
            if(option=='I'){
                if(unProd.id==id){

                    printf("%2i  - %10s  - %10s  - %c  -    %2i /%3s /%4i    -   %4i   -  %10s  -  %c  - %6i  - %10.2f  - %i \n", unProd.id, unProd.marca, unProd.modelo, unProd.tipo, unProd.ingreso.dia, unProd.ingreso.mes, unProd.ingreso.anio, unProd.anio_fab, unProd.color, unProd.estado, unProd.km, unProd.precio, unProd.act);
                    finBuscar=1;
                }
            }else{
                if(strcmp(unProd.modelo, modelo) == 0){
                    printf("%2i  - %10s  - %10s  - %c  -    %2i /%3s /%4i    -   %4i   -  %10s  -  %c  - %6i  - %10.2f  - %i \n", unProd.id, unProd.marca, unProd.modelo, unProd.tipo, unProd.ingreso.dia, unProd.ingreso.mes, unProd.ingreso.anio, unProd.anio_fab, unProd.color, unProd.estado, unProd.km, unProd.precio, unProd.act);
                    finBuscar=1;
                }
            }
        }
 //Si se encontro un producto pregunto que desea modificar-la opcion 4 es para salir
 //Usuario ingresa los nuevos datos, confirma los cambios y se guarda el struct nuevamente
 //podia hacerlo una vez al final pero como di la opcion 4 para salir lo deje uno por uno
        if(finBuscar==1){
            printModificar();
            option = validarCuatroChar('1','2','3','4');
            switch (option){
                case '1':   printTipo();
                            unProd.tipo= validarCuatroChar('A', 'S','P', 'U');
                            printf("\n\tEst%c seguro que desea modificar los datos?  ",160);
                            confirma = validarDosChar('S', 'N');
                            if(confirma=='S'){
                                fseek(pArchivo, -sizeof(struct producto), SEEK_CUR);
                                fwrite(&unProd, sizeof(struct producto),1,pArchivo);
                                printf("\n-- Modificado correctamente --");
                            }
                            break;
                case '2':   printf("\n\tIngrese Precio:  ");
                            unProd.precio = validaPositivoFloat();
                            printf("\n\tEst%c seguro que desea modificar los datos?  ",160);
                            confirma = validarDosChar('S', 'N');
                            if(confirma=='S'){
                                fseek(pArchivo, -sizeof(struct producto), SEEK_CUR);
                                fwrite(&unProd, sizeof(struct producto),1,pArchivo);
                                printf("\n-- Modificado correctamente --");
                            }
                            break;
                case '3':   printf("\n\tIngrese Kilometraje:  ");
                            unProd.km =validaPositivo();
                            printf("\n\tEst%c seguro que desea modificar los datos?  ",160);
                            confirma = validarDosChar('S', 'N');
                            if(confirma=='S'){
                                fseek(pArchivo, -sizeof(struct producto), SEEK_CUR);
                                fwrite(&unProd, sizeof(struct producto),1,pArchivo);
                                printf("\n-- Modificado correctamente --");
                            }
                            break;
                case '4':   break;
            }
        }else{
            printf("\n-- No se encontraron productos --");
        }
        fclose(pArchivo);
    }else{printf("-- Error en la apertura del Archivo --");}    //otro manejo de error
}

// Modifica el precio de los autos.El usuario ingresa una marca el porcentaje y si aumenta o disminuye
void actualizar(){
    char marca[20];
    char option;
    int porcentaje, cantModificados=0;
    struct producto unProd;
    FILE *pArchivo;

    printf("\n\tIngrese una Marca:  ");
    scanf("%s", marca);
    fflush(stdin);
    toUpperCase(marca);

    printf("\n\tActualizaci%cn por Aumendo o Disminuci%cn del precio?  ",162,162);
    option = validarDosChar('A', 'D');

    printf("\n\tIngrese valor porcentual sin el simbolo (Ejemplo:10, equivale a 10%c):  ",37);
    porcentaje = validaPositivo();

    pArchivo=fopen("concesionaria.dat", "rb+");
    if(pArchivo!=NULL){
        while(!feof(pArchivo)){
            fread(&unProd, sizeof(struct producto), 1, pArchivo);
            if(strcmp(unProd.marca, marca) == 0){       //comparo si la marca es igual para modificarlo

                if(option =='A'){       //aumento del precio
                    unProd.precio += (porcentaje*unProd.precio)/100;
                }else{                  //disminucion del precio
                    unProd.precio -= (porcentaje*unProd.precio)/100;
                }
                fseek(pArchivo, -sizeof(struct producto), SEEK_CUR);
                fwrite(&unProd, sizeof(struct producto),1,pArchivo);
                fflush(pArchivo);
                cantModificados++;
            }
        }
        printf("\n-- %i Modificado correctamente --", cantModificados);

        fclose(pArchivo);
    }else{printf(" -- Error en la apertura del Archivo --");}
}

// ingreso el id y le doy la baja poniendo act=0
void bajaLogica(){
    int id, encontrado=0;  //encontrado flag=1  si encuentra un prod
    char confirma;
    struct producto unProd;

    FILE *pArchivo;

    printf("\n\tIngrese el ID:   ");
    id = validaPositivo();

    pArchivo = fopen("concesionaria.dat","rb+");
    if(pArchivo!=NULL){

        //Muestro el producto encontrado
               printf("\nId  -   Marca    -    Modelo   - Tipo -  Fecha de Ingreso  - Anio-fab -    Color   -  Estado -  Km  -   Precio   - Act \n");
        printf("------------------------------------------------------------------------------------------------------------------ \n");
        while(!feof(pArchivo) && encontrado==0){
            fread(&unProd, sizeof(struct producto), 1, pArchivo);
            if(unProd.id==id){
                printf("%2i  - %10s  - %10s  - %c  -    %2i /%3s /%4i    -   %4i   -  %10s  -  %c  - %6i  - %10.2f  - %i \n", unProd.id, unProd.marca, unProd.modelo, unProd.tipo, unProd.ingreso.dia, unProd.ingreso.mes, unProd.ingreso.anio, unProd.anio_fab, unProd.color, unProd.estado, unProd.km, unProd.precio, unProd.act);
                encontrado=1;
            }
        }

        if(encontrado==1){
            printf("\n\tEst%c seguro que quiere dar de baja?  ", 160);
            confirma=validarDosChar('S', 'N');

            if(confirma=='S'){
                unProd.act=0;
                fseek(pArchivo, -sizeof(struct producto), SEEK_CUR);
                fwrite(&unProd, sizeof(struct producto),1,pArchivo);
                printf("\n-- Dado de baja correctamente --\n");
            }
        }else{
            printf("\n-- No se encontr%c el producto --", 162);
        }
        fclose(pArchivo);

    }else{printf("-- Error en la apertura del Archivo --");}
    listarActivos();
}

// si hay productos dados de baja en el archivo principal los agrego en el archivo de bajas y dejo en 0 en el archivo principal
void bajaFisica(){
    struct producto unProd;
    struct producto vacio={0,"0", "0","0",'0','0',{"0"}};
    FILE *pArchivo;
    FILE *pBajas;

    pBajas = fopen("concesionaria_bajas.dat","rb"); //abro el archivo de bajas en modo lectura para analizar si el archivo existe
    if(pBajas!=NULL){
        fclose(pBajas);
        pBajas = fopen("concesionaria_bajas.dat","ab");    //si existe abro el archivo para agrego al final
    }else{
        fclose(pBajas);
        printf("\nSe creo el archivo de bajas");
        pBajas = fopen("concesionaria_bajas.dat","wb");    //si NO existe lo creo y agrego
    }

    pArchivo = fopen("concesionaria.dat","rb+");

    if(pArchivo!=NULL){
        while(!feof(pArchivo)){
            fread(&unProd, sizeof(struct producto), 1, pArchivo);
            if(unProd.act==0 && unProd.id!=0){                  // comparo si act=0 y si tiene id
                fwrite(&unProd, sizeof(struct producto),1,pBajas);      //agrego el struct en el archivo de bajas
                fflush(pBajas);

                fseek(pArchivo, -sizeof(struct producto), SEEK_CUR);    //me posiciono en el lugar correcto del archivo de productos
                fwrite(&vacio, sizeof(struct producto),1,pArchivo);     //guardo el struct vacio en el lugar donde estaba el struct que saque
                fflush(pArchivo);
            }
        }
        fclose(pArchivo);
        printf("\n-- Eliminado correctamente --");
    }else{printf("-- Error en la apertura del Archivo --");}
    fclose(pBajas);
}


// ------------------- FUNCIONES PARA LISTAR -------------------
// lista todos los productos (vacios o no). Con opcion de listar el archivo de bajas
void listarTodo(){
    struct producto unProd;
    char option;
    char altas[]="concesionaria.dat";
    char bajas[]="concesionaria_bajas.dat";
    char archivo[25];
    FILE *pArchivo;

    printf("\n\tListar archivo de Productos o de Bajas. ");   //para saber que archivo abre
    option = validarDosChar('P', 'B');
    if(option =='P'){
        strcpy(archivo, altas);
    }else{
        strcpy(archivo, bajas);
    }

    pArchivo=fopen(archivo, "rb");
    if(pArchivo!=NULL){
        fread(&unProd, sizeof(struct producto), 1, pArchivo);
                printf("\nId  -   Marca    -    Modelo   - Tipo -  Fecha de Ingreso  - Anio-fab -    Color   -  Estado -  Km  -   Precio   - Act \n");
        printf("-------------------------------------------------------------------------------------------------------------------- \n");
        while(!feof(pArchivo)){
            printf("%2i  - %10s  - %10s  - %c  -    %2i /%3s /%4i    -   %4i   -  %10s  -  %c  - %6i  - %10.2f  - %i \n", unProd.id, unProd.marca, unProd.modelo, unProd.tipo, unProd.ingreso.dia, unProd.ingreso.mes, unProd.ingreso.anio, unProd.anio_fab, unProd.color, unProd.estado, unProd.km, unProd.precio, unProd.act);
            fread(&unProd, sizeof(struct producto), 1, pArchivo);
        }
        fclose(pArchivo);
    }else{printf("\n-- Error en la apertura del Archivo --");}
}

void listarActivos(){
    struct producto unProd;
    FILE *pArchivo;
    pArchivo=fopen("concesionaria.dat", "rb");
    if(pArchivo!=NULL){
        fread(&unProd, sizeof(struct producto), 1, pArchivo);
               printf("\nId  -   Marca    -    Modelo   - Tipo -  Fecha de Ingreso  - Anio-fab -    Color   -  Estado -  Km  -   Precio   - Act \n");
        printf("------------------------------------------------------------------------------------------------------------------- \n");

        while(!feof(pArchivo)){
            if(unProd.act == 1){
                printf("%2i  - %10s  - %10s  - %c  -    %2i /%3s /%4i    -   %4i   -  %10s  -  %c  - %6i  - %10.2f  - %i \n", unProd.id, unProd.marca, unProd.modelo, unProd.tipo, unProd.ingreso.dia, unProd.ingreso.mes, unProd.ingreso.anio, unProd.anio_fab, unProd.color, unProd.estado, unProd.km, unProd.precio, unProd.act);
            }
            fread(&unProd, sizeof(struct producto), 1, pArchivo);
        }
        fclose(pArchivo);
    }else{printf("\n-- Error en la apertura del Archivo --");}
}

// Lista dependiendo del estado que ingresa el usuario por teclado. Con opcion de listar el archivo de bajas
void listarEstado(){
    char estado;
    struct producto unProd;
    char option;
    char altas[]="concesionaria.dat";
    char bajas[]="concesionaria_bajas.dat";
    char archivo[25];
    FILE *pArchivo;

    printf("\n\tListar archivo de Productos o de Bajas. ");   //para saber que archivo abre
    option = validarDosChar('P', 'B');
    if(option =='P'){
        strcpy(archivo, altas);
    }else{
        strcpy(archivo, bajas);
    }

    pArchivo=fopen(archivo, "rb");
    if(pArchivo!=NULL){
        printf("\n\tIngrese el estado Nuevo o Usado. ");
        estado = validarDosChar('U','N');

        fread(&unProd, sizeof(struct producto), 1, pArchivo);
                printf("\nId  -   Marca    -    Modelo   - Tipo -  Fecha de Ingreso  - Anio-fab -    Color   -  Estado -  Km  -   Precio   - Act \n");
        printf("------------------------------------------------------------------------------------------------------------------- \n");
        while(!feof(pArchivo)){
            if(unProd.estado == estado){
                printf("%2i  - %10s  - %10s  - %c  -    %2i /%3s /%4i    -   %4i   -  %10s  -  %c  - %6i  - %10.2f  - %i \n", unProd.id, unProd.marca, unProd.modelo, unProd.tipo, unProd.ingreso.dia, unProd.ingreso.mes, unProd.ingreso.anio, unProd.anio_fab, unProd.color, unProd.estado, unProd.km, unProd.precio, unProd.act);
            }
            fread(&unProd, sizeof(struct producto), 1, pArchivo);
        }
        fclose(pArchivo);
    }else{printf("\n-- Error en la apertura del Archivo --");}
}

// lista los productos que fueron ingresados en el mes que el usuario indica
void listarFecha(){
    char mes[3];
    int coincide=1;
    struct producto unProd;
    char option;
    char altas[]="concesionaria.dat";
    char bajas[]="concesionaria_bajas.dat";
    char archivo[25];
    FILE *pArchivo;

    printf("\n\tListar archivo de Productos o de Bajas. ");   //para saber que archivo abre
    option = validarDosChar('P', 'B');
    if(option =='P'){
        strcpy(archivo, altas);
    }else{
        strcpy(archivo, bajas);
    }

    validarMes(mes);
    pArchivo=fopen(archivo, "rb");
    if(pArchivo!=NULL){
        fread(&unProd, sizeof(struct producto), 1, pArchivo);
               printf("\nId  -   Marca    -    Modelo   - Tipo -  Fecha de Ingreso  - Anio-fab -    Color   -  Estado -  Km  -   Precio   - Act \n");
        printf("------------------------------------------------------------------------------------------------------------------ \n");
        while(!feof(pArchivo)){
            for(int i=0; i<3; i++){             //analiza caracter a caracter del mes ingresado por el usuario y el del struct
                if(unProd.ingreso.mes[i] != mes[i]){
                    coincide=0;                 //si no coincide el mes el flag cambia a 0
                }
            }
            if(coincide == 1){
                printf("%2i  - %10s  - %10s  - %c  -    %2i /%3s /%4i    -   %4i   -  %10s  -  %c  - %6i  - %10.2f  - %i \n", unProd.id, unProd.marca, unProd.modelo, unProd.tipo, unProd.ingreso.dia, unProd.ingreso.mes, unProd.ingreso.anio, unProd.anio_fab, unProd.color, unProd.estado, unProd.km, unProd.precio, unProd.act);
            }
            fread(&unProd, sizeof(struct producto), 1, pArchivo);
            coincide =1;
        }
        fclose(pArchivo);
    }else{printf("\n-- Error en la apertura del Archivo --");}
}

// Busca productos de la misma marca que ingresa el usuario y los lista
void listarMarca(){
    char marca[20];
    int alguno=0;       //flag si se encuentran productos, si encuentra al menos uno flag=1
    struct producto unProd;
    FILE *pArchivo;

    pArchivo=fopen("concesionaria.dat", "rb");
    if(pArchivo!=NULL){
        printf("\n\tIngrese una Marca:  ");
        scanf("%s", marca);
        fflush(stdin);
        toUpperCase(marca);

        fread(&unProd, sizeof(struct producto), 1, pArchivo);
                printf("\nId  -   Marca    -    Modelo   - Tipo -  Fecha de Ingreso  - Anio-fab -    Color   -  Estado -  Km  -   Precio   - Act \n");
        printf("-------------------------------------------------------------------------------------------------------------------- \n");
        while(!feof(pArchivo)){

            if(strcmp(unProd.marca, marca) == 0){
                alguno=1;
                printf("%2i  - %10s  - %10s  - %c  -    %2i /%3s /%4i    -   %4i   -  %10s  -  %c  - %6i  - %10.2f  - %i \n", unProd.id, unProd.marca, unProd.modelo, unProd.tipo, unProd.ingreso.dia, unProd.ingreso.mes, unProd.ingreso.anio, unProd.anio_fab, unProd.color, unProd.estado, unProd.km, unProd.precio, unProd.act);
            }
            fread(&unProd, sizeof(struct producto), 1, pArchivo);
        }
        fclose(pArchivo);
        if(alguno==0){
            printf("\n-- No se encontraron Datos --");
        }
    }else{printf("-- Error en la apertura del Archivo --");}
}

// El usuario ingresa dos km, el programa busca en ese rango de valores y lista los productos encontrados
void listarKm(){
    int alguno=0, kmMax, kmMin;      //flag si se encuentran productos, si encuentra al menos uno flag=1
    struct producto unProd;
    FILE *pArchivo;

    pArchivo=fopen("concesionaria.dat", "rb");
    if(pArchivo!=NULL){
        printf("\n\tIngrese Kilometraje M%cximo:  ",160);
        kmMax = validaPositivo();
        printf("\n\tIngrese Kilometraje M%cnimo>:  ",161);
        kmMin = validaPositivo();


        fread(&unProd, sizeof(struct producto), 1, pArchivo);
               printf("\nId  -   Marca    -    Modelo   - Tipo -  Fecha de Ingreso  - Anio-fab -    Color   -  Estado -  Km  -   Precio   - Act \n");
        printf("------------------------------------------------------------------------------------------------------------------ \n");
        while(!feof(pArchivo)){

            if(unProd.km>kmMin && unProd.km<kmMax){
                alguno=1;
                printf("%2i  - %10s  - %10s  - %c  -    %2i /%3s /%4i    -   %4i   -  %10s  -  %c  - %6i  - %10.2f  - %i \n", unProd.id, unProd.marca, unProd.modelo, unProd.tipo, unProd.ingreso.dia, unProd.ingreso.mes, unProd.ingreso.anio, unProd.anio_fab, unProd.color, unProd.estado, unProd.km, unProd.precio, unProd.act);
            }
            fread(&unProd, sizeof(struct producto), 1, pArchivo);
        }
        fclose(pArchivo);
        if(alguno==0){
            printf("\n-- No se encontraron Datos --");
        }
    }else{printf("-- Error en la apertura del Archivo --");}
}


int main(){
    int opcion;
    char listarOpcion;

    printMenu();
    scanf("%i", &opcion);
    fflush(stdin);

    while(opcion!=0){
        switch(opcion){
            case 1: crearArchivo();
                    break;
            case 2: altaDeProducto();
                    break;

            case 3: printListar();
                    listarOpcion = validarCuatroChar('1','2','3','4');
                    switch (listarOpcion){
                        case '1':   listarTodo();
                                    break;
                        case '2':   listarActivos();
                                    break;
                        case '3':   listarEstado();
                                    break;
                        case '4':   listarFecha();
                                    break;
                    }
                    break;

            case 4: printf("\tBuscar por Marca o por Kilometraje. ");
                    listarOpcion = validarDosChar('M','K');
                    switch (listarOpcion){
                        case 'M':   listarMarca();
                                    break;
                        case 'K':   listarKm();
                                    break;
                    }
                    break;

            case 5: modificar();
                    break;
            case 6: actualizar();
                    break;
            case 7: bajaLogica();
                    break;
            case 8: bajaFisica();
                    break;
            default: printf("\nError: Opci%cn inv%clida, Ingrese Nuevamente:   ",162,160);  //otro manejo de error
        }
        printMenu();
        scanf("%i", &opcion);
        fflush(stdin);
    }
    return 0;
}

// ------------------- IMPRIMIR MENU DE OPCIONES -------------------
void printMenu(){
    printf("\n\n------------------- MENU -------------------\n");
    printf("\t1: Crear Archivo \n");
    printf("\t2: Alta de Producto \n");
    printf("\t3: Listar Productos \n");
    printf("\t4: Buscar Producto \n");
    printf("\t5: Modificar Producto \n");
    printf("\t6: Actualizar Precio \n");
    printf("\t7: Baja L%cgica Producto \n", 162);
    printf("\t8: Baja F%csica \n", 161);
    printf("\t0: Finalizar \n");
}
void printTipo(){
    printf("\n\n--------------- TIPO ---------------\n");
    printf("\tIngrese A: Autos \n");
    printf("\tIngrese S: Suv \n");
    printf("\tIngrese P: Pick Up \n");
    printf("\tIngrese U: Utilitarios \n");
}
void printListar(){
    printf("\n\n------------------- LISTAR -------------------\n");
    printf("\tIngrese 1: Listar Todo \n");
    printf("\tIngrese 2: Listar Activos \n");
    printf("\tIngrese 3: Listar por Estado \n");
    printf("\tIngrese 4: Listar por mes de Ingreso \n");
}
void printModificar(){
    printf("\n\n------------------- Modificar -------------------\n");
    printf("\tIngrese 1: Tipo \n");
    printf("\tIngrese 2: Precio \n");
    printf("\tIngrese 3: Kilometraje \n");
    printf("\tIngrese 4: Salir \n");
}

