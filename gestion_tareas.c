#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"gestion_tareas.h"


int crear_tarea(){
char tipo[15];
char descripcion[50];
int prioridad;
char identif[30];
char plazo[15]="con_plazo";
 int cont=0;
time_t tiempo;
struct tm *fecha1;
struct tm *fechalocal;

fecha1=malloc(sizeof(struct tm));
printf("Introducir tipo de tarea:\n"); // pedimos los datos de la nueva tarea al usuario
fscanf(stdin,"%s",tipo);
 getchar();
 if(strcmp(tipo,plazo)==0){ // se compara el tipo introducido para pedir la fecha de terminacion
printf("Introducir la fecha de terminación de la tarea(dd/mm/aaaa:hh:mm):\n");
 fscanf(stdin,"%i/0%i/%i:%i:%i",&fecha1->tm_mday,&fecha1->tm_mon,&fecha1->tm_year,&fecha1->tm_hour,&fecha1->tm_min);
 getchar();
 fecha1->tm_mon=(fecha1->tm_mon-1);
 fecha1->tm_year=fecha1->tm_year-1900;
 tiempo=time(NULL);
 fechalocal=localtime(&tiempo);// esto nos da la fecha y hora local
 strftime(identif,30,"%d/%m/%Y:%H:%M",fecha1);
 if(((fecha1->tm_year*365)+(fecha1->tm_mon*28)+fecha1->tm_mday)<=((fechalocal->tm_year*365)+(fechalocal->tm_mon*28)+fechalocal->tm_mday)){
   cont=1;}
 }
printf("Introducir la descripcion de la tarea:\n");
 fgets(descripcion,50,stdin);
printf("Introducir prioridad:\n");
fscanf(stdin,"%i",&prioridad);
 getchar();
 if(cont==1){
  printf("\nAVISO:la fecha debe ser posterior a la actual\n");
  printf("\nPulsa ENTER para salir al menu principal\n");
  scanf("%*C");
  free(fecha1);
 
  return 0;
	  }

 free(fecha1);

return 0;
}
Tarea *liberar(Tarea *cabecera){// se recorre la lista mientras haya nodos para liberar el espacio en memoria
Tarea *auxiliar;
while(cabecera!=NULL){
auxiliar=cabecera;
cabecera=cabecera->prox;
free(auxiliar);
}
return NULL;
}
int valor_identif_num(){// esta funcion saca un identificador numerico aleatorio para la lista del 0 al 21.
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
