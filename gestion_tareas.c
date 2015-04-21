#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"gestion_tareas.h"

typedef struct{
  char tipo[10];
  int identif_num;
  char descripcion[50];
  char propietario[20];
  int prioridad;
  char estado[15];
  int fecha;
  struct tarea *prox;
}tarea;

tarea *liberar(tarea*);

int crear_tarea(){

 char identif[20];
 time_t tiempo;
 struct tm *fecha;
 struct tm *fechalocal; 

 tarea *auxiliar=NULL;
 tarea *cabecera=NULL;

 cabecera=malloc(sizeof(tarea));
  auxiliar=malloc(sizeof(tarea));


 printf("Introducir tipo de tarea:");
  scanf("%s\n",&auxiliar->tipo[10]);
  getchar();
  printf("Introducir la descripcion de la tarea:");
  scanf("%s\n",&auxiliar->descripcion[50]);
  getchar();
  printf("Introducir prioridad:");
  scanf("%i\n",&auxiliar->prioridad);
  getchar();
 if(strcmp(auxiliar->tipo,"con_plazo")==0){
    printf("Introduce la fecha de terminación de la tarea(dd/mm/aaaa:hh:mm)");
    scanf("%i/%i/%i:%i:%i",&fecha->tm_mday,&fecha->tm_mon,&fecha->tm_year,&fecha->tm_hour,&fecha->tm_min);
    asctime(fecha);
    tiempo=time(NULL);
    fechalocal=localtime(&tiempo);
    if(fechalocal>fecha)
      printf("ERROR");
    auxiliar->fecha='-';
  }

  auxiliar->identif_num=valor_identif_num();
  auxiliar->prox=&cabecera;

  cabecera=auxiliar;

 FILE*tareas;

  if((tareas=fopen("tareas.txt","a"))==NULL){
    printf("ERROR: no se puede abrir el fichero");
    exit(1);
  }

  auxiliar=cabecera;
  while(auxiliar!=NULL){ // se pasan copian los datos en el fichero
    fputs(&auxiliar->tipo[10],tareas);
    fputs(&auxiliar->descripcion[50],tareas);
    fput(&auxiliar->prioridad,tareas);
    fput(&auxiliar->identif_num,tareas);
    fput(&auxiliar->fecha,tareas);
    &auxiliar=auxiliar->prox;
  }
  cabecera=liberar(cabecera);


  fclose(tareas);
  return 0;
}


tarea *liberar(tarea *cabecera){
 
  tarea *auxiliar;
  while(cabecera!=NULL){
    auxiliar=cabecera;
    &cabecera=cabecera->prox;
    free(auxiliar);
  }
  return NULL;
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
  printf("\nSe ha seleccionado listar una tarea.\n");

  return 0;
}
