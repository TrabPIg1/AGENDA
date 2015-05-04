struct tarea{
char tipo[10];
int identif_num;
char descripcion[50];
char propietario[20];
int prioridad;
char estado[15];
char fecha[20];
struct tarea *prox;
};
typedef struct tarea Tarea;
int almacenarfichero(Tarea *cabecera);
Tarea *liberar(Tarea *cabecera);
Tarea *cargar_tareas(Tarea *inicio);
int listar_tarea(Tarea**punt);
int ver_tarea(Tarea *cabecera,char propietario[20]);
int eliminar_tarea();
Tarea *crear_tarea(char propietario[20],Tarea *cabecera);
int valor_identif_num();
