#include<stdio.h>
#include<stdlib.h>
#include"gestion_tareas.h"

int valor_identif_num();

int crear_tarea(){
typedef struct{
  char tipo[10];
  int identif_num;
  char descripcion[50];
  char propietario[20];
  int prioridad;
  char estado[15];
}tarea;
 
  FILE*tareas;

 
  if((tareas=fopen("tareas.txt","a"))==NULL){
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
  fprintf(tareas,"\t%i\n",nueva.prioridad);
  nueva.propietario[20]=identif[20];
  fprintf(tareas,"\t%s\n",&nueva.propietario[20]);
  fprintf(tareas,"\tpendiente\n",nueva.estado[15]);
  nueva.identif_num=valor_identif_num();
  fprintf(tareas,"\t%i\n",nueva.identif_num);


  fclose(tareas);
  return 0;
}

int valor_identif_num(){
srand(time(NULL));
return rand()%21;
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
