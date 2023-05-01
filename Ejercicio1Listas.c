#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
void  borrarTareaPorId(int idBuscado, Nodo ** TodasLasTareas, Nodo ** TareasPendientes, Nodo ** TareasRealizadas);
void  borrarTareaPorClave(char clave[], Nodo ** TodasLasTareas, Nodo ** TareasPendientes, Nodo ** TareasRealizadas);
//funcion mostrar la cantidad de tareas y tiempo asociado
void mostrarDatos(Nodo * Lista);
//ffuncion pertenece
bool pertenece(int valor, Nodo * lista);
//funcion para buscar un nodo y borrarlos de la lista
Nodo * buscarYBorrardeLista(Nodo ** Lista, int id);

int main()
{
    Nodo * TodasTareas = NULL;
    Nodo * TareasPendientes = NULL;
    Nodo * TareasRealizadas = NULL;
    Nodo * TareasEnProceso = NULL;
    //cargo las tareas en tareas pendientes
    TodasTareas = cargarLista(TodasTareas); 
    //mostrar las tareas cargadas en la lista tareas pendientes
 
    int resp;
    char respuesta;
    Nodo * aux;
    do
    {
        printf("\n\n-----------CUESTIONARIO-------------------");
        printf("\n(1)Clasificar de Realizada, Pendiente o en Proceso la tarea");
        printf("\n(2)Listar todas las tareas");
        printf("\n(3)Seleccionar una tarea por ID");   
       // printf("\n(6)Borrar una tarea por Clave");
       printf("\n(4)Datos obetenidos de los tres estados");
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
            printf("\nTarea Realizada (s) - Tarea en Proceso (p) - Tarea Pendiente(n): ");
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
   
               }  else{
                if (respuesta == 'p')
                {
                    aux = TodasTareas;
                    TodasTareas = TodasTareas->siguiente;
                    aux->siguiente=NULL;
                    TareasEnProceso = insertarNodo(TareasEnProceso, aux);
                }
                
               }
            }
                   
        }    
    }else{
        printf("\nLas tareas ya se distribuyeron");
    }
    
       
        break;    
    case 2:
         printf("\n\n-----------TODAS LAS TAREAS-------------------");
         printf("\n\nTareas en Proceso------------------------------");
         mostrarLista(TareasEnProceso);
         printf("\n\nTareas Realizadas------------------------------");
         mostrarLista(TareasRealizadas);
         printf("\n\nTareas Pendientes------------------------------");
        mostrarLista(TareasPendientes);
    

    break;

    case 3:
    printf("\n\n-----------SELECCIONAR TAREA POR ID-------------------");
    int idBuscado;
    Nodo * Buscado = NULL;
    printf("\nIngresar el id a buscar: ");
    scanf("%d",&idBuscado);
    
    Buscado = buscarTareaPorId(TareasEnProceso , TareasPendientes, TareasRealizadas, idBuscado);
    
    if (Buscado != NULL)
    {
        printf("\nTarea seleccionada");
        mostrarTarea(Buscado);
        int opcion;
        printf("\n\n(1)Mover la tarea a otra lista");
        printf("\n(2)Eliminar la tarea");
        printf("\n(0)Nada");
        printf("\nRespuesta: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
        
        case 1:
      

         if (pertenece(idBuscado, TareasEnProceso))
        {
             char resp;
            printf("\nMover Tarea a PENDIENTE(n) o REALIZADO(s): ");
            fflush(stdin);
            scanf("%c",&resp);

            Buscado = buscarYBorrardeLista(&TareasEnProceso, idBuscado);

            switch (resp)
            {
            case 'n':

                TareasPendientes = insertarNodo(TareasPendientes, Buscado);   
                break;
            case 's':
               
               TareasRealizadas = insertarNodo(TareasRealizadas, Buscado);
            break;
            default:
                break;
            }

            
        }else{
            if (pertenece(idBuscado, TareasPendientes))
            {
                char resp;
               printf("\nMover Tarea a En PROCESO(p) o REALIZADO(s): ");
                 fflush(stdin);
                 scanf("%c",&resp);

            Buscado = buscarYBorrardeLista(&TareasPendientes, idBuscado);

                switch (resp)
                {
                case 'p':
                    TareasEnProceso = insertarNodo(TareasEnProceso, Buscado);   
                break;
                case 's':
                    TareasRealizadas = insertarNodo(TareasRealizadas, Buscado);
                break;
                default:
                break;
                }
                
            }else{
                if (pertenece(idBuscado, TareasRealizadas))
                {
                    char resp;
                     printf("\nMover Tarea a En PROCESO(p) o PENDIENTES(n): ");
                    fflush(stdin);
                    scanf("%c",&resp);

            Buscado = buscarYBorrardeLista(&TareasRealizadas, idBuscado);

                    switch (resp)
                    {
                    case 'p':
                        TareasEnProceso = insertarNodo(TareasEnProceso, Buscado);   
                    break;
                    case 'n':
                        TareasPendientes = insertarNodo(TareasPendientes, Buscado);
                    break;
                    default:
                    break;
                    }
                    
                }
                
            }
            
        }
         break;
        case 2:
        
         borrarTareaPorId(idBuscado, &TareasEnProceso, &TareasPendientes, &TareasRealizadas);   
        

        break;
        
        default:
            break;
        }    
    
    }else{
        printf("\nId=%d no encontrado", idBuscado);
    }
            
  

        break;
 /* 
    case 9:
    printf("\n\n-----------BORRAR TAREA POR CLAVE-------------------");
    char * clave2, claveBuscada2[TAMA];
    
     printf("\nIngresar clave a borrar: ");
    fflush(stdin);
    gets(claveBuscada2);
    fflush(stdin);
    clave2 = (char *)malloc(sizeof(char)* strlen(claveBuscada2)+1);
    strcpy(clave2, claveBuscada2);
    borrarTareaPorClave(clave2, &TodasTareas, &TareasPendientes, &TareasRealizadas);
  
        break;*/
    case 4:
    printf("\n\nDATOS OBTENIDOS----------------------------");
    if (TareasEnProceso!=NULL)
    {
        printf("\nTAREAS EN PROCESO");
        mostrarDatos(TareasEnProceso);
    }
    if (TareasPendientes != NULL)
    {
        printf("\nTAREAS PENDIENTES");
        mostrarDatos(TareasPendientes);
    }
    if (TareasRealizadas !=NULL)
    {
       printf("\nTAREAS REALIZADAS");
        mostrarDatos(TareasRealizadas);
    }
    
    
    
    
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

void  borrarTareaPorId(int idBuscado, Nodo ** TodasLasTareas, Nodo ** TareasPendientes, Nodo ** TareasRealizadas){
    Nodo * seg;
    Nodo * ante;
   
    if ((*TodasLasTareas)!=NULL)
    {
       
        if ((*TodasLasTareas)->T.TareaID==idBuscado)
        {
           Nodo * aux = (*TodasLasTareas);
           (*TodasLasTareas)=(*TodasLasTareas)->siguiente;
           aux->siguiente=NULL;
           free(aux);
        }else{
            seg = (*TodasLasTareas);
            while (seg != NULL)
            {
                if (seg->T.TareaID!=idBuscado)
                {
                        ante = seg;
                     seg= seg->siguiente;
                 }else{
                
                     ante->siguiente= seg->siguiente;
                     seg->siguiente=NULL;
                     free(seg);
                }
            
            }
        
        }
         
    }
     if ((*TareasPendientes)!=NULL)
    {
       
        if ((*TareasPendientes)->T.TareaID==idBuscado)
        {
           Nodo * aux = (*TareasPendientes);
           (*TareasPendientes)=(*TareasPendientes)->siguiente;
           aux->siguiente=NULL;
           free(aux);
        }else{
            seg = (*TareasPendientes);
            while (seg != NULL)
            {
                if (seg->T.TareaID!=idBuscado)
                {
                        ante = seg;
                     seg= seg->siguiente;
                 }else{
                
                     ante->siguiente= seg->siguiente;
                     seg->siguiente=NULL;
                     free(seg);
                }
            
            }
        
        }
         
    }
     if ((*TareasRealizadas)!=NULL)
    {
       
        if ((*TareasRealizadas)->T.TareaID==idBuscado)
        {
           Nodo * aux = (*TareasRealizadas);
           (*TareasRealizadas)=(*TareasRealizadas)->siguiente;
           aux->siguiente=NULL;
           free(aux);
        }else{
            seg = (*TareasRealizadas);
            while (seg != NULL)
            {
                if (seg->T.TareaID!=idBuscado)
                {
                        ante = seg;
                     seg= seg->siguiente;
                 }else{
                
                     ante->siguiente= seg->siguiente;
                     seg->siguiente=NULL;
                     free(seg);
                }
            
            }
        
        }
         
    }

    
}

void  borrarTareaPorClave(char clave[], Nodo ** TodasLasTareas, Nodo ** TareasPendientes, Nodo ** TareasRealizadas){
 Nodo * seg;
Nodo * ante;
   
    if ((*TodasLasTareas)!=NULL)
    {
       
        if (strcmp(clave, (*TodasLasTareas)->T.Descripcion)==0)
        {
           Nodo * aux = (*TodasLasTareas);
           (*TodasLasTareas)=(*TodasLasTareas)->siguiente;
           aux->siguiente=NULL;
           free(aux);
        }else{
            seg = (*TodasLasTareas);
            while (seg != NULL)
            {
                if (strcmp(clave,seg->T.Descripcion)!=0)
                {
                        ante = seg;
                     seg= seg->siguiente;
                 }else{
                     ante->siguiente= seg->siguiente;
                     seg->siguiente=NULL;
                     free(seg);
                }
            
            }
        
        }
         
    }
    if ((*TareasPendientes)!=NULL)
    {
       
        if (strcmp(clave, (*TareasPendientes)->T.Descripcion)==0)
        {
           Nodo * aux = (*TareasPendientes);
           (*TareasPendientes)=(*TareasPendientes)->siguiente;
           aux->siguiente=NULL;
           free(aux);
        }else{
            seg = (*TareasPendientes);
            while (seg != NULL)
            {
                if (strcmp(clave,seg->T.Descripcion)!=0)
                {
                        ante = seg;
                     seg= seg->siguiente;
                 }else{
                     ante->siguiente= seg->siguiente;
                     seg->siguiente=NULL;
                     free(seg);
                }
            
            }
        
        }
         
    }
    if ((*TareasRealizadas)!=NULL)
    {
       
        if (strcmp(clave, (*TareasRealizadas)->T.Descripcion)==0)
        {
           Nodo * aux = (*TareasRealizadas);
           (*TareasRealizadas)=(*TareasRealizadas)->siguiente;
           aux->siguiente=NULL;
           free(aux);
        }else{
            seg = (*TareasRealizadas);
            while (seg != NULL)
            {
                if (strcmp(clave,seg->T.Descripcion)!=0)
                {
                        ante = seg;
                     seg= seg->siguiente;
                 }else{
                     ante->siguiente= seg->siguiente;
                     seg->siguiente=NULL;
                     free(seg);
                }
            
            }
        
        }
         
    }

}

void mostrarDatos(Nodo * Lista){
    Nodo * aux = Lista;
    int contador=0, sumaDuracion=0;
    while (aux != NULL)
    {
        contador++;
        sumaDuracion = sumaDuracion+aux->T.Duracion;
        aux = aux->siguiente;   
    }
    printf("\nLa cantidad tareas en la lista es: %d",contador);
    printf("\nLa duracion total es: %d", sumaDuracion);
}

bool pertenece(int valor, Nodo * lista){
    Nodo * aux = lista;
    //recorre la lista hasta encontrar el valor en la lista
    while (aux != NULL)
    {
        if (aux->T.TareaID == valor)
        {
            //si se encuentra el ID, devuelve true
            return true;
        }
        aux = aux->siguiente;
    }
    //si no encuentra el ID, devuelve false
    return false;
}

//funcion que busca un nodo por su id, lo elimina y lo retorna
Nodo * buscarYBorrardeLista(Nodo ** Lista, int id){
    Nodo * actual = *Lista;
    Nodo * previo = NULL;

    while (actual != NULL && actual->T.TareaID != id)
    {
        previo = actual;
        actual = actual->siguiente;
    }

    //si no se encontro el nodo con el id, retornamos NULL
    if (actual == NULL)
    {
        return NULL;
    }

    //si el nodo a eliminar es el primero de la lista
    if (previo == NULL)
    {
        *Lista = actual->siguiente;
    }else{
        previo->siguiente=actual->siguiente;
    }

    //retorna el nodo eliminado
    return actual;
    
    
}