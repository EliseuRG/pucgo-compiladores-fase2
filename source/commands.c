#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "commands.h"

sqlite3 *db = NULL;
static char *errMsg = 0;

void createTableIfNotExists() {
    const char* sql = "CREATE TABLE IF NOT EXISTS records ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "data TEXT NOT NULL);";

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar tabela: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Tabela criada com sucesso (ou já existia).\n");
    }
}

void useDatabase(const char* databaseName) {
    int rc = sqlite3_open(databaseName, &db);
    if (rc) {
        fprintf(stderr, "Não foi possível abrir o banco de dados: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Banco de dados aberto com sucesso: %s\n", databaseName);
        createTableIfNotExists();
    }
}

void listRecords() {
    if (db == NULL) {
        printf("Erro: Nenhum banco de dados aberto.\n");
        return;
    }

    const char* sql = "SELECT * FROM records;";
    sqlite3_stmt *stmt;

    printf("Listando registros...\n");
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a declaração: %s\n", sqlite3_errmsg(db));
        return;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *data = sqlite3_column_text(stmt, 1);
        printf("%d: %s\n", id, data);
    }

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erro ao iterar sobre os registros: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

void appendRecord(const char* recordData) {
    if (db == NULL) {
        printf("Erro: Nenhum banco de dados aberto.\n");
        return;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO records (data) VALUES ('%s');", recordData);

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao inserir registro: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Registro adicionado.\n");
    }
}

void replaceRecord(int recordId, const char* newData) {
    if (db == NULL) {
        printf("Erro: Nenhum banco de dados aberto.\n");
        return;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "UPDATE records SET data = '%s' WHERE id = %d;", newData, recordId);

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao atualizar registro: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Registro %d atualizado.\n", recordId);
    }
}