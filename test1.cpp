/*
 * =====================================================================================
 *
 *       Filename:  test1.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/27/2021 16:24:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <unistd.h>
#include "doctest.h"



SCENARIO("sleep a second") {

  GIVEN("a one secod sleep duration") {
    unsigned int duration =1 ;

    WHEN("call sleep with this duration") {
      int ret = sleep(duration) ;

      THEN("it's expected nobody interupted our rest") {
        CHECK(ret == 0);
      }
    }
  }
}
