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

int cargar_tareas(Tarea**punt){
char tipo[15];
char descripcion[50];
int prioridad;
int primer_lista=1; 
int tareas_cargadas=0; 
int vacio;
Tarea *cabecera= NULL, *auxiliar; 
FILE *tareas; 
if((tareas=fopen("tareas.txt","a"))==NULL){
printf("ERROR: no se puede abrir el fichero");
exit(1);
}
fseek(tareas, 0, SEEK_END); 
if(ftell(tareas) == 0 ){ 
vacio= 0;
}
else{ fseek(tareas, 0, SEEK_SET); 
vacio= 1;
} 
if(vacio==0){
*punt= NULL; 
printf("\n\tAVISO: Fichero de alumnos vacío.\n");
printf("\n\n\tPulsarENTER para mostrar el menú principal: ");
scanf("%*c");
 exit(1);
}
while(!feof(tareas)){ 
if(primer_lista== 1){
cabecera= malloc(sizeof(Tarea));
if(cabecera== NULL){
printf("\nNo se ha podido reservar memoria para el nodo.\n");
exit(1);
} 
fgets(tipo, 15, tareas); 
strcpy(cabecera->tipo,tipo); 
fgets(descripcion, 50, tareas);
strcpy(cabecera->descripcion,descripcion); 
fscanf(tareas,"%i",&prioridad);
cabecera->prioridad=prioridad;
cabecera->prox= NULL; 
tareas_cargadas++; 
if(feof(tareas)){
break; 
}
primer_lista= 0;
auxiliar= cabecera; 
 } 
if(feof(tareas)){ 
break; 
} 
auxiliar->prox= malloc(sizeof(Tarea)); 
if(auxiliar->prox== NULL){
printf("\nNo se ha podido reservar memoria para el nodo.\n");
exit(1);
} 
auxiliar=auxiliar->prox;
fgets(tipo, 15, tareas); 
strcpy(cabecera->tipo,tipo); 
fgets(descripcion, 50, tareas);
strcpy(cabecera->descripcion,descripcion); 
fscanf(tareas,"%i",&prioridad);
cabecera->prioridad=prioridad;
auxiliar->prox= NULL; 
tareas_cargadas++; 
 }
fclose(tareas);
*punt= cabecera;
return tareas_cargadas;
}
