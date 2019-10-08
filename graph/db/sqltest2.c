#include <stdio.h> // fprintf, printf
#include "/home/econovi/local/include/sqlite3.h"

  // Set a glbal string that will hold some SQL sample
  // data

//#define DEBUG

char *sql = "DROP TABLE IF EXISTS Friends;"
            "CREATE TABLE Friends(Id INTEGER PRIMARY KEY, Name TEXT);"
            "INSERT INTO Friends(Name) VALUES ('Tom');"
            "INSERT INTO Friends(Name) VALUES ('Rebecca');"
            "INSERT INTO Friends(Name) VALUES ('Jim');"
            "INSERT INTO Friends(Name) VALUES ('Roger');"
            "INSERT INTO Friends(Name) VALUES ('Robert');";

int main(int argc, char **argv) {

  // 1. Definitions
  // Each opened SQLite database is represented by a pointer
  // to an instance of the opaque structure named sqlite3
  sqlite3 *db;

  // Return code - if the database is opened or created succesfully SQLITE_OK is returned
  // otherwise an error is returned
  int rc;

  // This string will hold the english language of the error description
  char *errmsg;

  // 2. Get the return code from sqlite3_open
  rc = sqlite3_open(":memory:", &db);

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
        return -1;

   }

        // Let us know if the database connection was succesfull.
        printf("Opened database connection succesfully\n");

  //3.Inserting data

#ifdef DEBUG
  fprintf(stdout,"The SQL statement is: %s\n", sql);
#endif





  // Close the database connection.
  sqlite3_close(db);
  return 0;

}

int dbInsert(db) {
  int rc = sqlite3_exec(db,sql,0,0,&err_msg)

}
// Read data
// Update data
// Delete data
