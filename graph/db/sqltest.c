#include <sqlite3.h>
#include <stdio.h>

int main(void) {

    sqlite3 *db;
    sqlite3_stmt *stmt;

    //1. initiate database connection

    int rc = sqlite3_open(":memory:",&db);

    if (rc != SQLITE_OK) {
      fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);

      return 1;
    }
    // 2. routines  , db, zsql - statements to be compiled, nByte - negative read up to /0 ter
    // mination
    //  If nByte is positive, then it is the number of bytes read from zSql.
    // If nByte is zero, then no prepared statement is generated.
    // If the caller knows that the supplied string is nul-terminated, then there
    // is a small performance advantage to passing an nByte parameter that
    // is the number of bytes in the input string including the nul-terminator.
    rc = sqlite3_prepare_v2(db,"SELECT SQLITE_VERSION()",-1,&stmt, 0);
    // the sqlite3_prepare() family of routines return SQLITE_OK; otherwise an error code is returned.
    if (rc != SQLITE_OK){
      fprintf(stderr, "Fail to fetch data: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);

      return 1;
    }

    // 3
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
      fprintf(stdout, "%s\n",sqlite3_column_text(stmt, 0));
    }

  sqlite3_finalize(stmt);
  sqlite3_close(db);


    return 0;
}
