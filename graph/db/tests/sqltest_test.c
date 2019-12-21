 /**
 *  @dir tests
 *  @brief Unit testing folder
 *  @details No other details
 */
#include <sqlite3.h>
#include "sqltest.h"



#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <stdio.h> // fprintf, printf
#include <stdlib.h> // exit,



// --------------------------------------------------------
// ------ Some values and variables used by tests ---------
// --------------------------------------------------------
  sqlite3 *db = NULL;

// --------------------------------------------------------
// ------------- Setup and Teardown Functions -------------
// --------------------------------------------------------
/* Setup function - initializes the database */
void t_setup(){
}
/* Teardown function - closes the database */
void teardown(){
}

//Test(tSuite_1, t_001, .init=t_setup, .fini=teardown){
Test(asserts, t_001, .init=t_setup, .fini=teardown){
  // test contents
  int rc = setup(&db);
  cr_assert(rc == 0);
}

Test(tSuite_2, t_002) {
    int *ptr = NULL;
    *ptr = 42;
}
/**
* Setup and teardown
*/

