/*
 * /d/Gondor/common/guild2/lib/morgul_lieutenant.h
 *
 * The file for various support for the Lieutenant
 *
 * Toby, 6 October 2006
 *
 * 
 */
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

private nomask int lieutenant_test();

private nomask int lieutenant_test()
{
    if(this_player()->query_morgul_level() == 24)
       return 1;
}

