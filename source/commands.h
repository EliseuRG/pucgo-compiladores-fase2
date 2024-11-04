#ifndef COMMANDS_H
#define COMMANDS_H

#include <sqlite3.h>

extern sqlite3 *db;

void useDatabase(const char* database);
void listRecords();
void appendRecord(const char* recordData);
void replaceRecord(int recordId, const char* newData);

#endif // COMMANDS_H