/*!
 * @dir src
 * @brief source directory
 * @file
 * @brief the main project file
 */

#include <stdio.h> 								// fprintf, printf
#include <stdlib.h> 							// exit,
#include <readline/readline.h>  	// readline
#include <readline/history.h> 		//
#include <sqlite3.h>							//
#include "sqltest.h"    //

/*! @defgroup defines Defines
 * @{ */

/** @brief Enable or disable debug*/
#define DEBUG 0
/** @brief Enable or disable writing to memory*/
#define MEMWRITE 0

/*!
 @} */

/*! @defgroup globals Global Variables
 * @{ */

/** @brief SQL insert table entries **/
static char *sSql = "DROP TABLE IF EXISTS Friends;"
		"CREATE TABLE Friends(Id INTEGER PRIMARY KEY, Name TEXT, Age INTEGER);"
		"INSERT INTO Friends(Name,Age) VALUES ('Tom',10);"
		"INSERT INTO Friends(Name,Age) VALUES ('Rebecca',32);"
		"INSERT INTO Friends(Name,Age) VALUES ('Jim',34);"
		"INSERT INTO Friends(Name,Age) VALUES ('Roger',12);"
		"INSERT INTO Friends(Name,Age) VALUES ('Robert',16);";

/** @brief SQL Update function **/
static char *uSql = "UPDATE Friends SET Name = 'Jerry' WHRE id = 1;";

/*!
 @} */

/*!
	*  @brief	Main program function.
	*  @returns int	error code
	*  @code{.shell-session}
	*  ./sqltest
	* Opened database connection succesfully
	*
	* -----------------------
	* 1. View database entries
	* 2. Update database records
	* 3. Delete database record
	* 4. Insert test data.
	*         41. From Command Line.
	*         42. From File.
	* 5. Quit
	*
	* -----------------------
	* Enter a choice >
	*  @endcode
	*
*/

int main(int argc, char **argv) {
	//  Each opened SQLite database is represented by a pointer
  //  to an instance of the opaque structure named sqlite3

  sqlite3 *db = NULL;
  int rc;

  // This string will hold the english language of the error description
  char *zErrMsg;

  // Ensure that the proper arguments are given.
  if (argc != 3 && argc != 1) {
      fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
      // Return error code
      return 1;
  } else if (argc == 3) {
			rc = setup(&db);
  } else {
			rc = setup(&db);
      // Execute the main menu function
	    mainmenu(db);
  }
  return 0;
}

int setup(sqlite3 **p_db) {

	sqlite3 *db = NULL;
  int rc;

#if MEMWRITE == 1
	  rc = psqlite3_open(":memory:", &db);
#else
	  rc = sqlite3_open("sqltest.db", &db);
#endif
	  // Test that the return code is OK
	  if (rc != SQLITE_OK) {

	      fprintf(stderr,"Error opening sqlite3 database in memory %s\n",sqlite3_errmsg(db) );
	      fprintf(stderr,"Clearing resoursces used for sqlite3_open\n");
				/*
					* Whether or not an error occurs when it is opened,
					* resources associated with the database connection
					* handle should be released by passing it to
					* sqlite3_close() when it is no longer required.
				*/
				sqlite3_close(db);
				fprintf(stderr,"Database closed.\n");

	   }
		// Let us know if the database connection was succesfull.
		fprintf(stdout,"Opened database connection succesfully\n");

	  // Display the SQLite version - debug

#if DEBUG == 1
	  // The sqlite3_stmt represents a single SQL statement
	  sqlite3_stmt *res;
	  // Seeing if the global variable is printed
	  fprintf(stdout,"The SQL statement is: %s\n", sSql);

	  /*
			* The sqlite3_prepare is the constructor for the sqlite3_stmt
			* compile sql text into byte code that will do the work for querying
			* 1st arg - database connection - obtained  from sqlite3_open()
			* 2nd arg - zSql - statement to be compiled
			* 3rd arg - nByte - negative -> read up to the first zero terminator
			* 4th arg - *ppStmt pointing to a compiled statement that can be run with sqlite3_step()
			* the calling proc is responsable for deleting the SQL statement with sqlite3_finalize()
			* 5th arg - pzTail point to the first byte past the end of the first SQL  staement
		*/
	  rc = sqlite3_prepare_v2(db, "SELECT sqlite_version()", -1, &res, 0);
	  fprintf(stderr,"%d\n\r",rc);
	  if (rc == SQLITE_ROW) {
		  fprintf(stdout,"SQLite Version is: %s\n",sqlite3_column_text(res,0));
	  }
#endif

	  *p_db = db;
	  return 0;
}

int mainmenu(sqlite3 *db) {
	char menu[] =
			"\n-----------------------\n"
			"1. View database entries\n"
			"2. Update database records\n"
			"3. Delete database record\n"
			"4. Insert test data.\n"
			"\t41. From Command Line.\n"
			"\t42. From File.\n"
			"5. Quit\n"
			"\n-----------------------\n";

	char response[1024];
	char *buf;
	int rc=0;
	unsigned int item = 0;
	for (;;) {
		fputs(menu,stdout);

		fputs("Enter a choice > ",stdout);
//		fflush();
		if(fgets(response, sizeof(response), stdin) == NULL) {
			exit(1);
		}
		if(sscanf(response,"%u",&item) != 1) {
			fprintf(stderr,"Error reading commnad. Please enter a valid integer\n");
		} else {
		switch (item) {
			case 1:
				buf = readline("Enter query: > ");
				dbSelect(db, buf);
				free(buf);
				break;
			case 2:
				fputs("dbDelete`\n",stdout);
				fgets(response, sizeof(response), stdin);
				//dbDelete(db, response);
				break;
			case 3:
				fputs("dbUpdate()\n",stdout);
				break;
			case 41:
				buf = readline("Insert test data via command.\n");
					if (!dbInsert(db,buf) ) {
					fprintf(stdout,"Inserted data OK\n");
					}
				break;
			case 42:
					if (!dbInsert(db,sSql) ) {
					fprintf(stdout,"Inserted data succesfully\n");
					}
				break;
			case 5:
				fputs("Quiting.\n",stdout);
				goto Exit;
			default:
				fputs("Please choose a valid menu option\n",stdout);
			}
		}
	}
		Exit:
	return 0;
}
// --------------------------- End MainMenu ---------------------------

int dbInsert(sqlite3 *db, char *data) {

	/*
   * Check that a database was passed and we have an open database connection
   * Note: do not close db connection while sqlite3_exec is running
   * Note: do not modify the sql statement while sqlite3_exec is running
	*/
  if ( db == NULL ) {
    fprintf(stderr,"Error with database access, exiting\n");
    return 1;
  }
  char *zErrMsg = NULL;
	/*
   * wrapper function does sqlite3_prepare(),sqlite3_step(), sqlite3_column(), sqlite3_finalize()
   * 1st arg - an open database
   * 2nd arg - SQL to be evaluated
   * 3rd arg - callback function - invoked for each result row comming out of the evaluated statements
   * int (*callback)(void*, int, char**, char**)
   * 4th arg - 1st arg to callback function - relaying the argument to it.
   * 5th arg - error message writte (char **)
	*/
		int rc = sqlite3_exec(db,data,0,0,&zErrMsg);
		/*
		 * @todo When there is an SQL syntax error
		 * the database closes. Syntax errors should not close the DB .
		 * Determine the correct behavior.
		*/
			if ( rc != SQLITE_OK ) {
				fprintf(stderr, "SQL error occured: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);

				return rc;
				}
  return 0;
}

// --------------------------- dbSelect ---------------------------


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

	 return 1;
  }
	/*
   * 2.Step
   * 1st arg - pointed data by sqlite_stmt
   * returns integer - the result of the operation
   * Useful routines;
	 */
  rc = sqlite3_step(res);
		  for ( int i = 0; i < sqlite3_data_count(res) ; i++ ) {
	       fprintf(stdout,"| %s\t",sqlite3_column_origin_name(res,i));
	  }
	  fprintf(stdout,"\r\n");
  while ( rc == SQLITE_ROW ) {
	  int i = 0;
  	// If the return code is SQLITE_ROW we can now iterate thorugh the entire column, row by row
    // - sqlite3_data_count() will return 0 if sqlite3_step was not called
	  for ( i = 0; i < sqlite3_data_count(res) ; i++ ) {
	       fprintf(stdout,"| %s\t",sqlite3_column_text(res,i));
	   }
	  fprintf(stdout,"\r\n");
  // Grab next row
	 rc = sqlite3_step(res);
   }
  // Finalize - clean up after using.
  rc = sqlite3_finalize(res);
  if ( rc != SQLITE_OK ) {
	  fprintf(stderr,"SQL error occured on sqlite3_finalize(): %s with code: %d\n",zErrMsg, rc);
	  sqlite3_free(zErrMsg);

	  return 1;
  }

  return 0;
}

#if 0
static int callback(void *data, int argc, char **argv, char **azColName ) {
  return 0;
}
#endif
// --------------------------- dbUpdate ---------------------------
int dbUpdate (sqlite3 *db, char *data) {
   sqlite3_stmt *res;
   // Vars
   const char *msg = "Called callback function\n";
   char *zErrMsg = NULL;
   int rc = 0;
   // Check that db is presnet
   if ( db == NULL ) {
    fprintf(stderr,"Error with database access, exiting\n");
    return 1;
   }
   // Prepare & check
   rc = sqlite3_prepare_v2(db, data, -1, &res, 0);
			if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error occured: %s with code %d\n", zErrMsg, rc);
			sqlite3_free(zErrMsg);

			return 1;
			}
//    rc = sqlite3_exec (db, data,callback,(void*) msg, &zErrMsg);
    fprintf(stdout,"%d\n",rc);

   return 0;
}
// Delete data
