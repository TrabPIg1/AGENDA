struct tarea{
char tipo[10];
int identif_num;
char descripcion[50];
char propietario[20];
int prioridad;
char estado[15];
int fecha;
struct tarea *prox;
};
typedef struct tarea Tarea;
Tarea *liberar(Tarea *cabecera);
int cargar_tareas(Tarea**punt);
int listar_tarea();
int ver_tarea();
int eliminar_tarea();
int crear_tarea();
int valor_identif_num();
