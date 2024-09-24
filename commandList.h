
#ifndef COMMANDLIST_H
#define COMMANDLIST_H
#include "types.h"
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct commandNode *commandPos;
struct commandNode {
    int num;
    command command;
    commandPos next;
};

typedef struct commandList {
    commandPos firstCommand;
    commandPos lastCommand;
}commandList;

void createEmptyCommandList (commandList *commandList);

void freeCommandList (commandList *commandList);

bool isEmptyList (commandList commandList);

commandPos firstCommand (commandList commandList);

commandPos lastCommand (commandList commandList);

commandPos previousCommand (commandPos commandPos, commandList commandList);

commandPos nextCommand (commandPos commandPos, commandList commandList);

bool createCommandNode (commandPos *commandPos);

void insertCommand (command command, commandList *commandList);

commandPos searchCommand (int num, commandList commandList);

command getCommand (commandPos commandPos, commandList commandList);

void printCommandList (commandList commandList);

void printLastNCommands (int n, commandList commandList);

#endif //COMMANDLIST_H