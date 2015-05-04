#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"gestion_tareas.h"
#include"pantalla.h"


Tarea *crear_tarea(char propietario[20], Tarea *cabecera){
char tipo[50];
char descripcion[50];
int prioridad;
 char identif[50],*auxi,identif2[50];
char plazo[15]="con_plazo";
int cont=0,a,d,m;
time_t tiempo;
struct tm *fechalocal;
Tarea *auxiliar, *nuevo;

printf("Introducir tipo de tarea:\n"); // pedimos los datos de la nueva tarea al usuario
 fgets(tipo,50,stdin);
 auxi=strtok(tipo,"\n");
 if(strcmp(tipo,plazo)==0){ // se compara el tipo introducido para pedir la fecha de terminacion
printf("Introducir la fecha de terminación de la tarea(dd/mm/aaaa:hh:mm):\n");
 fgets(identif,50,stdin);
 strcpy(identif2,identif);
     auxi=strtok(identif2,"/");
     d=atoi(auxi);
     auxi=strtok(NULL, "/");
     m=atoi(auxi);
     auxi=strtok(NULL, ":");
     a=atoi(auxi);
 tiempo=time(NULL);
 fechalocal=localtime(&tiempo);
 if((((a-1900)*365)+((m-1)*28)+d)<=((fechalocal->tm_year*365)+(fechalocal->tm_mon*28)+fechalocal->tm_mday)){
   cont=1;}
 }
 else{
   strcpy(identif,"-\n");}
printf("Introducir la descripcion de la tarea:\n");
 fgets(descripcion,50,stdin);
printf("Introducir prioridad:\n");
fscanf(stdin,"%i",&prioridad);
 getchar();
 if(cont==1){
  printf("\nAVISO:la fecha debe ser posterior a la actual\n");
  printf("\nPulsa ENTER para salir al menu principal\n");
  scanf("%*C");
 
 
  return cabecera;
	  }

nuevo= malloc(sizeof(Tarea));
strcpy(nuevo->tipo, tipo);
nuevo->identif_num=valor_identif_num();
strcpy(nuevo->descripcion, descripcion);
strcpy(nuevo->propietario, propietario);
nuevo->prioridad=prioridad;
strcpy(nuevo->estado,"pendiente\n");
strcpy(nuevo->fecha, identif);

if(cabecera== NULL){
cabecera=nuevo;
}
else{
auxiliar=nuevo;
auxiliar->prox=cabecera;
cabecera=auxiliar;
 }


return cabecera;
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
int ver_tarea(Tarea *cabecera,char propietario[20]){
int identif_num,a,d,m,diferencia,cont=0;
char fecha[20];
char *auxi,*auxi2;
time_t tiempo;
struct tm *fechalocal;
Tarea *auxiliar;
auxiliar=cabecera;
tiempo=time(NULL);
fechalocal=localtime(&tiempo);
printf("\nIntroducir el identificador de la tarea.\n");
fscanf(stdin,"%i",&identif_num);
 getchar();
 while(auxiliar){
   auxi2=strtok(auxiliar->propietario,"\n");
   if(auxiliar->identif_num==identif_num){
   if(strcmp(auxi2,propietario)==0){
     printf( "DESCRIPCION: %s",auxiliar->descripcion);
     printf( "PRIORIDAD: %i\n",auxiliar->prioridad);
     printf( "TIPO: %s\n",auxiliar->tipo);
     printf( "PLAZO: %s\n",auxiliar->fecha);
     strcpy(fecha,auxiliar->fecha);
     auxi=strtok(fecha,"/");
     d=atoi(auxi);
     auxi=strtok(NULL, "/");
     m=atoi(auxi);
     auxi=strtok(NULL, ":");
     a=atoi(auxi);
     diferencia=((a-1900)*365+((m-1)*28)+d)-(fechalocal->tm_year*365+fechalocal->tm_mon*28+fechalocal->tm_mday);
     printf("DIAS PARA TERMINAR LA TAREA: %i\n", diferencia);
     cont=0;
     break;
    }
   else{
     cont=2;}
   break;
   }
   else{
     cont=1;
   }
   
   auxiliar=auxiliar->prox;
 }
 if(cont!=0){
     if(cont==2){
       printf("\nAVISO:Operacion no permitida sobre esta tarea\n");}
     if(cont==1){
       printf("\nAVISO:Tarea no existente\n");}
     printf("\nPulsa ENTER para salir al menu principal\n");
     scanf("%*C");
     return 0;}
 
 return 0;
}
int listar_tarea(Tarea**punt){
  opciones1();

 Tarea *auxiliar; 
      int i;
 
      i=0;
      auxiliar=*punt;
      printf("\nMostrando la lista completa:\n");
      while (auxiliar!=NULL) {
            printf( "TIPO: %s",auxiliar->tipo);
	    printf( "DESCRIPCION: %s",auxiliar->descripcion);
	    printf( "PROPIETARIO: %s",auxiliar->propietario);
	    printf( "PRIORIDAD: %i\n",auxiliar->prioridad);
	    printf( "FECHA: %s",auxiliar->fecha);
            auxiliar = auxiliar->prox;
            i++;
      }
      if (i==0) printf( "\nLa lista está vacía\n" );
 
 
return 0;
}

Tarea *cargar_tareas(Tarea *inicio){
  char cadena[50];
int numero;
int primer_lista=1; 
int tareas_cargadas=0; 
Tarea *cabecera= NULL, *auxiliar; 
FILE *tareas; 
if((tareas=fopen("tareas.txt","r"))==NULL){
printf("ERROR: no se puede abrir el fichero");
exit(1);
}

while(!feof(tareas)){ 
if(primer_lista== 1){
cabecera= malloc(sizeof(Tarea));
if(cabecera== NULL){
printf("\n\vNo se ha podido reservar memoria para el nodo.\n\v");
exit(1);
} 
fgets(cadena, 50, tareas);
strcpy(cabecera->tipo,cadena); 
fgets(cadena, 50, tareas);
numero=atoi(cadena);
cabecera->identif_num=numero; 
fgets(cadena, 50, tareas);
strcpy(cabecera->descripcion,cadena);
fgets(cadena, 50, tareas);
strcpy(cabecera->propietario,cadena);
fgets(cadena, 50, tareas);
numero=atoi(cadena);
cabecera->prioridad=numero;
fgets(cadena, 50, tareas);
strcpy(cabecera->estado,cadena);
fgets(cadena, 50, tareas);
strcpy(cabecera->fecha,cadena);
fgets(cadena, 50, tareas);
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
printf("\n\vNo se ha podido reservar memoria para el nodo.\n\v");
exit(1);
} 
auxiliar=auxiliar->prox;
fgets(cadena, 50, tareas);
strcpy(auxiliar->tipo,cadena); 
fgets(cadena, 50, tareas);
numero=atoi(cadena);
auxiliar->identif_num=numero; 
fgets(cadena, 50, tareas);
strcpy(auxiliar->descripcion,cadena);
fgets(cadena, 50, tareas);
strcpy(auxiliar->propietario,cadena);
fgets(cadena, 50, tareas);
numero=atoi(cadena);
auxiliar->prioridad=numero;
fgets(cadena, 50, tareas);
strcpy(auxiliar->estado,cadena);
fgets(cadena, 50, tareas);
strcpy(auxiliar->fecha,cadena);
fgets(cadena, 50, tareas); 
auxiliar->prox= NULL; 
tareas_cargadas++; 
if(feof(tareas)){
  break; }
 }
fclose(tareas);
inicio= cabecera;
return inicio;
}

int almacenarfichero(Tarea *cabecera){
Tarea *auxiliar; 
FILE *tareas;
if((tareas=fopen("tareas.txt","w"))==NULL){
printf("ERROR: no se puede abrir el fichero");
exit(1);
}
if(cabecera== NULL){ 
return 0;
}
auxiliar=cabecera; 
while(auxiliar){
fputs(auxiliar->tipo,tareas);
fprintf(tareas,"%i\n",auxiliar->identif_num);
fputs(auxiliar->descripcion,tareas);
fputs(auxiliar->propietario,tareas);
fprintf(tareas,"%i\n",auxiliar->prioridad);
fputs(auxiliar->estado,tareas);
fputs(auxiliar->fecha,tareas);
if(auxiliar->prox!= NULL){ fprintf(tareas, "*\n");
}
auxiliar=auxiliar->prox;
}
return 0; 
} 

