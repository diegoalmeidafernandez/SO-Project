#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "commandList.h"
#include "types.h"
#include <sys/utsname.h>

#define MAX_TROZOS 10
#define MAX_STRING 15
#define MAX_COMMANDS 14
#define NAME0 "Diego Adrián Almeida Fernández"
#define NAME1 "Juan Melón Domínguez"
#define LOGIN0 "diego.almeida.fernandez@udc.es"
#define LOGIN1 "j.melon@udc.es"

//DECLARACIÓN DE FUNCIONES

void imprimirPrompt();

int TrocearCadena(char *cadena, char *trozos[]);

command leerEntrada();

void imprimirError(int opcion);

void authors(int opcion);

void date(int opcion);

void historic(int opcion, int num, char *commands[MAX_COMMANDS], commandList *commandList);

//void infosys();

void help(int opcion, char *commands[MAX_COMMANDS]);

int procesarEntrada(command command, char *commands[MAX_COMMANDS], commandList *commandList);

/////////////////////////////////////////////////////////////////////////////////////////////

//CODIFICACION DE FUNCIONES

void imprimirPrompt() {
    printf("~$ ");
}

int TrocearCadena(char *cadena, char *trozos[]) {
    int i = 0;

    if ((trozos[i] = strtok(cadena, " \n\t")) == NULL) {
        return 0;
    }
    while ((trozos[++i] = strtok(NULL, " \n\t")) != NULL && i < MAX_TROZOS);
    return i;
}

command leerEntrada() {
    char entrada[15];
    char *trozos[3];
    command command;

    fgets(entrada, MAX_STRING, stdin);
    int i = TrocearCadena(entrada, trozos);

    command.i = i;
    if (i > 0) {
        strcpy(command.comando, trozos[0]);

        if (i > 1) {
            strcpy(command.opcion, trozos[1]);
        } else {
            strcpy(command.opcion, "");
        }
    } else {
        strcpy(command.comando, "");
        strcpy(command.opcion, "");
    }
    return command;
}

void imprimirError(int opcion) {
    if (opcion == 0) {
        printf("Comando no válido.\n");
    }else {
        printf("Opción no válida.\n");
    }
}

void authors(int opcion) {
    switch (opcion) {
        case 0:
            printf(NAME0 "\t" NAME1 "\n" LOGIN0 "\t" LOGIN1 "\n");
            break;
        case 1:
            printf(NAME0 "\t" NAME1 "\n");
            break;
        case 2:
            printf(LOGIN0 "\t" LOGIN1 "\n");
            break;
        default:
            imprimirError(1);
            break;
    }
}

void date(int opcion) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    char buffer[80];

    switch (opcion) {
        case 0:
            strftime(buffer, sizeof(buffer), "Fecha:\t%d/%m/%Y\nHora:\t%H:%M:%S", tm_info);
            printf("%s\n", buffer);
            break;
        case 1:
            strftime(buffer, sizeof(buffer), "%H:%M:%S", tm_info);
            printf("Hora:\t%s\n", buffer);
            break;
        case 2:
            strftime(buffer, sizeof(buffer), "%d/%m/%Y", tm_info);
            printf("Fecha:\t%s\n", buffer);
            break;
        default:
            imprimirError(1);
            break;
    }
}

void historic(int opcion, int num, char *commands[MAX_COMMANDS], commandList *commandList) {
    switch (opcion) {
        case 0: printCommandList(*commandList);
            break;
        case 1: commandPos pos = searchCommand(num, *commandList);
                if (pos != NULL) {
                    command command = getCommand(pos, *commandList);
                    procesarEntrada(command, commands, commandList);
                }
            break;
        case 2: /*for (commandPos currentPos = searchCommand(num, *commandList); currentPos != NULL; currentPos = nextCommand(currentPos, *commandList)) {
                    if (currentPos -> command.i == 1) {
                        printf("CommNum %d:\t%s\n", currentPos->num, currentPos -> command.comando);
                    }else {
                        printf("CommNum %d:\t%s %s\n", currentPos->num, currentPos -> command.comando, currentPos -> command.opcion);
                    }
                }*/
            break;
        default: imprimirError(1);
            break;
    }
}

void infosys() {
    struct utsname buffer;

    if (uname(&buffer) != 0) {
        perror("uname");
        return;
    }

    printf("Sistema operativo: %s\n", buffer.sysname);
    printf("Nombre del nodo:   %s\n", buffer.nodename);
    printf("Versión del kernel:%s\n", buffer.release);
    printf("Versión del SO:    %s\n", buffer.version);
    printf("Arquitectura:      %s\n", buffer.machine);
}

void help(int opcion, char *commands[MAX_COMMANDS]) {
    switch (opcion) {
        case 0:
            printf(
                "%s:\tImprime los nombres y logins de los autores del programa.\n%s -l:\tImprime solamente los logins.\n%s -n:\tImprime solamente los nombres.\n",
                commands[0], commands[0], commands[0]);
        break;
        case 1:
            printf("%s:\tImprime el PID del proceso ejecutandose en la shell.\n", commands[1]);
        break;
        case 2:
            printf("%s:\tImprime el PID del proceso padre de la shell.\n", commands[2]);
        break;
        case 3:
            printf("%s [dir]:\tCambia el directorio actual de trabajo de la shell al deseado.\n", commands[3]);
        break;
        case 4:
            printf(
                "%s:\tImprime la fecha actual en formato DD/MM/YYYY y la hora actual en formato hh:mm:ss.\n%s -d:\tImprime la fecha actual en formato DD/MM/YYYY.\n%s -t:\tImprime la hora actual en formato hh:mm:ss.\n",
                commands[4], commands[4], commands[4]);
        break;
        case 5:
            printf(
                "%s:\tImprime todos los comandos que se han introducido con su número de orden.\n%s N:\tRepite el comando número N.\n%s -N:\tImprime solamente los últimos N-comandos.\n",
                commands[5], commands[5], commands[5]);
        break;
        case 6:
            printf("%s [file] mode:\tAbre un archivo y lo añade.\n", commands[6]);
        break;
        case 7:
            printf("%s [df]:\tCierra el descriptor de archivo df y elimina el elemento correspondiente de la lista.\n", commands[7]);
        break;
        case 8:
            printf("%s [df]:\tDuplica el descriptor de archivo.\n", commands[8]);
        break;
        case 9:
            printf("%s:\tImprime la información de la máquina que está ejecutando la shell.\n", commands[9]);
        break;
        case 10:
            printf("%s:\t Muestra por pantalla una lista de los comandos disponibles.\n%s [cmd]:\tBrinda una pequeña descripción del uso de cada comando.\n", commands[10], commands[10]);
        break;
        case 11:
            printf("%s:\tCierra el terminal.\n", commands[11]);
        break;
        case 12:
            printf("%s:\tCierra el terminal.\n", commands[12]);

        break;
        case 13:
            printf("%s:\tCierra el terminal.\n", commands[13]);

        break;
        case 14:
            printf("Comandos disponibles:\n");
        for (int i = 0; i < MAX_COMMANDS; i++) {
            printf("%s\n", commands[i]);
        }
        break;
        default:
            imprimirError(1);
        break;
    }
}

int procesarEntrada(command command, char *commands[MAX_COMMANDS], commandList *commandList) {
    int i = 0;

    if (strcmp(command.comando, commands[0]) == 0) { // authors
        if (command.i == 1) {
            authors(0);
        } else if (strcmp(command.opcion, "-n") == 0) {
            authors(1);
        } else if (strcmp(command.opcion, "-l") == 0) {
            authors(2);
        } else {
            authors(3);
        }
        insertCommand(command, commandList);
        return i;
    }

    if (strcmp(command.comando, commands[4]) == 0) { // date
        if (command.i == 1) {
            date(0);
        }else {
            if (strcmp(command.opcion, "-t") == 0) {
                date(1);
            }else {
                if (strcmp(command.opcion, "-d") == 0) {
                    date(2);
                }else {
                    date(3);
                }
            }
        }
        insertCommand(command, commandList);
        return i;
    }

    if (strcmp(command.comando, commands[5]) == 0) {
        if (command.i == 1) {
            historic(0, 0, commands, commandList);
        }else {
            int num;
            if (sscanf(command.opcion, "%d", &num) == 1) {
                if (num >= 0) {
                    historic(1, num, commands, commandList);
                }else {
                    historic(2, num, commands, commandList);
                }
            }else {
                historic(3, num, commands, commandList);
            }
        }
        insertCommand(command, commandList);
        return i;
    }

    if (strcmp(command.comando, commands[9]) == 0) { // infosys
        //infosys();
        insertCommand(command, commandList);
        return i;
    }

    if (strcmp(command.comando, commands[10]) == 0) { // help
        if (command.i == 1) {
            help(14, commands);
        }else {
            for (int j = 0; j < MAX_COMMANDS; j++) {
                if (strcmp(command.opcion, commands[j]) == 0) {
                    help(j, commands);
                    return i;
                }
            }
            printf("Opción no válida.\n");
        }
        insertCommand(command, commandList);
        return i;
    }

    if ((strcmp(command.comando, commands[11]) == 0) || // exit
       (strcmp(command.comando, commands[12]) == 0) || // quit
       (strcmp(command.comando, commands[13]) == 0)) { //bye
        i = 1;
        insertCommand(command, commandList);
        return i;
    }
    imprimirError(0);
    return i;
}

int main() {
    bool terminado = false;
    commandList commandList;
    createEmptyCommandList(&commandList);
    char *commands[MAX_COMMANDS] = {
        "authors", "pid", "ppid", "cd", "date", "historic", "open", "close",
        "dup", "infosys", "help", "exit", "quit", "bye"
    };

    while (!terminado) {
        imprimirPrompt();
        command command = leerEntrada();

        if (command.i > 0) {
            int i = procesarEntrada(command, commands, &commandList);

            if (i == 1) {
                terminado = true;
            }
        }
    }
    freeCommandList(&commandList);
    return 0;
}