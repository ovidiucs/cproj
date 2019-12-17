 /**
 *  @dir tests
 *  @brief Unit testing folder
 *  @details No other details
 */

#include <criterion/criterion.h>
#include <sqlite3.h>
#include "../include/sqltest.h"

#include <stdio.h> // fprintf, printf
#include <stdlib.h> // exit,

/**
* Variables used by tests
*/

Test(tSuite_1, t_001){
  sqlite3 *db = NULL;
  // test contents
  cr_assert(setup(db) == 0);
}

/**
* Setup and teardown
*/

