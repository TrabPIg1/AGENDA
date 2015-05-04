#include<stdio.h>
#include<string.h>
#include"pantalla.h"

void caracteres(int L, char C, int E){
  int i,n;
  if(E<Max){
    for(n=0;n<L;n++){
    for(i=0;i<E;i++){
      printf("%c",C);
      }
    printf("\n");
   }}
  else{
    for(n=0;n<L;n++){
    for(i=0;i<Max;i++){
      printf("%c",C);
      }
    printf("\n");
   }}


   return;

}

int confir(char mens[])
{
  char letra;
  printf("\n%s\n",mens);
  scanf("%c",&letra);
  getchar();
  switch(letra){
  case 's':
    printf("\nHas seleccionado \"Si\".\n");
    return 1;
    break;
  case 'S':    
    printf("\nHas seleccionado \"Si\".\n");
    return 1;
    break;
  case 'n':
    printf("\nHas seleccionado \"No\".\n");
    return 0;
    break;
  case 'N':
    printf("\nHas seleccionado \"No\".\n");
    return 0;
    break;
  default:
    printf("\nNo has seleccionado una opcion valida.Por defecto se regresa al menu principal\n");
    return -1;
    break;
    }
  

}


int texto(char C, int E, char mens[])
{
  int j,tam;
  tam=strlen(mens);
  if(E<Max){
  for(j=0;j<(E/2)-tam/2;j++){
    printf("%c",C);}
  printf("%s",mens);
  for(j=0;j<(E/2)-tam/2;j++){
    printf("%c",C);}
  printf("\n");
  }
  else{
  for(j=0;j<(Max/2)-tam/2;j++){
    printf("%c",C);}
  printf("%s",mens);
  for(j=0;j<(Max/2)-tam/2;j++){
    printf("%c",C);}
  printf("\n");
  }
  if((E/2)-tam/2>0){
    return 1;}
  else{ return 0;}
}

void opciones(){
 printf("\n1)\t Crear tarea\n");
  printf("2)\t Eliminar tarea\n");
  printf("3)\t Ver tarea\n");
  printf("4)\t Ver lista tareas\n");
  printf("0)\t Salir\n");
  printf("¿Siguiente operacion?\n");
  return;
}

void opciones1(){
 printf("\n1)\t Pendientes\n");
  printf("2)\t Terminadas\n");
  printf("3)\t Todas\n");
  printf("0)\t Cancelar\n");
  printf("¿Tareas a presentar?\n");
  return;
}

void opciones2(){
 printf("\n1)\t Por pantalla\n");
  printf("2)\t A fichero\n");
  printf("0)\t Cancelar\n");
  printf("¿Presentacion de resultado?\n");
  return;
}

void opciones3(){
 printf("\n1)\t Guardar cambios\n");
  printf("2)\t Descartar cambios\n");
  printf("0)\t Cancelar\n");
  printf("¿Opcion?\n");
  return;
}


