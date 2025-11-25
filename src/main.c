#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

int main() {
    Agenda agenda;
    iniciar_agenda(&agenda);

    int opcion;
    char nombre_buscar[30];
    char telefono_buscar[15];
    Contacto c;
    int pos;

    do {
        printf("\n===== AGENDA TELEFONICA =====\n");
        printf("1. Agregar contacto\n");
        printf("2. Buscar contacto por nombre\n");
        printf("3. Buscar contacto por telefono\n");
        printf("4. Mostrar agenda completa\n");
        printf("5. Ordenar A-Z\n");
        printf("6. Ordenar Z-A\n");
        printf("7. Guardar contactos en archivo\n");
        printf("8. Cargar contactos desde archivo\n");
        printf("0. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch(opcion) {

            case 1:
                leer_contacto(&c);
                agregar_contacto(&agenda, c);
                break;

            case 2:
                printf("Ingresa el nombre a buscar: ");
                fgets(nombre_buscar, 30, stdin);
                nombre_buscar[strcspn(nombre_buscar, "\n")] = 0;
                pos = buscar_contacto(&agenda, nombre_buscar);
                if (pos != -1)
                    mostrar_contacto(agenda.contactos[pos]);
                else
                    printf("Contacto no encontrado.\n");
                break;

            case 3:
                printf("Ingresa el telefono a buscar: ");
                fgets(telefono_buscar, 15, stdin);
                telefono_buscar[strcspn(telefono_buscar, "\n")] = 0;
                pos = buscar_contacto_x_telefono(&agenda, telefono_buscar);
                if (pos != -1)
                    mostrar_contacto(agenda.contactos[pos]);
                else
                    printf("Telefono no encontrado.\n");
                break;

            case 4:
                imprimir_agenda(agenda);
                break;

            case 5:
                ordenar_contactos(&agenda);
                printf("Contactos ordenados A-Z.\n");
                break;

            case 6:
                ordenar_contactos_inv(&agenda);
                printf("Contactos ordenados Z-A.\n");
                break;

            case 7:
                guardar_contactos("contactos.txt", agenda);
                printf("Contactos guardados en contactos.txt\n");
                break;


            case 8:
                cargar_contactos("contactos.txt", &agenda);
                printf("Contactos cargados desde contactos.txt\n");
                break;


            case 0:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opcion no valida.\n");
        }

    } while(opcion != 0);

    return 0;
}
