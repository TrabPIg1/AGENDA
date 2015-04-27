#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
// Definición de macros: 
//Establecer atributos en la presentación por la pantalla (x = 1 negrita, x = 7 vídeo inverso). 
#define atributo(x) printf("\x1b[%dm",(x)) 
//Eliminar el atributo o atributos establecidos. 
#define no_atributo( )  printf("\x1b[0m");
/* Declaraciones de lasestructuraspara los alumnosde un Centro Académicoy para susrespectivos expedientesacadémicos. */ 
//Estructura para los nodos de las sublistasde expedientes de los nodos de la listade alumnos. 
struct expediente_academico{ 
char curso[60];  
//Campo que contiene las notas (expediente) de un curso. 
struct expediente_academico *sig;  
//El puntero sigpermitirá crear los siguientes nodos de la sublista. 
}; 
typedef struct expediente_academico t_notas; 
//Estructura para los nodos de la lista de alumnos. 
struct alumno_centro_academico{  
char nombre[30];  
//Campo que contiene el nombre de un alumno. 
char nif[12];  
//Campo que contiene el número de identificación fiscal del alumno. 
struct expediente_academico *expe;  
//El puntero expe permitirá crear el primer nodo de la sublista. 
struct alumno_centro_academico *sig; 
//El puntero sigpermitirá crear los siguientes nodos de la lista. 
}; 
typedef struct alumno_centro_academico t_alum;
//Prototipos de las funciones (declaraciones). 
void menu_principal(char*opcion);  
//Menú principal del programa.  
void menu_salir(char*opcion); 
//Menú que gestiona la opción salir del menú principal del programa. 
int cargar_fich_alumnos(t_alum**punt); 
/* Carga el fichero de alumnos del Centro con sus respectivos expedientes académicos en una lista dinámica. */ 
int almacenar_lista_en_fichero(t_alum*p_inicio); 
/* Almacena la lista dinámica en el fichero de alumnos. */ 
t_alum*matricular_alumno(int*cambio_matricular_alumno, t_alum*p_inicio);      
/* Matricula un alumno: Reservando memoria para un nuevo nodo, cargando dicho nodo con la  información del alumno y enlazando el nuevo nodo a la lista dinámica(en este caso, al final de la lista). */ 
void visualizar_expediente_alumno(t_alum*p_inicio); 
/* Visualiza las notas de cada curso de un alumno. */ 
void visualizar_estadisticos_Centro(int num_expedientes, t_alum*p_inicio); 
//Visualiza determinados estadísticos relacionados con los alumnos de un Centro Académico.
int alumno_graduado(char NIF[20], int *num_aprobados, t_alum *p_inicio); 
/* Indica si un alumno está graduado; si no lo está indica el número de materias que tiene aprobadas. Llamada por las funciones visualizar_expediente_alumnoy visualizar_estadisticos_Centro*/ 
FILE *gfopen(char*nom_fich, char*modo); 
/* Función genérica abrir fichero y determinar error apertura fichero.Llamada por la función cargar_fich_alumnos.*/ 
int fichero_vacio(FILE*pf);  
//Determina si un fichero está vacío. Llamada por la función cargar_fich_alumnos.
 void comprobar_reserva_memoria_lista(t_alum*punt); 
/* Comprueba si la función malloc ha podido reservar memoria para un nodo de la lista dinámica.Llamada por las funciones cargar_fich_alumnosymatricular_alumno.*/ 
void comprobar_reserva_memoria_sublista(t_notas*punt); 
/* Comprueba si la función  mallocha podido reservar memoria para un nodo de la sublistadinámica. Llamada por las funciones cargar_fich_alumnosy matricular_alumno.  */ 
void liberar_memoria_lista(t_alum*punt);  
//Libera la memoria de los nodos de la lista dinámica. 
void liberar_memoria_sublista(t_notas*punt); 
/* Libera la memoria de los nodos de la sublista de cada nodo de la lista dinámica. 
Llamada por la función liberar_memoria_lista*/
int main( ){ 
char opcion; 
int num_expedientes, cambio_matricular_alumno; 
t_alum *p_inicio; 
cargar_fich_alumnos(&p_inicio);  
/* Llamada a la función cargar_fich_alumnos. A la función se le pasa la direccióndel punterop_inicio. La función devuelve el puntero p_inicio. Esta variable puntero contienela dirección del principio de una lista dinámica cargada con los alumnos del Centro Académico almacenados en el fichero de alumnos. IMPORTANTE: cuando se manipula la información de un fichero a través de una lista dinámica se recomienda que las primeras funciones que se implementen sean cargarel fichero en la lista y almacenaresta lista en el fichero. Un vez creada la lista, se pueden implementar las funcionalidades que se deseen para transformaro consultar la información contenida en la lista dinámica. Si ha lugar, el contenido de la lista dinámica, con los cambios realizados por las funcionalidades, se almacenan (se salvan) en el fichero.*/
for( ; ; ){  
//Buclefor idefinido. C establecequeel campo condiciónvacíose evalúaa verdadero. 
menu_principal(&opcion); 
//Llamadaa la funciónmenu_principal. Muestralasopcionesdel menú. 
switch(opcion){ 
case '1': 
  p_inicio= matricular_alumno(&cambio_matricular_alumno, p_inicio); 
/*Llamada a la función matricular_alumno. A la función se le pasan dos parámetros:  el punterop_inicio que apunta al principio de la lista dinámicade alumnos y la dirección de la variable cambio_matricular_alumno. Si la matrícula del alumno se ha realizado con éxito, la función devuelveel valor 1 en la variable cambio_matricular_alumno(el contenido de esta variable se utiliza en la opción salir del menú principal del programa) y retorna ladirección de inicio de la nueva lista con un nuevo nodo añadido. Esta dirección retornada se asigna al punterop_inicio. */ 
break; 
case '2': 
visualizar_expediente_alumno(p_inicio); 
/*Llamada a la función visualizar_expediente_alumnno. A la función se le pasa el punterop_inicioque apunta al principio de la lista dinámicade alumnos. La función solicita por la pantalla que se introduzca el NIF del alumnos cuyo expediente se quiere visualizar. Si el NIFcorresponde con un alumno de la lista dinámica, se visualiza su expediente, sino se visualiza que el NIF no se corresponde con ningún alumno de la lista dinámica . */ 
break;
case '3': visualizar_estadisticos_Centro(p_inicio); 
/*Llamada a la función visualizar_estadisticos_Centro.A la función se le pasa el punterop_inicioque apunta al principio de la lista dinámicade alumnos. La función visualizadeterminados estadísticos relacionados con los alumnos del Centro. */ 
break; 
case '0': 
if(cambio_matricular_alumno){ 
/* Si se ha matriculado al menos un alumno en el Centro, la lista dinámica ha cambiado. La función menu_salirle da al usuario la opción de elegir salir del programa salvando o no estos cambios de la lista dinámica. También le da la opción de elegir volver al menú principal del programa. */ 
menu_salir(&opcion); 
switch(opcion){ 
case '1': //Salir salvando. 
almacenar_lista_en_fichero(p_inicio); 
liberar_memoria_lista(p_inicio); 
system("clear"); 
exit(1);
case '2': //Salirsin salvar. 
system("clear"); 
liberar_memoria_lista(p_inicio); 
exit(1); 
case '0': //Volveral menúprincipal. 
system("clear"); 
break; }
}
else{
//Salir (cubre los casos que solo consultanla lista: visualizar expediente alumno y visualizar estadísticos Centro). 
system("clear"); 
liberar_memoria_lista(p_inicio); 
exit(1); 
} 
break;
} 
} //fin for( ; ; ) 
return 1; 
}  //Fin funciónmain.
/* Definición de la función que muestra el menú principal del programa. Nombre:  menu_principal. Tipo de la función: void. Parámetrosformales: 1. Entrada.Recibeatravésdelpunteroopcionladireccióndeunavariabledetipochar. 2. Salida.Devuelveenladireccióndelpunteroopcionlaopciónelegidaporelusuario. Salida:lafunciónvisualizaporlapantallaennegritalasopcionesdelmenúprincipalquepuedeelegirelusuario.*/ 
void menu_principal(char *opcion){ 
system("clear"); 
atributo(1);  //Establece el atributo negrita en las visualizaciones por la pantalla. 
printf("\n\tCentroAcadémico:\n"); 
printf("\n\t1) Matricular alumno."); 
printf("\n\t2) Visualizar expediente alumno."); 
printf("\n\t3) Visualizar estadísticos Centro."); 
printf("\n\t0) Salir."); 
printf("\n\n\t¿Siguienteoperación?: "); 
scanf(" %c",opcion);
if(!(*opcion>='0' &&*opcion<='3'))
{ 
do{ 
printf("\n\tELECCIÓNINCORRECTA, PULSAR 1, 2, 3o0:"); 
scanf(" %c",opcion); 
}while(!(*opcion>='0' &&*opcion<='3')); 
} no_atributo(); //Elimina el atributo negrita establecido. 
return; 
} //Fin de la función menu_principal.
/* Definición de la función que muestra el menú salir. Nombre:  menu_salir. Tipo de la función: void. Parámetrosformales: 1. Entrada.Recibeatravés delpunteroopcionladireccióndeunavariabledetipochar. 2. Salida.Devuelveenladireccióndelpunteroopcionlaopciónelegidaporelusuario. Salida:Lafunciónmuestraporlapantallaennegritalasopcionesdelmenúsalirquepuedeelegirelusuario.*/ 
void menu_salir(char*opcion){ 
system("clear"); 
atributo(1); 
printf("\n\t1) Guardar cambios"); 
printf("\n\t2) Descartar cambios."); 
printf("\n\t0) Cancelar."); 
printf("\n\n\t¿Siguienteoperación?: "); 
scanf(" %c",opcion);
if(!(*opcion>='0' &&*opcion<= '2')){ 
do{ 
printf("\n\tELECCIÓNINCORRECTA, PULSAR 1, 2 o 0: "); 
scanf(" %c", opcion); 
}while(!(*opcion>='0' &&*opcion<= '2')); 
} 
no_atributo(); 
return; 
} //Fin de la función menu_salir.
/* Definición de la función que matricula un alumno. Nombre:  matricular_alumno. Tipo de la función: puntero t_alum. Parámetrosformales: 1. Entrada. Recibe dos parámetros: la dirección de una variable tipo entero a través del puntero cambio_matricular_alumnoyelpunterop_inicioalprincipiodelalistadinámicadealumnosdelCentro. 2. Salida. Devuelve en la dirección del puntero cambio_matricular_alumno el valor 1 si se ha matriculado el alumno,yelvalor0sinosehapodidomatricular. Retorno de la función: Lafunciónretorna unpuntero p_inicio alprincipiodelanuevacon elnodo delnuevo alumno.*/ 
t_alum*matricular_alumno(int *cambio_matricular_alumno, t_alum*p_inicio){ 
char NOMBRE[62], NIF[20], cad_NIF[20]=" "; 
t_alum *p_aux, *p_nuevo; 
t_notas *p_aux_notas; 
system("clear"); 
scanf("%*c"); //Leer carácter del ENTER y no asignar.
printf("\n\tIntroducirel nombre del nuevo alumno: "); 
fgets(NOMBRE, 60, stdin); 
printf("\n\tIntroducirel NIF: "); 
fscanf(stdin,"%s", NIF); 
strcat(cad_NIF, NIF);  //Concatenarun espacioen blancoal principio del NIF. Necesariopara la comparacióndel if del while. 
p_aux= p_inicio; 
//p_aux: punteroauxiliaral principio de la lista. 
//Comprobarsiel NIF pertenecea un alumnocon expedienteen el Centro. 
while(p_aux){ 
if(strcmp(p_aux->nif, cad_NIF) == 0){ 
printf("\n\n\tAVISO: El NIF introducido pertenecea un alumno con expediente en el Centro.\n"); 
*cambio_matricular_alumno= 0;  
//Valor utilizado en la opción salir del menú principal. 
printf("\n\n\tPulsarENTER para volver al menú principal"); 
scanf("%*c%*c");  //Leer los dos caracteresdel ENTER y no asignarlos. 
return p_inicio; //Se sale de la funciónretornandoel punterop_inicioal principio de la mismalista. 
} 
p_aux=p_aux->sig; 
} //Fin bucle while.
//CRAER UN NODO PARA CARGAR LA INFORMACIÓN DEL NUEVO ALUMNO. 
//Reserva memoria para el nuevo nodo a incorporar a la lista dinámica de alumnos. 
p_nuevo= malloc(sizeof(t_alum)); 
comprobar_reserva_memoria_lista(p_nuevo); 
strcpy(p_nuevo->nombre, NOMBRE);  
//Cargar el nombre del nuevo alumno en el nodo. 
strcpy(p_nuevo->nif, cad_NIF); 
//Cargar el NIF del nuevo alumno en el nodo. 
p_nuevo->sig= NULL; 
/* El nuevo nodo se enlaza al final de la lista. El campo puntero siges el puntero de finalde la lista. Asignarle el punteroNULL hace que lalista finalice apuntado aNULL. */ 
p_nuevo->expe = NULL;
/* Se asigna el puntero NULL al campo puntero expedel nuevo nodo. Este nodo apuntando a NULL indica que el nodo se crea sin la sublistadinámica del expediente del nuevo alumno por ser un alumno deprimera matrícula. IMPORTANTE: el campo puntero expedel nodo es el puntero que se utilizará para reservar memoria para el primer nodo de la sublista. El campo puntero expehace las veces de puntero al principio de la sublista. */
//Enlazar el nodo al final de la lista. 
if(p_inicio== NULL){ 
//Caso particular lista vacía (se carga el primer alumno en la lista de alumnos). 
p_inicio= p_nuevo; 
} 
else{ 
p_aux= p_inicio; 
while(p_aux->sig){ 
p_aux= p_aux->sig; 
//Al terminar el bucle whileel puntero p_auxapunta al último nodo. 
} p_aux->sig= p_nuevo;
 //Enlazar el último nodo de la lista con el nuevo nodo. 
} *cambio_matricular_alumno= 1;  
//Valor utilizado en la opción salir del menú principal. 
return p_inicio; 
//Retorna un puntero al principio de la nuevalista dinámica. 
} //Fin de la función matricular_alumno.
/* Definición de la función que visualiza el expediente de un alumno localizado por su NIF. Nombre: visualizar_expediente_alumno. Tipo de la función: void. Parámetrosformales:Recibeelpunterop_inicioalprincipiodelalistadinámicadealumnosdelCentro. Salida:MuestraporlapantallaelexpedientedeunalumnolocalizadoporsuNIF.SielNIFnocorrespondea ningúnalumno,muestraunmensajeindicándolo.*/ 
void visualizar_expediente_alumno(t_alum*p_inicio){ 
int num_curso=1, num_aprobados=0; 
char NIF[20], cad_NIF[20]=" "; 
t_alum *p_aux; 
t_notas *p_aux_notas; 
system("clear"); //Localizar el alumno por su NIF. 
printf("\n\tIntroducirel NIF del alumno: "); 
fscanf(stdin,"%s", NIF); 
strcpy(cad_NIF, " "); 
strcat(cad_NIF, NIF); 
//Necesarioconcatenarun carácterblancoal principio del NIF.
//Recorrerlalistalocalizandoal alumno.  
p_aux= p_inicio;  //p_auxpunteroauxiliaral principio de lalista. 
while(p_aux){ 
if(strcmp(cad_NIF,p_aux->nif) == 0){ 
break; /* El buclewhileterminacuandose localizaal alumno. Cuandose interrumpeel bucleel punterop_auxapuntaal nodoquecontieneel expedientedel alumno.*/ 
} p_aux= p_aux->sig; 
} //Estudio de la salida del bucle while. 
if(p_aux== NULL){ //Caso particular: se recorre la lista y ningún NIF de alumno coincide con el NIF de búsqueda. 
printf("\n\tNoexiste ningún alumno con el NIF: %s\n", NIF); 
printf("\n\n\tPulsarENTER para volver al menú principal: "); 
scanf("%*c%*c"); //Leer y no asignarlos caracteresdel ENTER. 
return; //Salirde la función. 
}
else{ 
printf("\n\n\t%s",p_aux->nombre); //Visualizar el nombre del alumno. 
if(p_aux->expe == NULL){  //No existesublistade expediente. 
printf("\n\tAlumnode primera matrícula.\n"); 
} 
else{ 
p_aux_notas= p_aux->expe; /* Al punteroauxiliarp_aux_notasse le asignael campo punteroexpedel nodolocalizado. Este punteroauxiliarpermiterecorrerla sublistade expedientes. */ 
while(p_aux_notas){ 
switch(num_curso){ 
case 1: printf("\tprimero:"); 
break; 
case 2: printf("\n\tsegundo:"); 
break;
case 3: printf("\n\ttercero:"); 
break; 
case 4: printf("\n\tcuarto:"); 
break; 
} 
num_curso++; 
printf("%s", p_aux_notas->curso); 
p_aux_notas= p_aux_notas->sig; 
} //Fin bucle whilede la sublistade expedientes.  
if(!alumno_graduado(cad_NIF, &num_aprobados, p_inicio)){ 
printf("\n\n\tElalumno no está Graduado y le faltan %d materias para terminar el Grado.\n", 40 -num_aprobados); 
//Se establece que el número de materias del Grado es 40. 
}
else{ 
printf("\n\n\tElalumno está Graduado.\n");    
}
}
} 
printf("\n\n\tPulsarENTER para volver al menú principal: "); 
scanf("%*c%*c"); 
return; } //Fin de la función visualizar_expediente_alumno.
/* Definición de la función que visualiza estadísticos del Centro Académico. Nombre: visualizar_estadisticos_Centro. Tipo de la función: void. Parámetrosformales:Recibeelpunterop_inicioalprincipiodelalistadinámicadealumnosdelCentro. Salida:MuestraporlapantallaestadísticosdelCentro.*/ 
void visualizar_estadisticos_Centro(t_alum*p_inicio){ 
int num_expedientes=0, num_aprobados, num_alumnos_graduados=0; 
int num_alumnos_primera_matricula=0; 
int num_alumnos_NO_graduados=0; 
t_alum *p_aux; 
system("clear"); //Recorrerla listade alumnos. 
p_aux= p_inicio; 
while(p_aux){ 
if(alumno_graduado(p_aux->nif, &num_aprobados, p_inicio)){ 
/*Se llama repetidamente a la funciónalumno_graduadopasándole los NIF de los alumnos. */ 
num_alumnos_graduados++; 
} 
else{ 
num_alumnos_NO_graduados++; 
}
if(p_aux->expe== NULL){  //Si punteroa sublistade expedientesesNULL =>alumnode primeramatrícula. 
num_alumnos_primera_matricula++; 
} 
num_expedientes++; 
p_aux= p_aux->sig;  //Avanzarel punterop_aux. 
} //Fin del bucle while.
printf("\n\tESTADÍSTICOSDEL CENTRO:"); 
printf("\n\tNúmerode expedientes en el archivo del Cemtro: %d", num_expedientes); 
printf("\n\tNúmerode alumnos que se han graduado en el Centro: %d", num_alumnos_graduados); 
printf("\n\tAlumnosmatriculados en el Centro: %d", num_alumnos_NO_graduados); 
printf("\n\tAlumnosde primera matrícula: %d\n", num_alumnos_primera_matricula); 
printf("\n\n\tPulsarENTER para volver al menú principal: "); 
scanf("%*c%*c"); 
return; } //Fin de la función visualizar_estadisticos_Centro.
/* Definición de la función que determina si un alumno está graduado. Nombre:  alumno_graduado. Tipo de la función: int. Parámetrosformales: 1. Entrada.Recibetresparámetros,unoporvalorydosporreferencia. a) ParámetroporvalorNIF.Através deesteparámetroserecibeelNIFdelalumno. b) Parámetrosporreferencia.Elpunterop_inicioalprincipiodelalistadinámicadealumnosdelCentroyla direccióndeunavariableenteraatravés delparámetronum_aprobados. 2. Salida.Devuelveenladireccióndelpunteronum_aprobadoselnúmerodeaprobados. Retornodelafunción:Retornaelvalor1sielalumnoestágraduadoyelvalor0sinoloestá.*/ 
int alumno_graduado(char NIF[20], int *num_aprobados, t_alum *p_inicio){ 
char *p; //Puntero utilizado para asignarle el puntero retornado por la función strtok. 
char cad[60]; /* Cadena utilizada para evitar que la cadena p_aux_notas->curso sea "desguazada" por la funciónstrtok. */ 
int graduado, cont_aprobados;  /* La variblecont_aprobadosse utiliza para contar el número de asignaturasaprobadas del expediente de un alumno. */
t_alum *p_aux; //Puntero auxiliar para recorrer la listade alumnos. 
t_notas *p_aux_notas; //Puntero auxiliar para recorrer la sublistade expedientes. 
cont_aprobados=0;  //Variable utilizada para contar las materias aprobadas por los alumnos. 
p_aux= p_inicio; 
while(p_aux){  
if(strcmp(p_aux->nif, NIF) == 0){ 
p_aux_notas= p_aux->expe; /* Asigna al puntero auxiliar p_aux_notasla dirección del campo puntero expede un nodode la lista dinámica de alumnos. El puntero auxiliar p_aux_notasse utiliza para recorrer la sublistadinámica de este nodode lalista de alumnos que contiene el expedientedel alumno contenido  en dicho nodo. */
while(p_aux_notas){  //Bucle whilepara recorrer las sublistasde los expedientes de los alumnos. 
strcpy(cad,p_aux_notas->curso); 
p = strtok(cad," \n"); //Primera llamadaa la funciónstrtok. El punteropapuntaa la primera subcadenaextraida. 
if(atof(p) >=5){  //La funciónatofconvierte el contenidode la subcadenaapuntadaporel punteropenun float. 
cont_aprobados++; } 
do{  //Convieneutilizarun do-while para obtenerlassiguientessubcadenas. El punter papuntaa lassucesivassubcadenas. 
p = strtok(NULL, " \n"); 
if(p != NULL){ 
if(atof(p) >=5){ cont_aprobados++; 
} 
} 
}while(p);  //La funciónstrtokdevuelveNULLcuandono quedanmássubcadenasquedevolver. 
p_aux_notas= p_aux_notas->sig; //Avanzar el puntero en lasublistade expedientes. 
}
}
p_aux= p_aux->sig;  //Avanzar el puntero p_auxen la listade alumnos. 
}  //Fin bucle whilelistade alumnos. 
*num_aprobados= cont_aprobados;  /* Asigna en la dirección del puntero num_aprobadosel número de asignaturas aprobadas por el alumno. */ 
if(cont_aprobados== 40){ //Para Plan de Estudios con 40asignaturas (10 asignaturas por curso). 
graduado = 1; 
} 
else{ graduado = 0; 
} 
return graduado; 
} //Fin de la función alumno_graduado.
/* Definición de la función que carga un fichero de textoen una lista dinámica. El fichero a cargar es un fichero de alumnos de un Centro Académico. Nombre: cargar_fich_alumnos. Tipo de la función: int. Parámetrosformales: 1. Entrada.Recibeladireccióndeunpunteroatravés delpunterodoblepunt. 2. Salida. Devuelve a través del puntero doble punt, asignando en la dirección recibida, la dirección de un puntero de tipo t_alum al principio de una lista dinámica que contiene los alumnos del fichero de alumnos delCentro Retorno:retornaelnúmerodealumnoscargadosenlalistadinámica.*/  
int cargar_fich_alumnos(t_alum**punt){ 
  int primer_nodo_lista=1; /* Variable utilizada para crear elprimernodo de lalista de alumnos dentro del whilede lectura delfichero de alumnos. Se elige inicializarla con el valor 1. */ 
int alumnos_cargados=0; //Variable contador de alumnos cargados en la lista. 
char cad[60], *p_cad; //Variables utilizadasporlasfuncionesfgetsy strtok, respectivamente. 
int i; //Variable contadordel buclefor utilizadoen la creaciónde lassublistasde expedientes. 
FILE *pf;  //Declaración puntero a fichero pf. 
t_alum *p_inicio= NULL, *p_aux; //Punteros utilizados en la creación de la lista de alumnos. 
t_notas*p_aux_notas; //Puntero utilizado en la creación de las sublistasde expedientes.
//Abrir el fichero de alumnos para lectura. 
pf = gfopen("fich_alumnos.txt", "r"); /* Llamada a la función gfopenpara abrirel fichero fich_alumnos.txt paralectura. */ 
if(!fichero_vacio(pf)){ 
*punt= NULL;  /* Se asigna en la dirección *puntel puntero NULL. Esto significa que la lista dinámica de alumnos estará vacía. La función matricular_alumnopuede añadir nodos a la lista. */ 
printf("\n\v\tAVISO: Fichero de alumnos vacío.\n"); 
printf("\n\n\tPulsarENTER para mostrar el menú principal: "); 
scanf("%*c"); 
return 0; //Se sale de la función. 
}
while(!feof(pf)){  //Leer del ficheroasociadoal punteropf mientraspf no apunteal final del fichero. 
if(primer_nodo_lista== 1){ 
/* RESERVAR MEMORIA PARA EL PRIMER NODO DE LA LISTA DE ALUMNOS DEL CENTRO Y CARGARLO CON EL NOMBRE Y EL NIFDEL PRIMER ALUMNO DEL FICHERO DE ALUMNOS. */ 
p_inicio= malloc(sizeof(t_alum)); //Reservar memoria para el primer nodo de la lista de alumnos. 
comprobar_reserva_memoria_lista(p_inicio); /* Si la función mallocretorna el puntero NULL, se sale del programa. */ 
fgets(cad, 60, pf); //Leer el nombre del primer alumno. 
strcpy(p_inicio->nombre,cad); //Cargar en la lista el nombre primer alumno. 
fgets(cad, 60, pf); //Leer la línea con el nifdel primer alumno. 
p_cad= strtok(cad,":"); /* Extraer la subcadena"nif" de la cadena que contiene el nifdel alumno.   El puntero p_cadapunta a la subcadena. */ p_cad= strtok(NULL,"\n"); /* extraer la subcadenacon el nifde la cadena que contiene el nif. puntero p_cadapunta a la subcadena). */ 
strcpy(p_inicio->nif,p_cad); //Cargar en la lista el nifdel primer alumno. 
p_inicio->sig= NULL; //Asigna al puntero sigdel nodo el puntero NULL. 
alumnos_cargados++; //Incrementa el contador de alumnos cargados en la lista.
if(feof(pf)){ //Cubre el caso particular de unúnicoalumno en el fichero de alumnosque es de primeramatrícula. Nose debe crear lasublista. 
break; 
//Salir del buclewhilede lectura del fichero dealumnos. 
}      
//Crear la sublistadel expediente del alumno.   
fgets(cad, 60, pf); //Lee la línea del primer curso o el carácter * si el alumnos es deprimera matrícula. 
if(strcmp(cad, "*\n") == 0){ 
p_inicio->expe= NULL; /* Si el carácter leído es el carácter*de separación de alumnos=>el alumno es de primeramatrícula. Al campo puntero expede la lista de alumnos se le asigna el puntero NULL */ 
} 
else{ /*Crear elprimer nodo de la sublistadel expediente académico del alumno y cargarlo con las notas del primer curso. El puntero p_inicio->expe es el puntero al principio de la sublista. */ 
p_inicio->expe= malloc(sizeof(t_notas)); //Reservar memoria para el primer nodo de lasublista. 
comprobar_reserva_memoria_sublista(p_inicio->expe); 
p_inicio->expe->sig= NULL; 
p_cad= strtok(cad,":"); /* Extraer la subcadena"Primero" de la cadena que contiene el primer curso. El puntero p_cadapunta a esta subcadena.*/ 
p_cad= strtok(NULL,"\n"); //Extraer la subcadenade notas de la cadena que contiene el primer curso. 
strcpy(p_inicio->expe->curso, p_cad); /* Cargar el campo curso del primer nodo de la sublistacon las notas de primero.*/ 
p_aux_notas= p_inicio->expe; /* El puntero p_aux_notasapunta al primer nodo de la sublista.  Este puntero auxiliar se utiliza para crear los nuevos nodos de la sublista. */ 
//Crear los siguientes nodos de la sublistay cargarlos con las notas de los correspondientescursos. 
for(i=1; i<=4; i++){ /* Se eligequela variable contadoripuedatomarvaloresde 1 a4 para cubrirla possible lecturade trescursosmásel caráter* de separaciónde alumnos. */ 
fgets(cad, 60, pf); 
if(!feof(pf)){ 
if(strcmp(cad, "*\n") != 0){ /* Si la cadena cadNOcontiene el carácter * de separación entre alumnos. */ 
p_aux_notas->sig= malloc(sizeof(t_notas)); /* Reservar memoria para el nuevo nodo de la sublista. */ 
comprobar_reserva_memoria_sublista(p_aux_notas->sig); 
p_aux_notas= p_aux_notas->sig; //Avanzar el puntero auxiliar al nuevo nodo. 
p_aux_notas->sig= NULL; 
p_cad= strtok(cad,":"); //Extraer la subcadenacon la cabeceradel correspondiente curso.
p_cad= strtok(NULL,"\n"); //extraer la subcadenade notasdel correspondiente curso. 
strcpy(p_aux_notas->curso, p_cad); //Cargar el campo cursodel nodo de la sublista.
} 
else{ 
break; /* Cuando se lee el carácter *deseparación entre alumnos se sale del bucle for. Los nuevos nodos de la sublistase van creando hasta que se lea el carácter *=> pueden crearse de 0a 3 nuevos nodos.*/ 
}
} 
} //Fin del bucle for.
} 
primer_nodo_lista= 0; /* Permite que no se vuelva a ejecutar este segmento de código =>se preserva el puntero p_inicioal principio de la lista de alumnos. */ 
p_aux= p_inicio; /* La asignación hace que el puntero auxiliar p_auxapunte al principio de la lista de alumnos. Este puntero se utiliza para crear los siguientes nodos de la lista. */ 
}  //Fin del bloque de código del ifde creación del primer nodo de la listade alumnos.
if(feof(pf)){ //Caso particularde un único alumno en el fichero de alumnos. Nose deben crear másnodos en la lista de alumnos. 
break; //Salir del bucle whilede lectura del fichero de alumnos. 
}    /* CREAR LOS SIGUIENTES NODOS DE LA LISTA DE ALUMNOS Y CARGARLOS CON LOS NOMBRES Y LOS NIF. PARA CADA NODO SE CREA SU SUBLISTAY SE CARGA CON EL CORRESPONDIENTE EXPEDIENTE .*/ 
p_aux->sig = malloc(sizeof(t_alum)); //Reservarmemoriaparaun nuevonodode la lista. 
comprobar_reserva_memoria_lista(p_aux->sig); p_aux= p_aux->sig;  //Avanzarel punteroauxiliaralnuevonodo. 
fgets(cad, 60, pf); //Leer el nombre del alumno. 
strcpy(p_aux->nombre,cad); //Cargar el nombre del alumno. 
fgets(cad, 60, pf); //Leer la línea que contiene el nifdel alumno. 
p_cad= strtok(cad,":"); /* Extraer la subcadena"nif" de la cadena que contiene el nif. El puntero p_cadapunta a la subcadena. */ 
p_cad= strtok(NULL,"\n"); /* extraer la subcadenacon el nifde la cadena que contiene el nif. El puntero p_cadapunta a la subcadena. */ 
strcpy(p_aux->nif,p_cad); //Cargar elnifdel alumno. 
p_aux->sig= NULL; //Asigna al puntero sigdel nodo el puntero NULL. 
alumnos_cargados++; //Incrementar el contador de alumnos cargados en la lista.
//Crear las sublistasde los nodos de la lista de alumnos. 
fgets(cad, 60, pf); if(!feof(pf)){ //Cubre el caso particular dealumno de primera matrícula al final del fichero. 
if(strcmp(cad, "*\n") == 0){ 
p_aux->expe= NULL; /* Si el carácter leído es el crácter* de separación de alumnos =>el alumno es de primeramatrícula. Al campo puntero expede la lista de alumnos se le asigna el puntero NULL */ 
} 
else{ /*Crear losprimeros nodos de las sublistasde expedientes de los alumnos y cargarloscon las notas de los  primeros cursos.*/ 
p_aux->expe= malloc(sizeof(t_notas)); //Reservar memoria para el primer nodo de la sublista. 
comprobar_reserva_memoria_sublista(p_aux->expe); p_aux->expe->sig = NULL;
p_cad= strtok(cad,":"); /* Extraer la subcadena"Primero" del primercurso. El puntero p_cad apunta a la subcadena.*/ 
p_cad= strtok(NULL,"\n"); /* Extraer la subcadenade notas del primer curso. El puntero p_cadapunta a la subcadena. */ 
strcpy(p_aux->expe->curso, p_cad); /* Cargar el campo curso del primer nodo de la sublistacon las notas de primero.*/ 
p_aux_notas= p_aux->expe; /* El puntero auxiliar p_aux_notasse utiliza para crear los nuevos nodos de la sublista. */ 
//Crear los siguientes nodos de las sublistsay cargarlos con las notas de los correspondientescursos. 
for(i=1; i<=4; i++){ 
fgets(cad, 60, pf); 
if(!feof(pf)){  //Evitarcargarladoblelecturade laúltimalíneadel fichero. 
if(strcmp(cad, "*\n") != 0){ 
p_aux_notas->sig= malloc(sizeof(t_notas)); /* Reservar memoria para el nuevo nodo de la sublista. */ 
comprobar_reserva_memoria_sublista(p_aux_notas->sig); 
p_aux_notas= p_aux_notas->sig; //Avanzar el puntero auxiliar al nuevo nodo. 
p_aux_notas->sig= NULL;
p_cad= strtok(cad,":"); //Extraer la subcadenacon la cabecera del curso correspondiente. 
p_cad= strtok(NULL,"\n"); //Extraer la subcadenade notas del curso correspondiente. 
strcpy(p_aux_notas->curso, p_cad); //Cargar el campo cursodel nodo de la sublista. 
} 
else{ 
break; //Cuando se lee el carácter * deseparación entre alumnos se sale del bucle for. 
}
} 
} //Fin del bucle for.
} 
} //Fin bloque ifcaso particular alumno primera matrícula al final del fichero. 
} //Fin del bucle while. 
fclose(pf);  //Cerrar el fichero asociado al puntero pf.
*punt= p_inicio; /* En la dirección de *puntse asigna el puntero p_inicio. Es decir, se asigna la dirección contenida en la variable puntero p_inicio. */ 
returnalumnos_cargados; //Retorna el número de alumnos cargados en la lista. 
}//Fin de la función cargar_fich_alumnos.
/* Definición de la función que almacena una lista dinámica en un fichero detexto. Nombre: almacenar_lista_en_fichero. Tipo de la función: int. Parámetrosformales:Recibeelpunterop_inicioalprincipiodeunalistadinámica. Retorno:Retornaelnúmerodealumnosalmacenadosenelficherodealumnos.*/ 
int almacenar_lista_en_fichero(t_alum*p_inicio){ 
int cont_curso, expedientes_almacenados=0; 
t_alum *p_aux;  //Puntero auxiliar para recorrer la lista de alumnos.  
t_notas *p_aux_notas; /* Puntero auxiliar para recorrer lassublistasde expedientes de los nodosde la lista de alumnos. */
FILE *pf; 
pf= gfopen("fich_alumnos.txt", "w");  /* Llamada a la función gfopenparaabrirel fichero fich_alumnos.txt paraescritura. */ 
if(p_inicio== NULL){  //Si la lista está vacía, se sale de la función. 
return 0; //El valor 0 del retorno indica que no se ha almacenado ningún alumno en el fichero de alumnos. 
}
p_aux= p_inicio;  //p_aux: puntero auxiliar al principiode la lista dinámica de alumnos. 
while(p_aux){ 
fprintf(pf, "%s", p_aux->nombre); //almacenar el nombredel alumno. 
fprintf(pf, "nif:%s\n", p_aux->nif); //almacenar elNIF del alumno. 
//Almacenar los expedientes de los alumnos. 
p_aux_notas= p_aux->expe; //p_aux_notasapunta al primer nodo de lasublistade expedientes. 
cont_curso= 0;  //La variable se inicializaa 0 para cada nodo de la listade alumnos. 
while(p_aux_notas){ 
cont_curso++; /* La variable cont_cursoseincrementa con el avance del puntero p_aux_notasen lasublistade expediente. */ 
switch(cont_curso){ 
case 1: fprintf(pf, "primero:%s\n", p_aux_notas->curso); 
break; 
case 2: fprintf(pf, "segundo:%s\n", p_aux_notas->curso);  
break;
case 3: fprintf(pf, "tercero:%s\n", p_aux_notas->curso); 
break; 
case 4: fprintf(pf, "cuarto:%s\n", p_aux_notas->curso); 
break; 
} 
p_aux_notas= p_aux_notas->sig; /* Avanzar el puntero p_aux_notasal siguiente nodo de la sublistade expedientes. */ 
} //Fin bucle whilesublistade expedientes. 
if(p_aux->sig!= NULL){ fprintf(pf, "*\n");  //Almacena el carácter *separador de alumnos. 
} 
expedientes_almacenados++; 
p_aux= p_aux->sig;  //Avanzar el puntero p_auxal siguiente nodo de lalista de alumnos. 
} //Fin bucle whilelista de alumnos. 
return expedientes_almacenados; //Retorna el número de expedientes almacenados en el fichero. 
}  //Fin de la función almacenar_lista_en_fichero.
/*Definicióndelafunciónqueabreunfichero. Nombredelafunción: gfopen. Tipodelafunción:FILE. Parámetros formales: recibe dos parámetros: un puntero al array que contiene el nombre del fichero que se desea abrir y otropunteroalacadenaquecontieneelmododeaperturadelfichero. Retorno:unpunteropfasociadoalficheroquesehaabierto.*/ 
FILE*gfopen(char *nom_fich, char *modo){ 
FILE*pf; if((pf= fopen(nom_fich, modo))== NULL){ 
system("clear"); 
printf("\n\vERROR: No es posible abrir el fichero %s \n\v",nom_fich); 
exit(1); 
} 
return pf; 
}
/*Definicióndelafunciónquedeterminasiunficheroestávacío. Nombredelafunción: fichero_vacio Tipodelafunción:int. Parámetrosformales:recibeunpunterodetipoFILEasociadoalficheroquesedeseadeterminarsiestávacío. Retorno:retornaelvalor0sielficheroestávacíoyelvalor1sinoestávacío.*/ 
int fichero_vacio(FILE*pf){ 
int vacio; 
fseek(pf, 0, SEEK_END); /* Situar el puntero pfal final del fichero con un desplazamiento 0 (ftell detectará si es cierto o no). */ 
if(ftell(pf) == 0 ){  /* ftellindica que la posición del fichero apuntada porpfes el final del mismo =>el fichero está vacío. */ 
vacio= 0; 
} 
else{ fseek(pf, 0, SEEK_SET); //Volver a situar el punteropfal principio del fichero. 
vacio= 1; 
} 
return vacio; 
}
/*Definicióndelafunciónquecompruebasisehapodidoreservarmemoriaparaunnododeunalistadinámica. Nombredelafunción: comprobar_reserva_memoria Tipodelafunción:void. Parámetrosformales:recibeunpunterodetipot_alumretornadoporlafunciónmalloc. Retorno:noretornaningúnvalor.*/ 
void comprobar_reserva_memoria_lista(t_alum*punt){ 
if(punt== NULL){ 
printf("\n\vNose ha podido reservar memoria para el nodo.\n\v"); 
exit(1); 
} 
return; 
}
/* Definición de la función que comprueba si se ha podido reservar memoria para un nodo de una sublista dinámica. Nombredelafunción: comprobar_reserva_memoria_sublista. Tipodelafunción:void. Parámetrosformales:recibeunpunterodetipot_notasretornadoporlafunciónmalloc. Retorno:noretornaningúnvalor.*/ 
void comprobar_reserva_memoria_sublista(t_notas*punt){ 
if(punt== NULL){ 
printf("\n\vNose ha podido reservar memoria para el nodo.\n\v"); 
exit(1); 
} 
return; 
}
/*Definicióndelafunciónqueliberalamemoriadelosnodosdeunalistadinámicasimplementeenlazada. Nombredelafunción: liberar_memoria_lista Tipodelafunción:void. Parámetrosformales:recibeunpunterodetipot_alumqueapuntaalprincipiodeunalistadinámica. Retorno:noretornaningúnvalor.*/ 
void liberar_memoria_lista(t_alum*p_inicio){ 
t_alum *p_aux, *p_aux1; /* Se declaran dos punteros auxiliares para liberar la memoria de los nodos de lalista dinámica simplementeenlazada. */ 
p_aux= p_aux1 = p_inicio;  //Hacer que los dos punteros auxiliares apunten al principio de la lista. 
while(p_aux){ 
if(p_aux->sig== NULL){ //Casos particulares delultimo nodo de una listao de unalista con un sólonodo. 
free(p_aux);  //Liberar la memoria del nodo. 
p_aux= NULL;  /* Al liberar memoria se debe inicializar a NULL el puntero para evitar consecuencias imprevisibles. En este caso, el puntero es el de la condicióndel whiley se produciría automáticamente un error.*/ 
} 
else{ //Caso general. 
p_aux= p_aux->sig; //Avanzar el puntero de la condición del whileal siguiente nodo.
p_aux1->sig= NULL;  /* Romper el enlacecon la lista del nodo apuntado por p_aux1ubicado al principio de la lista. */ 
free(p_aux1);  //Liberar la memoria de dicho nodo. 
p_aux1 = p_aux;  //Hacer que p_aux1 vuelva a apuntar al nodo ubicado al principio de la lista.
} 
} //Fin del bucle while. 
return;
}
/*Definicióndelafunciónqueliberalamemoriadelosnodosdeunasublistadinámica. Nombredelafunción: liberar_memoria_sublista Tipodelafunción:void. Parámetrosformales:recibeunpunterodetipot_notasqueapuntaalprincipiodeunalistadinámica. Retorno:noretornaningúnvalor.*/ 
void liberar_memoria_sublista(t_notas*p_inicio_notas){ 
t_notas *p_aux_notas, *p_aux1_notas;  /* Se declaran dos punteros auxiliares para liberar la memoria de los nodos de lalista dinámica simplementeenlazada. */ 
p_aux_notas= p_aux1_notas = p_inicio_notas;  /* Hacer que los dos punteros auxiliares apunten al principio de la lista. */ 
while(p_aux_notas){ 
if(p_aux_notas->sig== NULL){ /* Casos particulares delultimo nodo de una listao de unalista con un sólonodo. */ 
free(p_aux_notas);  //Liberar la memoria del nodo. 
p_aux_notas= NULL;  /* Al liberar memoria se debe inicializar a NULL el puntero para evitar consecuencias imprevisibles. En este caso, el puntero es el de la condición del whiley se produciría automáticamente un error.*/ 
} 
else{ //Caso general.
p_aux_notas= p_aux_notas->sig; //Avanzar el puntero de la condición del whileal siguiente nodo. 
p_aux1_notas->sig= NULL;  /* Romper el enlacecon la lista del nodo apuntado por p_aux1_notas ubicado al principio de la lista. */ 
free(p_aux1_notas);  //Liberar la memoria de dicho nodo. 
p_aux1_notas = p_aux_notas;  /* Hacer que p_aux1_notas vuelva a apuntar al nodo ubicado al principio de la lista. */
} 
} //Fin del bucle while. 
return;
}
