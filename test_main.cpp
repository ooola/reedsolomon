/*
 * =====================================================================================
 *
 *       Filename:  test_main.cpp
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  09/27/2021 16:23:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

int main(int argc, char** argv) {
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    return context.run(); 
}
