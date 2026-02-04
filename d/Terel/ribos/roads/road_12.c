/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road_12.c
 *
 * 
 */

#include "/d/Terel/include/Terel.h"
inherit RIBOS_DIR +"roads/rc_road";
#include <ss_types.h>
#include <stdproperties.h>


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() + 
               "The road leads to the northwest and south.\n");
    
    add_exit(RIBOS_DIR + "roads/road_13","northwest",0, 1);
    add_exit(RIBOS_DIR + "roads/road_11","south", 0, 1);
    reset_room();
}


