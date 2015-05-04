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
Tarea *cabecera;
caracteres(3,'*',80);
texto('*',80," GESTOR DE TAREAS DE UNA AGENDA ");
caracteres(3,'*',80);
cabecera=cargar_tareas(cabecera);
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
cabecera=crear_tarea(identif,cabecera);
break;
case '2':
A++;
eliminar_tarea();
break;
case '3':
ver_tarea(cabecera,identif);
break;
case '4':
listar_tarea(&cabecera);
break;
case '0':
  almacenarfichero(cabecera);
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
