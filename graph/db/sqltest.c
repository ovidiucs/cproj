#include <stdio.h> // fprintf, printf
#include "../../include/sqlite3.h"

  // Set a glbal string that will hold some SQL sample
  // data

#define DEBUG 0
#define MEMWRITE 0

  // sample test data
char *sSql = "DROP TABLE IF EXISTS Friends;"
            "CREATE TABLE Friends(Id INTEGER PRIMARY KEY, Name TEXT, Age INTEGER);"
            "INSERT INTO Friends(Name,Age) VALUES ('Tom',10);"
            "INSERT INTO Friends(Name,Age) VALUES ('Rebecca',32);"
            "INSERT INTO Friends(Name,Age) VALUES ('Jim',34);"
            "INSERT INTO Friends(Name,Age) VALUES ('Roger',12);"
            "INSERT INTO Friends(Name,Age) VALUES ('Robert',16);";

// --------------------------------------------------------------------------------------------------

int dbInsert(sqlite3 *db, char *data);
int dbSelect(sqlite3 *db, char *data);
int (*callback)(int row);

// --------------------------------------------------------------------------------------------------

int main(int argc, char **argv) {

  // 1. Definitions
  // Each opened SQLite database is represented by a pointer
  // to an instance of the opaque structure named sqlite3
  sqlite3 *db;

  // Return code - if the database is opened or created succesfully SQLITE_OK is returned
  // otherwise an error is returned
  int rc;

  // This string will hold the english language of the error description
  char *zErrMsg;

  // Ensure that the proper arguments are given.`
  if (argc != 3) {
      fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
      // Return error code
      return 1;

  }

  // 2. Get the return code from sqlite3_open

#if MEMWRITE == 1
  rc = sqlite3_open(":memory:", &db);
#else
  rc = sqlite3_open("sqltest.db", &db);
#endif

  // Test that the return code is OK
  if (rc != SQLITE_OK) {

      fprintf(stderr,"Error opening sqlite3 database in memory %s\n",sqlite3_errmsg(db) );
      fprintf(stderr,"Clearing resoursces used for sqlite3_open\n");

      // Whether or not an error occurs when it is opened,
      // resources associated with the database connection
      // handle should be released by passing it to
      // sqlite3_close() when it is no longer required.
        sqlite3_close(db);
        fprintf(stderr,"Database closed.\n");

            // Return error code
        return 1;

   }

        // Let us know if the database connection was succesfull.
        fprintf(stdout,"Opened database connection succesfully\n");

  // Display the SQLite version - debug

#if DEBUG == 1
  // The sqlite3_stmt represents a single SQL statement
  sqlite3_stmt *res;
  // Seeing if the global variable is printed
  fprintf(stdout,"The SQL statement is: %s\n", sSql);
  // The sqlite3_prepare is the constructor for the sqlite3_stmt
  // compile sql text into byte code that will do the work for querying
  // 1st arg - database connection - obtained  from sqlite3_open()
  // 2nd arg - zSql - statement to be compiled
  // 3rd arg - nByte - negative -> read up to the first zero terminator
  // 4th arg - *ppStmt pointing to a compiled statement that can be run with sqlite3_step()
  // the calling proc is responsable for deleting the SQL statement with sqlite3_finalize()
  // 5th arg - pzTail point to the first byte past the end of the first SQL  staement
  rc = sqlite3_prepare_v2(db, "SELECT sqlite_version()", -1, &res, 0);
  fprintf(stderr,"%d\n\r",rc);
  if (rc == SQLITE_ROW) {
          fprintf(stdout,"SQLite Version is: %s\n",sqlite3_column_text(res,0));
  }
#endif

  // 3.Inserting data - calls dbInsert
  // 1st arg - open database handle
  // 2nd arg - string to insert
  if (!dbInsert(db,sSql) ) {
        fprintf(stdout,"Inserted data succesfully\n");
  }
  char *zSelect = "SELECT * from Friends;";
  if (!dbSelect(db,zSelect) ) {
        fprintf(stdout,"Select data succesfully\n");
        }
  // Close the database connection.
  sqlite3_close(db);
  return 0;

}
// --------------------------------------------------------------------------------------------------
// Inserting data

int dbInsert(sqlite3 *db, char *data) {
  // Check that a database was passed and we have an open database connection
  // Note: do not close db connection while sqlite3_exec is running
  // Note: do not modify the sql statement while sqlite3_exec is running
  if ( db == NULL ) {
    fprintf(stderr,"Error with database access, exiting\n");
    return 1;
  }
  char *zErrMsg = NULL;
  // wrapper function does sqlite3_prepare(),sqlite3_step(), sqlite3_column(), sqlite3_finalize()
  // 1st arg - an open database
  // 2nd arg - SQL to be evaluated
  // 3rd arg - callback function - invoked for each result row comming out of the evaluated statements
  // int (*callback)(void*, int, char**, char**)
  // 4th arg - 1st arg to callback function - relaying the argument to it.
  // 5th arg - error message writte (char **)
  int rc = sqlite3_exec(db,data,0,0,&zErrMsg);
  if ( rc != SQLITE_OK ) {
         fprintf(stderr, "SQL error occured: %s\n", zErrMsg);
         sqlite3_free(zErrMsg);
         sqlite3_close(db);

         return 1;
  }

  return 0;
}

// --------------------------------------------------------------------------------------------------
// Select data

// 1st arg - an opened db
// 2nd arg - select statement

int dbSelect(sqlite3 *db, char *data) {
  // Note: does not use the wrapper function (test) -
  // pointer to a prepared statement - called by prepare
  sqlite3_stmt *res;

  // Check that a database was passed and we have an open database connection
  if ( db == NULL ) {
    fprintf(stderr,"Error with database access, exiting\n");
    return 1;
  }
  char *zErrMsg = NULL;
  int rc = 0;
  //1. Prepare
  // int rc = sqlite3_prepare_v2(db,data,-1,&res,0);
#if DEBUG == 1
  fprintf(stderr,"Database is: %s ; Data is: %s, ; Return Code is: %d ; stmt is %p\n",
                  db,data,rc,res);
#endif

  rc = sqlite3_prepare_v2(db, data, -1, &res, 0);

#if DEBUG == 1
  fprintf(stderr,"Database is: %s ; Data is: %s, ; Return Code is: %d ; stmt is %p\n",
                  db,data,rc,res );
#endif
  // On success the sqlite3_prepare() returns SQLITE_OK
  if ( rc != SQLITE_OK ) {
         fprintf(stderr, "SQL error occured: %s with code %d\n", zErrMsg, rc);
         sqlite3_free(zErrMsg);
         sqlite3_close(db);

         return 1;
  }

  //2.Step
  // 1st arg - pointed data by sqlite_stmt
  // returns int
  rc = sqlite3_step(res);
  if ( rc == SQLITE_ROW ) {
          // we got a row
    callback(rc);
  }//  fprintf(stdout, "%s",rc);

  // Finalize
  rc = sqlite3_finalize(res);
  if ( rc != SQLITE_OK ) {
          fprintf(stderr, "SQL error occured: %s with code %d\n", zErrMsg, rc);
          sqlite3_free(zErrMsg);
          sqlite3_close(db);

          return 1;
    }

  return 0;
}

void (*callback)(int row) {
  while (row == 100) {
   fprintf(stdout,"SQLite Version is: %s\n",sqlite3_column_text(res,1));)
  }
}
// Update data
// Delete data
