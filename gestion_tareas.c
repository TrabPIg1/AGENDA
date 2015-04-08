#include<stdio.h>
#include<stdlib.h>
#include"gestion_tareas.h"



int crear_tarea(){
typedef struct{
  char tipo[10];
  int identificador;
  char descripcion[50];
  char propietario[20];
  int prioridad;
  char estado[];
}tarea;
 
  FILE*tareas;

 
  if((tareas=fopen("tareas.txt","r+"))==NULL){
    printf("ERROR:No se puede abrir el fichero");
    exit(1);
  }
  tarea nueva;
  printf("Introducir el tipo de tarea:");
  scanf("%s",&nueva.tipo[10]);
  getchar();
  fprintf(tareas,"\t%s\n",&nueva.tipo[10]);
  printf("Introducir la descripcion de la tarea:");
  scanf("%s",&nueva.descripcion[50]);
  getchar();
  fprintf(tareas,"\t%s\n",&nueva.descripcion[50]);
  printf("Introducir prioridad:");
  scanf("%i",&nueva.prioridad);
  getchar();
  fprintf(tareas,"\t%i\n",&nueva.prioridad);
  


  fclose(tareas);
  return 0;
}

int eliminar_tarea(){
  printf("\nSe ha seleccionado eliminar una tarea.\n");

  return 0;
}

int ver_tarea(){
  printf("\nSe ha seleccionado ver una tarea.\n");

  return 0;
}

int listar_tarea(){
  printf("\nse ha seleccionado listar una tarea.\n");
  
  return 0;
}
