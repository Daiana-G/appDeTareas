#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct tareas {
	char tarea [60];
	int id;
	int estado;
};


void crear();
void modificar();
void listar();
void filtrarPorEstado();
void eliminar();


int main(){
	
	int opcion;
	
	do{
		printf("\n\t\tApp de tareas\n");
		printf("\n\t1-Crear tarea");
		printf("\n\t2-Modificar estado de tarea");
		printf("\n\t3-Listado tareas");
		printf("\n\t4-Filtrar por Estado");
		printf("\n\t5-Eliminar tarea");
		printf("\n\t6-Finalizar");
		printf("\n\n\tIngrese una opcion valida del 1 al 5 (solo deben ingresarse numeros)\n");
		
		scanf("%i",&opcion);
		
		switch(opcion){
			case 1: crear();
				break;
			case 2: modificar();
				break;
			case 3:listar();
				break;
			case 4:filtrarPorEstado();
				break;
			case 5: eliminar();
				break;
			default:
				if(opcion !=6){
					
				printf("\ndebes ingresar una opcion numerica valida del 1 al 6\n");
				
				}else if(opcion==6){
					printf("\n El programa se finalizo con exito, presione cualquier tecla");
				} 
				break;
		}
	}while(opcion!=6);
	
	
	return 0;
}

void crear(){
	FILE *arch;
	arch=fopen("tareas.dat","ab");
	if(arch==NULL){
		exit(1);
	}
	
	tareas tarea;
	printf("Ingrese tarea..");
	fflush(stdin);
	gets(tarea.tarea);
	fflush(stdin);
	
	tarea.estado= 1;
	
	printf("ingrese un numero identificador para su tarea");
	scanf("%i",&tarea.id);
	fflush(stdin);
	
	fwrite (&tarea, sizeof(tareas),1,arch);
	
	fclose(arch);
};


void modificar(){
	
	FILE *arch;
    arch=fopen("tareas.dat","r+b");
    
    if (arch==NULL){
        exit(1);
	}
	
    printf("\nIngrese ID de la tarea para modificar estado");
    
	int id;
    
	scanf("%i", &id);
    
	tareas tarea;
    
	int existe=0;
    
	fread(&tarea, sizeof(tareas), 1, arch);
    
    while(!feof(arch))
    {
        if (id==tarea.id){
        	
        	printf("\n%s",tarea);
        	printf("\nModifique estado");
        	printf("\nPara Dejar en estado \"pendiente\" presione 1");
        	printf("\nPara Dejar en estado \"en curso\" presione 2");
			printf("\nPara Dejar en estado \"terminado\" presione 3");		
        	printf("\nIngrese numero:");
        	scanf("%i",&tarea.estado);
        	int pos=ftell(arch)-sizeof(tareas);
        	fseek(arch,pos,SEEK_SET);
        	fwrite(&tarea, sizeof(tareas), 1, arch);
        	printf("\nSe modifico el estado de la tarea\n");
        	existe=1;
			break;
        }
        
        fread(&tarea, sizeof(tareas), 1, arch);
    }
    
	if (existe==0){
        
        printf("\nNo existe una tarea con ese id\n");
		printf("\nPuede consultar el listado para verificar el id\n");
		
	}
	
    fclose(arch);
    
};

void listar(){
	
	FILE *arch;
    	arch=fopen("tareas.dat","rb");
    if (arch==NULL){
        exit(1);
	}
	
    tareas tarea;
    
	fread(&tarea, sizeof(tareas), 1, arch);
    
  	system("cls");
  	
  	int existe;
  	
  	existe=0;
  	
    printf("\n\tListado de Tareas:\n\n");
	while(!feof(arch))
    {
    	
    	switch(tarea.estado){
    		case 1:
    			printf("\n\tID:%i\tTarea:%s\tEstado:Pendiente\n", tarea.id, tarea.tarea);
    			existe=1;
				break;
    		case 2:
    			printf("\n\tID:%i\tTarea:%s\tEstado:En curso\n", tarea.id, tarea.tarea);
				existe=1;
				break;
			case 3:
				printf("\n\tID:%i\tTarea:%s\tEstado:Terminado\n\n", tarea.id, tarea.tarea);
				existe=1;
			break;
		}
    	
        
		fread(&tarea, sizeof(tareas), 1, arch);
    }
    
    if(existe==0){
		printf("\n\tNo hay tareas pendientes\n\n");
	}

    
    fclose(arch);


};


void filtrarPorEstado(){
	
	FILE *arch;
    arch=fopen("tareas.dat","rb");
    if (arch==NULL){
        exit(1);
	}
	
    tareas tarea;
    
	fread(&tarea, sizeof(tareas), 1, arch);
    
    int estado;
	system("cls");
	
    printf("\nFiltrado por estado\n");
    printf("\n------------------------------------------\n");
    printf("\npresione 1 para filtrar por \"pendiente\"\n");
    printf("\npresione 2 para filtrar por \"en curso\"\n");
    printf("\npresione 3 para filtrar por \"terminado\"\n");
    printf("\n------------------------------------------\n");
     
	scanf("%i",&estado);
    fflush(stdin);
    
    system("cls");
    
	printf("\n------------------------------------------\n");
    
    int existe=0;
    
    if(estado==1){
		printf("tareas pendientes:\n");
	}else if(estado==2){
		printf("tareas en curso:\n");
	}else if(estado==3){
		printf("tareas terminadas:\n");
	}
	
    
	while(!feof(arch))
    {
		if(tarea.estado==estado==1){
    		printf("\nID:%i\tTarea:%s\n", tarea.id, tarea.tarea);
			existe=1;
		}
		   
		if(tarea.estado==estado==2){
			
    		printf("\nID:%i\tTarea:%s\n", tarea.id, tarea.tarea);
    		if(tarea.estado==2){
    			printf("en curso");
			}
			existe=1;
		}
		   
		if(tarea.estado==estado==3){
			printf("\nID:%i\tTarea:%s\n", tarea.id, tarea.tarea);
			existe=1;
		}
       
		fread(&tarea, sizeof(tareas), 1, arch);
    }
    
     
    if(existe==0){
		printf("\nno hay tareas con ese estado\n");
	}
    printf("\n------------------------------------------\n");
        
    
    fclose(arch);
};

void eliminar(){
	
	FILE *arch;
    arch=fopen("tareas.dat","rb");
    if (arch==NULL){
       	exit(1);
	}
    
	
	printf("\nIngrese el id de la tarea a borrar\n");
    
    int idTarea;
    scanf("%i", &idTarea);
    
    tareas tarea;

    FILE *nuevo;
    nuevo=fopen("tareas.tmp","ab");
    
	if (arch==NULL){
        exit(1);
	}

    int existe=0;
    
	fread(&tarea, sizeof(tareas), 1, arch);
    
	while(!feof(arch)){
		
        if ( idTarea == tarea.id){
        	
			printf("\nEliminando tarea..\n");
			
			printf("\n%i\t%s\n",tarea.id,tarea.tarea);
			
			printf("\nTarea Eliminada\n");
			
			existe=1;
		}else{
        	
            fwrite(&tarea, sizeof(tareas), 1, nuevo);
        
		}
        
		fread(&tarea, sizeof(tareas), 1, arch);
    }
    
    if (existe==0){
    	
		printf("\nNo existe una tarea con el id %i\n",idTarea);
		printf("\nPuede consultar el listado (Opcion 3 del menu) para verificar el id\n");
		printf("\n------------------------------------------\n");
		system("pause");
		system("cls");
	}
	
    fclose(arch);
    fclose(nuevo);
    
    remove("tareas.dat");
    rename("tareas.tmp", "tareas.dat");
};