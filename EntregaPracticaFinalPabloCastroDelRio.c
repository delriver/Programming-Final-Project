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

#define num_Opciones 4

/*Definición de funciones*/
int solicitarOpcionMenu();
void seleccionarOpcion(int);
int contarCaracteres(FILE *);
int numeroTotalFilas(FILE *);
int filaMasLarga(FILE *);
bool validarOpcionMenuElegida(char);
//bool validarEntero2(int, int, int, int, char);
//bool validarReal(float, int, float, float, char);
//int menuTerritorios();
//int menuEstaciones();
//int menuMes();

/*Función principal*/
int main(){
  solicitarOpcionMenu();

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
  char nOpcion;
  bool validacion = false;

  //Menú
  printf("\n*****************************************************************");
  printf("\n1. Número total de caracteres\n2. Número total de filas\n3. Fila más larga\n4. Añadir fila\n0. Salir");
  printf("\n*****************************************************************");

  //Petición del número para acceder a la opción solicitada y comprobación
  printf("\n\nPon la que opcion a la que quieres acceder segun su numero (Entre 0 y %d): ", num_Opciones);
  while(validacion == false){
    scanf("\n%c", &nOpcion);
    validacion = validarOpcionMenuElegida(nOpcion);
    if(validacion == false)
      printf("\nOpcion incorrecta, introduce un numero entre 0 y %d: ", num_Opciones);
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
    case '1': //Opción 1, contar el número de caracteres
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

    case '2': //Opción 2, contar el número de filas
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

    case '3': //Opción 3, dar la fila más larga
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

    case '4': //Opción 4, añadir una fila
      printf("\nHas elegido la opcion 4:\n");
      FILE *p;
      p = fopen("ValoresClimatologicosFINAL.csv", "r");

      if (p == NULL){
        printf("\nNo se ha podido abrir el archivo");
      }else{
        addFila(p);
        fclose(p);
      }
      break;

    case '0': //Opción para salir
      printf("\nFinalizando programa\n");
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
@Descripción: Función que recibe un numero y detecta si esta entre 0 y 3
@Entrada: Numero a validar
@Salida: Verdadero o falso
@Fecha: 29 de Abril de 2021
@Autor: Pablo Castro del Río
@Version: v1.0 - Valida 4 opciones
          v.1.1 - Valida 5 opciones
****************************************************************/
bool validarOpcionMenuElegida(char n){
  if (n == '0' || n == '1' || n == '2' || n == '3' || n == '4')
    return true;
  else
    return false;
}

/****************************************************************
@Nombre: addFila
@Descripción: Función que añade una fila pidiendo los datos para rellenar los distintos campos
@Entrada: Archivo abierto para introducir la fila
@Salida: Fila con los datos correspondientes
@Fecha: 04 de Mayo de 2021
@Autor: Pablo Castro del Río
@Version: v1.0
****************************************************************/
void addFila(){

}
