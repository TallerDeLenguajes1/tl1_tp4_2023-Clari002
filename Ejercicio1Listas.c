#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMA 150
typedef struct Tarea
{
    int TareaID; //Numerado en ciclo iterativo
    char * Descripcion;
    int Duracion; //entre 10 - 100
}Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo * siguiente;
}Nodo;

//funciones para cargar nodos y los datos a la lista
Nodo * crearTarea(Tarea T);
Tarea retornarTarea(int contador, Tarea T);
Nodo * cargarLista(Nodo * Lista);
Nodo * insertarNodo(Nodo * Lista, Nodo * nuevoNodo);
//funciones para mostrar
void mostrarTarea(Nodo * Lista);
void mostrarLista(Nodo * Lista);
//funcion buscar
Nodo * buscarTareaPorId(Nodo * TodasLasTareas, Nodo * TareasPendientes, Nodo * TareasRealizadas,int  idBuscado);
Nodo * buscarTareaPorClave(Nodo * TodasLasTareas,Nodo * TareasPendientes, Nodo * TareasRealizadas, char clave[]);
//funcion borrar
void  borrarTareaPorId(Nodo * TodasLasTareas, Nodo * TareasPendientes, Nodo * TareasRealizadas,int  idBuscado);
int main()
{
    Nodo * TodasTareas = NULL;
    Nodo * TareasPendientes = NULL;
    Nodo * TareasRealizadas = NULL;
    //cargo las tareas en tareas pendientes
    TodasTareas = cargarLista(TodasTareas); 
    //mostrar las tareas cargadas en la lista tareas pendientes
 
    int resp;
    char respuesta;
    Nodo * aux;
    do
    {
        printf("\n\n-----------CUESTIONARIO-------------------");
        printf("\n(1)Clasificar de Realizada o Pendiente la tarea");
        printf("\n(2)Mostrar todas las Tareas");
        printf("\n(3)Mostrar las Tareas Pendientes");
        printf("\n(4)Mostrar las Tareas Realizadas");
        printf("\n(5)Buscar una tarea por ID");
        printf("\n(6)Buscar una tarea por Clave");
        printf("\n(0)Salir");
        printf("\nInsertar valor: ");
        scanf("%d", &resp);
    switch (resp)
    {
    case 1:
    if (TodasTareas!=NULL)
    {
         while (TodasTareas!= NULL)
        {
            mostrarTarea(TodasTareas);
            printf("\nTarea Realizada (s/n): ");
            printf("\n");
            fflush(stdin);
            scanf("%c", &respuesta);
            if (respuesta == 's')
            {
                aux=TodasTareas;
                TodasTareas=TodasTareas->siguiente;
                aux->siguiente=NULL;           
                TareasRealizadas = insertarNodo(TareasRealizadas, aux);

            }else{
                if (respuesta == 'n')
               {
                  aux = TodasTareas;
                  TodasTareas=TodasTareas->siguiente;
                  aux->siguiente=NULL;
                  TareasPendientes= insertarNodo(TareasPendientes, aux);
   
               }  
            }
                   
        }    
    }else{
        printf("\nLas tareas ya se distribuyeron");
    }
    
       
        break;    


    case 2:
    if (TodasTareas!= NULL)
    {
         printf("\n\n-----------TODAS LAS TAREAS-------------------");

        mostrarLista(TodasTareas);
    }else{
        printf("\nLas tareas se distribuyeron");
    }
   
        break;
    case 3:
    printf("\n\n-----------TAREAS PENDIENTES-------------------");

        mostrarLista(TareasPendientes);
        break;
    case 4:
    printf("\n\n-----------TAREAS REALIZADAS-------------------");

        mostrarLista(TareasRealizadas);
        break;
    case 5:
    printf("\n\n-----------BUSCAR TAREA POR ID-------------------");
    int idBuscado;
    Nodo * Buscado = NULL;
    printf("\nIngresar el id a buscar: ");
    scanf("%d",&idBuscado);
    
    Buscado = buscarTareaPorId(TodasTareas , TareasPendientes, TareasRealizadas, idBuscado);
    if (Buscado != NULL)
    {
         mostrarTarea(Buscado);
    }else{
        printf("\nId=%d no encontrado", idBuscado);
    }
    
   

        break;
    case 6:
    
    printf("\n\n-----------BUSCAR TAREA POR CLAVE-------------------");
     char * clave, claveBuscada[TAMA];
    Nodo * Buscado2 = NULL;

     printf("\nIngresar clave a buscar: ");
    fflush(stdin);
    gets(claveBuscada);
    fflush(stdin);
    clave = (char *)malloc(sizeof(char)* strlen(claveBuscada)+1);
    strcpy(clave, claveBuscada);
    Buscado2 = buscarTareaPorClave(TodasTareas, TareasPendientes, TareasRealizadas, clave);
      if (Buscado2 != NULL)
    {
         mostrarTarea(Buscado2);
    }else{
        printf("\nClave=%s no encontrada", claveBuscada);
    }

    free(clave);
        break;
  
    default:
        break;
    }

    } while (resp != 0);
    return 0;
}

//funciones
Nodo * cargarLista(Nodo * Lista){

    Nodo * nuevoNodo;
    Tarea TAREA;
    char valor = 's';
    int contador=1;
    while (valor == 's')
    {
        TAREA = retornarTarea(contador, TAREA);
        nuevoNodo = crearTarea(TAREA);
        contador=contador+1;
        Lista = insertarNodo(Lista, nuevoNodo);

        printf("Dese continuar (s/n): ");
        fflush(stdin);
        scanf("%c", &valor);
      
        printf("\n");
    }
    return Lista;
}

Tarea retornarTarea(int contador, Tarea T)
{
    char Buff[TAMA];
        T.TareaID=contador;
        printf("Ingrese una descripcion: ");
         fflush(stdin);
        gets(Buff);
         
        //reserva de memoria para la descripcion
        T.Descripcion=(char *)malloc(sizeof(char *)*strlen(Buff+1));
        strcpy(T.Descripcion,Buff);
        printf("Ingrese la duracion entre 10 - 100: ");
        fflush(stdin);
        scanf("%d", &T.Duracion);
       

    return T;
}

Nodo * crearTarea(Tarea T){
    Nodo * TAREA = (Nodo *)malloc(sizeof(Nodo));

    TAREA->T.TareaID=T.TareaID;
    TAREA->T.Duracion=T.Duracion;
    TAREA->T.Descripcion= T.Descripcion;
   
  // strcpy((*TAREA).T.Descripcion, T.Descripcion);
 
   TAREA->siguiente=NULL;

   return TAREA;
}

Nodo * insertarNodo(Nodo * Lista, Nodo * nuevoNodo){
    if (Lista == NULL)
    {
        Lista = nuevoNodo;
    }else{
        nuevoNodo->siguiente=Lista;
        Lista=nuevoNodo;
    }
    return Lista;
}

void mostrarTarea(Nodo * Lista){
     printf("\n-------------TAREA N%d-------------", Lista->T.TareaID);
        printf("\nID: %d", Lista->T.TareaID);
        printf("\nDescripcion: ");
        puts(Lista->T.Descripcion);
        printf("Duracion: %d", Lista->T.Duracion);
}

void mostrarLista(Nodo * Lista){
    Nodo * aux = Lista;
    while (aux != NULL)
    {
        mostrarTarea(aux);
        aux = aux->siguiente;
    }
    

}

Nodo * buscarTareaPorId(Nodo * TodasLasTareas, Nodo * TareasPendientes, Nodo * TareasRealizadas,int  idBuscado){
Nodo * auxPend = TareasPendientes;
Nodo * auxRea = TareasRealizadas;
Nodo * aux = TodasLasTareas;
Nodo * Buscado=NULL;
    if(aux != NULL){
        while (aux != NULL)
        {
            if (aux->T.TareaID==idBuscado)
            {
                Buscado = insertarNodo(Buscado, aux);
                return Buscado;
            }else{
                aux=aux->siguiente;
            }
            
        }
        
    }

    if (auxPend!=NULL)
    {
         while (auxPend!= NULL)
        {
        if (auxPend->T.TareaID==idBuscado)
        {
           
            Buscado = insertarNodo(Buscado, auxPend);
            return Buscado;
        }else{
            auxPend=auxPend->siguiente;
        }

        }
        
    }

    if (auxRea!=NULL)
    {
        while (auxRea!=NULL)
            {
                if(auxRea->T.TareaID=idBuscado){
                    Buscado = insertarNodo(Buscado, auxRea);
                    return Buscado;
                }else{
                    auxRea=auxRea->siguiente;
                }
            }
    }
    
   
    return(NULL);
}

Nodo * buscarTareaPorClave(Nodo * TodasLasTareas, Nodo * TareasPendientes, Nodo * TareasRealizadas, char clave[]){
Nodo * auxPend = TareasPendientes;
Nodo * auxRea = TareasRealizadas;
Nodo * aux = TodasLasTareas;
Nodo * Buscado=NULL;

  if(aux != NULL){
        while (aux != NULL)
        {
            if (strstr(aux->T.Descripcion,clave)!=NULL)
            {
                Buscado = insertarNodo(Buscado, aux);
                return Buscado;
            }else{
                aux=aux->siguiente;
            }
            
        }
        
    }
      if(auxPend != NULL){
        while (auxPend != NULL)
        {
            if (strstr(auxPend->T.Descripcion,clave)!=NULL)
            {
                Buscado = insertarNodo(Buscado, auxPend);
                return Buscado;
            }else{
                auxPend=auxPend->siguiente;
            }
            
        }
        
    }
      if(auxRea != NULL){
        while (auxRea != NULL)
        {
            if (strstr(auxRea->T.Descripcion,clave)!=NULL)
            {
                Buscado = insertarNodo(Buscado, auxRea);
                return Buscado;
            }else{
                auxRea=auxRea->siguiente;
            }
            
        }
        
    }
return(NULL);
}


