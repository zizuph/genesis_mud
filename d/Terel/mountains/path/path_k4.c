/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * path_k4.c  -- Mountain path
 * The mountain paths are named using a grid configuration, for example: path_ x=a-ff x=1-##.c
 * Tomas  --  Dec. 1999
 */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "path/default_pass";

public void
create_room()
{
    ::create_room();
    set_long("The mountain pass ends before wide open mountain range. " +
       "A dense snow-covered forest can be seen to the northeast " +
       "and a sheer cliff face to the northwest. The entrance " +
       "to the pass is to the southwest.\n");


    add_exit(MOUNTAIN_DIR + "path/path_k5", "north", 0, cold_fatigue);
    add_exit(MOUNTAIN_DIR + "path/path_j3", "southwest", 0, cold_fatigue);

}


