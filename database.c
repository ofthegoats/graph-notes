#include "database.h"

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

int db_prepare(const char* filename)
{
    sqlite3* db;
    char* err_msg = NULL;
    int rc;
    const char* sql = "PRAGMA foreign_keys = ON;"        // referential integrity
                      "CREATE TABLE IF NOT EXISTS Node(" // node entity
                      "id INTEGER NOT NULL,"
                      "filepath TEXT NOT NULL,"
                      "PRIMARY KEY(id)"
                      ");"
                      "CREATE TABLE IF NOT EXISTS Edge(" // edge entity
                      "src INTEGER NOT NULL,"
                      "dest INTEGER NOT NULL,"
                      "PRIMARY KEY(src, dest),"
                      "FOREIGN KEY(src) REFERENCES Node(id),"
                      "FOREIGN KEY(dest) REFERENCES Node(id)"
                      ");";
    rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "opening database failed\n");
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "preparing database failed: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    sqlite3_close(db);
    return DB_OP_SUCCESS;
}

int db_add_node(const char* filename, void* id, const char* path)
{
    sqlite3* db;
    char* err_msg = NULL;
    int rc;
    char* sql;
    sprintf(sql,
            "PRAGMA foreign_keys = ON;INSERT INTO Node(id, filepath) VALUES(%d, %s);",
            (int)id, path);
    rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "opening database failed\n");
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "inserting into node failed: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    sqlite3_close(db);
    return DB_OP_SUCCESS;
}

int db_remove_node(const char* filename, void* id)
{
    sqlite3* db;
    char* err_msg = NULL;
    int rc;
    char* sql;
    sprintf(sql, "PRAGMA foreign_keys = ON;DELETE FROM Node WHERE id = %d;", (int)id);
    rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "opening database failed\n");
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "deleting from node failed: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    sqlite3_close(db);
    return DB_OP_SUCCESS;
}

int db_add_edge(const char* filename, void* src, void* dest)
{
    sqlite3* db;
    char* err_msg = NULL;
    int rc;
    char* sql;
    sprintf(sql, "PRAGMA foreign_keys = ON;INSERT INTO Edge(src, dest) VALUES (%d, %d);",
            (int)src, (int)dest);
    rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "opening database failed\n");
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "inserting into edge failed: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    sqlite3_close(db);
    return DB_OP_SUCCESS;
}

int db_remove_edge(const char* filename, void* src, void* dest)
{
    sqlite3* db;
    char* err_msg = NULL;
    int rc;
    char* sql;
    sprintf(sql, "PRAGMA foreign_keys = ON;DELETE FROM Edge WHERE src = %d AND dest = %d",
            (int)src, (int)dest);
    rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "opening database failed\n");
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "deleting from edge failed: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return DB_OP_FAILURE;
    }
    sqlite3_close(db);
    return DB_OP_SUCCESS;
}
