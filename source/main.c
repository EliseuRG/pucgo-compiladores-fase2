#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "commands.h"

void interpretCommand(char* command) {
    char* token = strtok(command, " ");

    if (strcmp(token, "USE") == 0) {
        char* database = strtok(NULL, " ");
        if (database != NULL) {
            useDatabase(database);
        } else {
            printf("Erro: Nome da base de dados ausente.\n");
        }
    }
    else if (strcmp(token, "LIST") == 0) {
        listRecords();
    }
    else if (strcmp(token, "APPEND") == 0) {
        char* recordData = strtok(NULL, "\n");
        if (recordData != NULL) {
            appendRecord(recordData);
        } else {
            printf("Erro: Dados do registro ausentes.\n");
        }
    }
    else if (strcmp(token, "REPLACE") == 0) {
        char* idStr = strtok(NULL, " ");
        char* newData = strtok(NULL, "\n");
        if (idStr != NULL && newData != NULL) {
            int recordId = atoi(idStr);
            replaceRecord(recordId, newData);
        } else {
            printf("Erro: ID do registro ou novos dados ausentes.\n");
        }
    }
    else {
        printf("Comando desconhecido: %s\n", token);
    }
}

int main() {
    char command[256];

    printf("==================================================\n");
    printf("|   Pontifícia Universidade Católica de Goiás    |\n");
    printf("|   Escola Politécnica - Ciência da Computação   |\n");
    printf("|   CMP1076 - Compiladores                       |\n");
    printf("|   Docente..: Claudio Martins Garcia            |\n");
    printf("|   Acadêmico: Eliseu Rodrigues Guimarães        |\n");
    printf("|                                                |\n");
    printf("|      Bem-vindo ao interpretador DBASE!         |\n");
    printf("|                                                |\n");
    printf("==================================================\n\n");

    // COMANDOS
    printf("               Comandos disponíveis\n");
    printf("__________________________________________________\n\n");
    printf("  USE <nome>           - Seleciona a base de dados\n");
    printf("  LIST                 - Lista os registros\n");
    printf("  APPEND <dados>       - Adiciona um registro\n");
    printf("  REPLACE <id> <dados> - Atualiza um registro\n");
    printf("__________________________________________________\n\n");
    
    printf("Digite um comando:\n");

    while (1) {
        printf("> ");
        if (fgets(command, sizeof(command), stdin) != NULL) {
            command[strcspn(command, "\n")] = '\0'; // Remove newline character
            interpretCommand(command);
            printf("\n");
        } else {
            break;
        }
    }

    if (db != NULL) {
        sqlite3_close(db);
    }
    return 0;
}