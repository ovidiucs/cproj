#ifndef SQLTEST_H
#define SQLTEST_H
 /*!
  *  @dir include
  *  @brief include directory for header files
  *
 */
 /*!
  *  @file sqltest.h
  *  @brief Function prototypes sqlite3 test program
  *
  *  @author Ovidiu Constantinescu (ovidiucs)
  *  @bug No known bugs.
 */

 /*!
  *  @defgroup func Functions
  *  @defgroup sfunc Static Functions
 */

/*! @brief Mainmenu function
  *  Each open SQLite database is represented by a pointer
  *  to an instance of the opaque structure named "sqlite3".
  *  @ingroup func
  *  @param db an sqlite3 database
  *  @return int Success code
  */
int mainmenu(sqlite3 *db);

/*! @brief Inserting database records
  * @ingroup      func
  *
  * @param[in] db Pass a database instance
  * @param[in] data Data to be inserted
  * @return err
  * @code{.c}
  *		char iSQL = "INSERT INTO Friends(Name,Age) VALUES ('Tom',10);";
  *		int rc = dbInsert(database, iSQL );
  * @endcode
*/
int dbInsert(sqlite3 *db, char *data);

/*! @brief Select data from an sqlite3 database.
  * @ingroup      func
  *
  * @param[in] db Pass a database instance
  * @param[in] data Data to be selected
  * @return err
  * @code{.c}
  *		char iSQL = "SELECT * FROM Friends;";
  *		int rc = dbInsert(database, iSQL );
  * @endcode
  * @todo limit queries
*/
int dbSelect(sqlite3 *db, char *data);

/*! @brief Update data from an sqlite3 database.
  * @ingroup      func
  *
  * @param[in] db Pass a database instance
  * @param[in] data Data to be updated
  * @return err
  * @code{.c}
  *		char uSQL = "UPDATE Friends SET Name = 'Jerry' WHRE id = 1;";
  *		int rc = dbUpdate(database, uSQL );
  * @endcode
  * @todo limit queries
*/
int dbUpdate(sqlite3 *db, char *data);

/*! @brief Setup function for a mysqllite database
  * @ingroup      func
  *
  * @param[in] p_db -> address of pointer to a db
  * @return int -> if the database is opened or created successfully SQLITE_OK is returned otherwise an error is returned.
  * @code{.c}
  *		int rc = setup(&db);
  *
  * @endcode
*/
int setup(sqlite3 **p_db);

/*!
 * @brief traverse SELECT statements with multiple records.
 * @ingroup sfunc
 *
 * @param data Ignored in this case, see the documentation for sqlite3_exec
 * @param argc The number of columns in the result set
 * @param argv The row's data
 * @param azColName  The column names
 * @return int
 */
static int callback(void *data, int argc, char **argv, char **azColName );

#endif
