//PROYECTO AGENDA 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"gestion_tareas.h"
#include"pantalla.h"

int main()
{ int A=0,B=1;
  char dato;
  char identif[20];
  caracteres(3,'*',80);
  texto('*',80," GESTOR DE TAREAS DE UNA AGENDA ");
  caracteres(3,'*',80);
  printf("\nIntroduzca su identificador:");
  scanf("%s",identif);
  getchar();

 
    while(dato!='0'||B!=1){
    
	opciones();
	scanf("%c", &dato);
	getchar();
	switch (dato)
	  {
	  case '1':
	    A++;
	    crear_tarea();
	    break;
	  case '2':
	    A++;
	    eliminar_tarea();
	    break;
	  case '3':           
	    ver_tarea();
	    break;
	  case '4':
	    listar_tarea();
	    break;
	  case '0':
      
	    if (A==0){
	      printf("\nHa seleccionado salir.\n");
	      break;}
	    else {
	      B=confir("Se han modificado datos ¿Esta seguro que desea salir? (s/n)");
	    }
	    break;
	  default:
	    printf("\nHas realizado una seleccion no valida.Por defecto se regresa al menu principal\n");
	    break;
	  }
     
    }
    return 0;
}

