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
  tarea prueba;
  printf("Tipo de tarea:");
  scanf("%s",&prueba.tipo[10]);
  getchar();
  fprintf(tareas,"\t%s\n",&prueba.tipo[10]);


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
