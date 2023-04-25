#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//estrucutras
struct Tarea
{
    int TareaID; //Numerado en ciclo iterativo
    char * Descripcion;
    int Duracion; //entre 10 - 100
};

typedef struct Tarea Tareas;



int main()
{
    srand(time(NULL));
    int cTarea= 0;
    
    printf("Ingrese la catidad de tareas que va a realizar: ");
    
    scanf("%d", &cTarea);
    fflush(stdin);
    
    //reserva de memoria del vector de puntero
    Tareas **TAREA =(struct Tarea**)malloc(sizeof(struct Tarea*)*cTarea);
    
    //Iicializamos el arreglo apuntado a NULL
    for (int i = 0; i < cTarea; i++)
    {
        TAREA[i]=NULL;
    }

    int k=1;
    for (int i = 0; i < cTarea; i++)
    {
        //reserva de memoria para cada celda del vector
        TAREA[i]= malloc(sizeof(struct Tarea *));
        char aux[1000];

        TAREA[i]->TareaID = k;

        printf("\n\n-----------TAREA N%d-------------",k);
        k++;
        printf("\nIngrese una descripcion: ");
        gets(aux);
        //reserva de memoria para la descripcion
        TAREA[i]->Descripcion=(char *)malloc(sizeof(char *)*strlen(aux+1));
        strcpy(TAREA[i]->Descripcion, aux);

        printf("Ingrese la duracion entre 10 - 100: ");
     
        scanf("%d", &TAREA[i]->Duracion);
           fflush(stdin);
                                                
    }

    printf("\n\n-----------TAREAS CARGADAS-------------------");

    for (int i = 0; i < cTarea; i++)
    {
        printf("\n-------------TAREA N%d-------------", TAREA[i]->TareaID);
        printf("\nID: %d", TAREA[i]->TareaID);
        printf("\nDescripcion: ");
        puts(TAREA[i]->Descripcion);
        printf("Duracion: %d", TAREA[i]->Duracion);
 
    }


    Tareas *TareasRealizadas[cTarea];
    Tareas *TareasPendientes[cTarea];
    char respuesta;

    int a=0, b=0;
        printf("\n\n-----------CLASIFICACION-------------------");
     for (int i = 0; i < cTarea; i++)
    {
        printf("\n-------------TAREA N%d-------------", TAREA[i]->TareaID);
        printf("\nID: %d", TAREA[i]->TareaID);
        printf("\nDescripcion: ");
        puts(TAREA[i]->Descripcion);
        printf("Duracion: %d", TAREA[i]->Duracion);
        printf("\nTarea Realizada (s/n): ");
          fflush(stdin);
        scanf("%c", &respuesta);
      

        if (respuesta == 's')
        {
            TareasRealizadas[a]=TAREA[i];
            a=a+1;
        }
            if (respuesta == 'n')
            {
                  TareasPendientes[b]=TAREA[i];
                   b=b+1;
            }
      
     TAREA[i]=NULL;
        
        
    }

    printf("\n\n-----------TAREAS REALIZADAS-------------------");
    for (int i = 0; i < a; i++)
    {
        printf("\n-------------TAREA N%d-------------", TareasRealizadas[i]->TareaID);
        printf("\nID: %d", TareasRealizadas[i]->TareaID);
        printf("\nDescripcion: ");
        puts(TareasRealizadas[i]->Descripcion);
        printf("Duracion: %d", TareasRealizadas[i]->Duracion);
     
    }

  printf("\n\n-----------TAREAS PENDIENTES-------------------");
    for (int i = 0; i < b; i++)
    {
        printf("\n-------------TAREA N%d-------------", TareasPendientes[i]->TareaID);
        printf("\nID: %d", TareasPendientes[i]->TareaID);
        printf("\nDescripcion: ");
        puts(TareasPendientes[i]->Descripcion);
        printf("Duracion: %d", TareasPendientes[i]->Duracion);

    }


    return 0;
}

