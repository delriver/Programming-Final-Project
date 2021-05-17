/****************************************************************
@Nombre: practicaFinal.c
@Descripción: Programa que a partir de un archivo de texto externo, cuenta los caracteres y lineas a petición del usuario.
@Entrada: Archivo de texto (.csv en este caso)
@Salida: Numero de caracteres, numero de filas, o fila mas larga a petición del usuario.
@Fecha: 29 de Abril de 2021
@Autor: Pablo Castro del Río
@Versión: v1.0 - Menú con tres opciones + Salida
          v1.1 - Añadir opción a menú de añadir nueva fila
****************************************************************/

/*Parámetros del preprocesador*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


#define num_Opciones 4

/*Definición de funciones*/
int solicitarOpcionMenu();
void seleccionarOpcion(int);
int contarCaracteres(FILE *);
int numeroTotalFilas(FILE *);
int filaMasLarga(FILE *);
bool validarEntero(int, int, int);
bool validarReal(float, float, float);
int menuTerritorios();
int menuEstaciones();
int menuMes();
int pedirDatosEnteros(int, int);
float pedirDatosReales(float, float);
void addFila(FILE *);

/*Función principal*/
int main(){
  int i = 1;
  while(i == 1){
    solicitarOpcionMenu();
  }

  return 0;
}

/*Descripción de funciones*/

/****************************************************************
@Nombre: solicitarOpcionMenu
@Descripción: Imprime por pantalla el menú con las diferentes opciones y pide que elijas a la que quieres acceder
@Entrada: -
@Salida: -
@Fecha: 29 de Abril de 2021
@Autor: Pablo Castro del Río
@Versión: v1.0 - Menú con tres opciones + salir
          v1.1 - Añadir opción 4 (Añadir nueva fila)
****************************************************************/
int solicitarOpcionMenu(){
  int nOpcion;
  bool validacion = false;

  //Menú
  printf("\n*****************************************************************");
  printf("\n1. Número total de caracteres\n2. Número total de filas\n3. Fila más larga\n4. Añadir fila\n0. Salir");
  printf("\n*****************************************************************");

  //Petición del número para acceder a la opción solicitada y comprobación
  printf("\n\nPon la que opcion a la que quieres acceder segun su numero (Entre 0 y %d): ", num_Opciones);
  while(validacion == false){
    scanf("\n%d", &nOpcion);
    validacion = validarReal(nOpcion, 0, num_Opciones);
  }

  seleccionarOpcion(nOpcion); //LLamada a la opción seleccionada
  return 0;
}


/****************************************************************
@Nombre: seleccionarOpcion
@Descripción: Función que recibe la opción que queremos usar, abre el archivo, llama a la función correspondiente, y al terminar esta cierra el archivo
@Entrada: Número entero (Opción seleccionada)
@Salida: Archivo abierto
@Fecha: 29 de Abril de 2021
@Autor: Pablo Castro del Río
@Versión: v1.0
****************************************************************/
void seleccionarOpcion(int a){
  switch (a){
    case 1: //Opción 1, contar el número de caracteres
      printf("\nHas elegido la opcion 1:\n");
      FILE *t;
      t = fopen("ValoresClimatologicosFINAL.csv", "r");

      if (t == NULL){
        printf("\nNo se ha podido abrir el archivo");
      }else{
        contarCaracteres(t);
        fclose(t);
      }
      break;

    case 2: //Opción 2, contar el número de filas
      printf("\nHas elegido la opcion 2:\n");
      FILE *h;
      h = fopen("ValoresClimatologicosFINAL.csv", "r");

      if (h == NULL){
        printf("\nNo se ha podido abrir el archivo");
      }else{
        numeroTotalFilas(h);
        fclose(h);
      }
      break;

    case 3: //Opción 3, dar la fila más larga
      printf("\nHas elegido la opcion 3:\n");
      FILE *j;
      j = fopen("ValoresClimatologicosFINAL.csv", "r");

      if (j == NULL){
        printf("\nNo se ha podido abrir el archivo");
      }else{
        filaMasLarga(j);
        fclose(j);
      }
      break;

    case 4: //Opción 4, añadir una fila
      printf("\nHas elegido la opcion 4:\n");
      FILE *p;
      p = fopen("ValoresClimatologicosFINAL.csv", "a");

      if (p == NULL){
        printf("\nNo se ha podido abrir el archivo");
      }else{
        addFila(p);
        fclose(p);
      }
      break;

    case 0: //Opción para salir
      printf("\nFinalizando programa\n");
      exit(-1);
      break;
  }
}


/****************************************************************
@Nombre: contarCaracteres
@Descripción: Función que cuenta el numero de caracteres del archivo
@Entrada: Archivo abierto para contar carácteres
@Salida: Numero de carácteres
@Fecha: 29 de Abril de 2021
@Autor: Pablo Castro del Río
@Version: v1.0
****************************************************************/
int contarCaracteres(FILE *f){
  int contador = 0;
  char caracter;

  caracter = fgetc(f);

  while(!feof(f)){
    if(caracter != '\n'){
      ++contador;
    }
    caracter = fgetc(f);
  }
  printf("\nEl número total de caracteres es: %d", contador);

  return contador;
}


/****************************************************************
@Nombre: numeroTotalFilas
@Descripción: Función que cuenta el numero total de filas del archivo
@Entrada: Archivo abierto
@Salida: El número total de filas
@Fecha: 29 de Abril de 2021
@Autor: Pablo Castro del Río
@Version: v1.0
****************************************************************/
int numeroTotalFilas(FILE *f){
  int contador = 0;
  char caracter;

  while(!feof(f)){
    caracter = fgetc(f);

    if(caracter == '\n'){
      ++contador;
    }
  }
  printf("\nEl numero total de filas es: %d", contador);

  return contador;
}


/****************************************************************
@Nombre: filaMasLarga
@Descripción: Función que cuenta el numero de caracteres de cada fila y dice cual es la más larga
@Entrada: Archivo abierto
@Salida: El número de la fila más larga
@Fecha: 29 de Abril de 2021
@Autor: Pablo Castro del Río
@Version: v1.0
****************************************************************/
int filaMasLarga(FILE *f){
  int contadorF1 = 0;
  int contadorF2 = 0;
  int filaLarga = 0;
  int filaActual = 0;
  char caracter;

  filaActual = 1;
  caracter = fgetc(f);

  while(!feof(f)){
    ++contadorF2;
    caracter = fgetc(f);

    if (caracter == '\n'){
      if (contadorF2 > contadorF1){
        contadorF1 = contadorF2;
        contadorF2 = 0;
        filaLarga = filaActual;
      }
      filaActual += 1;
    }
  }
  printf("\nLa fila más larga es la fila %d, con %d caracteres", filaLarga, contadorF1);

  return filaLarga;
}

/****************************************************************
@Nombre: validarEntero
@Descripción: Función que valida un numero entero dentro de un rango dado
@Entrada: Numero entero a validar, así como dos más para validar el rango.
@Salida: Verdadero en caso de que el entero estea dentro del rango, falso en caso contrario
@Fecha: 06 de Mayo de 2021
@Autor: Pablo Castro del Río
@Version: v1.0
****************************************************************/
bool validarEntero(int a, int b, int c){
  if(a >= b && a <= c){
    return true;
  }else{
    printf("\nEl valor indicado no es correcto");
    return false;
  }
}

/****************************************************************
@Nombre: validarReal
@Descripción: Función que valida un numero real dentro de un rango dado
@Entrada: Numero real a validar, así como dos más para validar el rango.
@Salida: Verdadero en caso de que sea un numero real y estea dentro del rango, falso en caso contrario
@Fecha: 06 de Mayo de 2021
@Autor: Pablo Castro del Río
@Version: v1.0
****************************************************************/
bool validarReal(float a, float b, float c){
  if(a >= b && a <= c){
    return true;
  }else{
    printf("\nEl valor indicado no es correcto");
    return false;
  }
}

/****************************************************************
@Nombre: menuTerritorios
@Descripción: Muestra un menú con las 3 comunidades autónomas y pide un número entero para seleccionar una de las opciones
@Entrada: -
@Salida: Número de la comunidad elegida
@Fecha: 06 de Mayo de 2021
@Autor: Pablo Castro del Río
@Version: v1.0
****************************************************************/

int menuTerritorios(){
  int numComunidad;
  bool validar = false;

  printf("\n*****************************************************************");
  printf("\n1. Comunidad Valenciana\n2. Castilla y Leon\n3. Comunidad de Madrid");
  printf("\n*****************************************************************");
  printf("\n\nPon la que opcion a la que quieres acceder segun su numero: ");

  while(validar == false){
    scanf("%d", &numComunidad);
    validar = validarEntero(numComunidad, 1, 3);
  }

  return numComunidad;

}

/****************************************************************
@Nombre: menuEstaciones
@Descripción:
@Entrada: -
@Salida: Número de la estación elegida
@Fecha: 06 de Mayo de 2021
@Autor: Pablo Castro del Río
@Version: v1.0
****************************************************************/

int menuEstaciones(){
  int numEstacion;
  bool validar = false;

  printf("\n*****************************************************************");
  printf("\n1. Valencia\n2. Elche aeropuerto\n3. Castellón\n4. Ávila\n5. Burgos aeropuerto\n6. León\n7. Ponferrada\n8. Salamanca aeropuerto\n9. Segovia\n10. Soria\n11. Valladolid\n12. Valladolid aeropuerto\n13. Zamora\n14. Colmenar Viejo\n15. Getafe\n16. Madrid Cuatro Vientos\n17. Madrid Retiro\n18. Madrid Aeropuerto\n19. Puerto de Navacerrada\n20. Torrejón de Ardoz");
  printf("\n*****************************************************************");
  printf("\n\nPon la que opcion a la que quieres acceder segun su numero: ");

  while(validar == false){
    scanf("%d", &numEstacion);
    validar = validarEntero(numEstacion, 1, 20);
  }



  return numEstacion;

}

/****************************************************************
@Nombre: menuMes
@Descripción:
@Entrada: -
@Salida: Número del mes elegido
@Fecha: 06 de Mayo de 2021
@Autor: Pablo Castro del Río
@Version: v1.0
****************************************************************/

int menuMes(){
  int numMes;
  bool validar = false;

  printf("\n*****************************************************************");
  printf("\n1.Enero\n2.Febrero\n3.Marzo\n4.Abril\n5.Mayo\n6.Junio\n7.Julio\n8.Agosto\n9.Septiembre\n10. Octubre\n11.Noviembre\n12.Diciembre");
  printf("\n*****************************************************************");
  printf("\n\nPon la que opcion a la que quieres acceder segun su numero: ");

  while(validar == false){
    scanf("%d", &numMes);
    validar = validarEntero(numMes, 1, 12);
  }



  return numMes;

}

/****************************************************************
@Nombre: pedirDatosEnteros
@Descripción: Función que pide datos numericos (enteros) para el addFila
@Entrada: Recibe el string sobre el dato que va a preguntar, así como los valores del rango de enteros (para realizar la validación)
@Salida: Dato pedido
@Fecha: 12 de Mayo de 2021
@Autor: Pablo Castro del Río
@Version: v1.0
****************************************************************/

int pedirDatosEnteros(int a, int b){
  int dato;
  bool validar = false;

  while(validar == false){
    scanf("%d", &dato);
    validar = validarEntero(dato, a, b);
  }

  return dato;
}

/****************************************************************
@Nombre: pedirDatosReales
@Descripción: Función que pide datos numericos (reales) para el addFila
@Entrada: Recibe el string sobre el dato que va a preguntar, así como los valores del rango de enteros (para realizar la validación)
@Salida: Dato pedido
@Fecha: 12 de Mayo de 2021
@Autor: Pablo Castro del Río
@Version: v1.0
****************************************************************/

float pedirDatosReales(float a, float b){
  float dato;
  bool validar = false;

  while(validar == false){
    scanf("%f", &dato);
    validar = validarReal(dato, a, b);
  }

  return dato;
}

/****************************************************************
@Nombre: addFila
@Descripción: Función para añadir un fila con todos los datos correspondientes, los cuales pide
@Entrada: Fichero al que añadir la fila
@Salida: Fila añadida al fichero con todos los datos (tanto númericos como tipo string)
@Fecha: 13 de Mayo de 2021
@Autor: Pablo Castro del Río
@Version: v1.0
****************************************************************/

void addFila(FILE *f){
  int nTerritorio;
  int nEstacion;
  int nMes;

  nTerritorio = menuTerritorios();
  nEstacion = menuEstaciones();
  nMes = menuMes();

  char territorio [30];
  char estacion [30];
  char mes [30];

  switch(nTerritorio){
    case 1:
      strcpy(territorio, "Comunidad valenciana");
      break;
    case 2:
      strcpy(territorio, "Castilla y León");
      break;
    case 3:
      strcpy(territorio, "Comunidad de Madrid");
      break;
   }

   switch(nEstacion){
     case 1:
       strcpy(estacion, "Valencia");
       break;
     case 2:
       strcpy(estacion, "Elche aeropuerto");
       break;
     case 3:
       strcpy(estacion, "Castellón");
       break;
     case 4:
       strcpy(estacion, "Ávila");
       break;
     case 5:
       strcpy(estacion, "Burgos aeropuerto");
       break;
     case 6:
       strcpy(estacion, "León");
       break;
     case 7:
       strcpy(estacion, "Ponferrada");
       break;
     case 8:
       strcpy(estacion, "Salamanca aeropuerto");
       break;
     case 9:
       strcpy(estacion, "Segovia");
       break;
     case 10:
       strcpy(estacion, "Soria");
       break;
     case 11:
       strcpy(estacion, "Valladolid");
       break;
     case 12:
       strcpy(estacion, "Valladolid aeropuerto");
       break;
     case 13:
       strcpy(estacion, "Zamora");
       break;
     case 14:
       strcpy(estacion, "Colmenar Viejo");
       break;
     case 15:
       strcpy(estacion, "Getafe");
       break;
     case 16:
       strcpy(estacion, "Madrid Cuatro Vientos");
       break;
     case 17:
       strcpy(estacion, "Madrid Retiro");
       break;
     case 18:
       strcpy(estacion, "Madrid aeropuerto");
       break;
     case 19:
       strcpy(estacion, "Puerto de Navacerrada");
       break;
     case 20:
       strcpy(estacion, "Torrejón de Ardoz");
       break;
   }

   switch(nMes){
     case 1:
       strcpy(mes, "Enero");
       break;
     case 2:
       strcpy(mes, "Febrero");
       break;
     case 3:
       strcpy(mes, "Marzo");
       break;
     case 4:
       strcpy(mes, "Abril");
       break;
     case 5:
       strcpy(mes, "Mayo");
       break;
     case 6:
       strcpy(mes, "Junio");
       break;
     case 7:
       strcpy(mes, "Julio");
       break;
     case 8:
       strcpy(mes, "Agosto");
       break;
     case 9:
       strcpy(mes, "Septiembre");
       break;
     case 10:
       strcpy(mes, "Octubre");
       break;
     case 11:
       strcpy(mes, "Noviembre");
       break;
     case 12:
       strcpy(mes, "Diciembre");
       break;
   }

  printf("Temperatura media mensual/anual (ºC): ");
  float temperatura = pedirDatosReales(-20,50);
  printf("Media mensual/anual de las temperaturas máximas diarias (°C): ");
  float tempMaxima = pedirDatosReales(-20,50);
  printf("Media mensual/anual de las temperaturas mínimas diarias (°C): ");
  float tempMinima = pedirDatosReales(-20,50);
  printf("Precipitación mensual/anual media (mm): ");
  int precipitacion = pedirDatosEnteros(0,300);
  printf("Humedad relativa media (%%): ");
  int humedad = pedirDatosEnteros(0,100);
  printf("Número medio mensual/anual de días de precipitación superior o igual a 1 mm: ");
  float mediaPrecipitacion = pedirDatosReales(0,366);
  printf("Número medio mensual/anual de días de nieve: ");
  float nieve = pedirDatosReales(0,366);
  printf("Número medio mensual/anual de días de tempestad: ");
  float tempestad = pedirDatosReales(0,20);
  printf("Número medio mensual/anual de días de niebla: ");
  float niebla = pedirDatosReales(0,30);
  printf("Número medio mensual/anual de días de helada: ");
  float helada = pedirDatosReales(0, 50);
  printf("Número medio mensual/anual de días con datos “vacíos”: ");
  float sinDatos = pedirDatosReales(0,50);
  printf("Número medio mensual/anual de horas de sol: ");
  float sol = pedirDatosReales(0,250);

  fprintf(f, "%s,%s,%s,%.1f,%.1f,%.1f,%i,%i,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n", territorio,estacion,mes,temperatura,tempMaxima,tempMinima,precipitacion,humedad,mediaPrecipitacion,nieve,tempestad,niebla,sinDatos,sol);
}
