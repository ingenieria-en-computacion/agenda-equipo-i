#include "agenda.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 * Esta función se encarga de iniciar el número de contactos a cero
 */
void iniciar_agenda(Agenda *agenda){
    agenda->num_contactos = 0;  // Inicializa la agenda vacía
}



// Varible que lleva la cuenta de cuantos contactos hay en la agenda
int num_contactos;

/**
 * Esta función sirve para agregar un contacto nuevo en la agenda
 */
void agregar_contacto(Agenda *agenda, Contacto c){
    if (agenda->num_contactos < MAX_CONTACTOS) {
        agenda->contactos[agenda->num_contactos] = c;  // Guardar contacto
        agenda->num_contactos++;                       // Aumentar contador
    } else {
        printf("La agenda está llena.\n");
    }
}


/**
 * Esta función sirve para buscar un contacto por nombre en la agenda y retorna la posición del contacto si exisite
 * En caso contrario retorna -1
 */
int buscar_contacto(Agenda *agenda, char *nombre){
    for (int i = 0; i < agenda->num_contactos; i++) {
        if (strcmp(agenda->contactos[i].nombre, nombre) == 0) {
            return i;
        }
    }
    return -1; // No encontrado
}


/**
 * Esta función  sirve para buscar un contacto por su número de telefono en la agenda
 */
int buscar_contacto_x_telefono(Agenda *agenda, char telefono[]){
    for (int i = 0; i < agenda->num_contactos; i++) {
        if (strcmp(agenda->contactos[i].telefono, telefono) == 0) {
            return i;
        }
    }
    return -1; // No encontrado
}


/**
 * Esta función sirve para ordenar los contactos por nombres de forma ascendente
 */
void ordenar_contactos(Agenda *a){
     int i, j;
    Contacto temp;
    for(i = 0; i < a->num_contactos; i++){
        for(j=0; j < a->num_contactos-i-1; j++){
            if(strcmp(a->contactos[j].nombre, a->contactos[j+1].nombre) > 0){
                temp = a->contactos[j];
                a->contactos[j] = a->contactos[j+1];
                a->contactos[j+1] = temp;
            }
        }
    }
}

/**
 * Esta función sirve para ordenar los contactos por nombres de forma descendente
 */
void ordenar_contactos_inv(Agenda *a){
   
}


/**
 * Función auxiliar para imprimir un contacto
 */
void mostrar_contacto(Contacto c){
    printf("Nombre: %s\n", c.nombre);
    printf("Apellido: %s\n", c.apellido);
    printf("Fecha de nacimiento: %d de %d\n", c.dia_nacimiento, c.mes_nacimiento);
    printf("Telefono: %s\n", c.telefono);
    printf("Tipo de telefono: %d\n", c.tipo);
}


/**
 * Función auxiliar para leer un contacto
 */
void leer_contacto(Contacto *c){
    printf("Ingrese el nombre: ");
    scanf("%s", c->nombre);

    printf("Ingrese el apellido: ");
    scanf("%s", c->apellido);

    printf("Ingrese el mes de nacimiento (1-12): ");
    int mes;
    scanf("%d", &mes);
    c->mes_nacimiento = mes - 1; // Ajuste para usar enum

    printf("Ingrese el día de nacimiento: ");
    scanf("%d", &c->dia_nacimiento);

    printf("Ingrese el número de teléfono: ");
    scanf("%s", c->telefono);

    printf("Tipo de teléfono (0=Casa,1=Movil,2=Oficina,3=Otro): ");
    scanf("%d", (int*)&c->tipo);
}

/**
 * Función que imprime todos los contactos de la agenda en pantalla
 */
void imprimir_agenda(Agenda agenda){
    if (agenda.num_contactos == 0) {
        printf("La agenda está vacía.\n");
        return;
    }

    printf("\n CONTACTOS EN LA AGENDA \n");
    for (int i = 0; i < agenda.num_contactos; i++) {
        mostrar_contacto(agenda.contactos[i]);
        printf("------------------------------\n");
    }
}

/**
 * Función que sirve para cargar contactos escritos en un archivo a la agenda
 */
void cargar_contactos(char *filename, Agenda *agenda){
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    Contacto c;
    while (fscanf(f, "%s %s %d %d %s %d",
                  c.nombre,
                  c.apellido,
                  &c.mes_nacimiento,
                  &c.dia_nacimiento,
                  c.telefono,
                  (int*)&c.tipo) == 6)
    {
        agregar_contacto(agenda, c);
    }

    fclose(f);
}


/**
 * Función que sirve para guardar todos los contactos de la agenda en un archivo
 */
void guardar_contactos(char *filename, Agenda agenda){
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("No se pudo abrir el archivo para escribir.\n");
        return;
    }

    for (int i = 0; i < agenda.num_contactos; i++) {
        Contacto c = agenda.contactos[i];
        fprintf(f, "%s %s %d %d %s %d\n",
                c.nombre,
                c.apellido,
                c.mes_nacimiento,
                c.dia_nacimiento,
                c.telefono,
                c.tipo);
    }

    fclose(f);
}