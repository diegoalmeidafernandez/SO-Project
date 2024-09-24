#include "commandList.h"

#include <stdlib.h>

void createEmptyCommandList(commandList *commandList) {
    commandList -> firstCommand = NULL;
    commandList -> lastCommand = NULL;
}

void freeCommandList(commandList *commandList) {
    commandPos currentCommand = commandList -> firstCommand;
    commandPos nextCommand;

    while (currentCommand != NULL) {
        nextCommand = currentCommand->next;
        free(currentCommand);
        currentCommand = nextCommand;
    }
    commandList -> firstCommand = NULL;
    commandList -> lastCommand = NULL;
}

bool isEmptyList (commandList commandList) {
    return (commandList.firstCommand == NULL);
}

commandPos firstCommand (commandList commandList) {
    return commandList.firstCommand;
}

commandPos lastCommand (commandList commandList) {
    return commandList.lastCommand;
}

commandPos previousCommand (commandPos pos, commandList commandList) {
    commandPos commandPos =  firstCommand(commandList);

    while (commandPos != NULL && nextCommand(commandPos, commandList) != pos) {
        commandPos = nextCommand(commandPos, commandList);
    }
    return commandPos;
}

commandPos nextCommand (commandPos commandPos, commandList commandList) {
    return commandPos -> next;
}

bool createCommandNode (commandPos *commandPos) {
    *commandPos = malloc(sizeof(struct commandNode));
    return (*commandPos != NULL);
}

void insertCommand (command command, commandList *commandList) {
    commandPos pos;

    if (!createCommandNode(&pos)) {
        return;
    }

    pos -> command = command;
    pos -> next = NULL;

    if (isEmptyList(*commandList)) {
        pos -> num = 1;
        commandList->firstCommand = pos;
        commandList->lastCommand = pos;
    }else {
        pos -> num = commandList -> lastCommand -> num + 1;
        commandList->lastCommand -> next = pos;
        commandList->lastCommand = pos;
    }
}

commandPos searchCommand (int num, commandList commandList) {
    if (num < 1 || num > lastCommand(commandList) -> num || isEmptyList(commandList)) {
        return NULL;
    }

    commandPos currentCommand = firstCommand(commandList);
    while (currentCommand != NULL) {
        if (currentCommand -> num == num) {
            return currentCommand;
        }
        currentCommand = nextCommand(currentCommand, commandList);
    }
    return NULL;
}

command getCommand (commandPos commandPos, commandList commandList) {
    return commandPos -> command;
}

void printCommandList (commandList commandList) {
    if (isEmptyList(commandList)) {
        printf("Aún no se ha introducido ningún comando en la shell.\n");
    }else {
        for (commandPos currentPos = firstCommand(commandList); currentPos != NULL; currentPos = nextCommand(currentPos, commandList)) {
            command currentCommand = getCommand(currentPos, commandList);

            if (currentCommand.i == 1) {
                printf("CommNum %d:\t%s\n", currentPos -> num, currentCommand.comando);
            }else{
                printf("CommNum %d:\t%s %s\n", currentPos -> num, currentCommand.comando, currentCommand.opcion);
            }
        }
    }
}

void printLastNCommands(int n, commandList commandList) {
    if (isEmptyList(commandList)) {
        printf("Aún no se ha introducido ningún comando en la shell.\n");
        return;
    }

    commandPos lastPos = lastCommand(commandList);
    int totalCommands = lastPos->num;

    if (n > totalCommands) {
        printf("Aún no se han introducido tantos comandos en la shell.\n");
        return;
    }

    int start = totalCommands - n + 1;

    for (int i = start; i <= totalCommands; i++) {
        commandPos currentPos = searchCommand(i, commandList);

        if (currentPos != NULL) {
            command currentCommand = getCommand(currentPos, commandList);

            if (currentCommand.i == 1) {
                printf("CommNum %d:\t%s\n", currentPos->num, currentCommand.comando);
            } else {
                printf("CommNum %d:\t%s %s\n", currentPos->num, currentCommand.comando, currentCommand.opcion);
            }
        } else {
            printf("Error: no se encontró el comando número %d.\n", i);
        }
    }
}
