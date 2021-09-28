/*
 * =====================================================================================
 *
 *       Filename:  test2.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/27/2021 16:24:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "doctest.h"
#include <unistd.h>

TEST_CASE("sleep a second") {
    CHECK(sleep(1) == 0);
}
