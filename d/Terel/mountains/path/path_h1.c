/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * path_h1.c  -- Mountain path
 * The mountain paths are named using a grid configuration, for example: path_ x=a-ff x=1-##.c
 * Tomas  --  Dec. 1999
 */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "path/default_pass";

public void
create_room()
{
    ::create_room();
    set_long(query_long()+".\n");


    add_exit(MOUNTAIN_DIR + "path/path_i2", "northeast", 0, cold_fatigue);
    add_exit(MOUNTAIN_DIR + "path/path_g0", "southwest", 0, cold_fatigue);

}


