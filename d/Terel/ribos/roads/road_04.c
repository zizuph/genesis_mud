/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road_04.c
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
               "The road leads to the southeast and northwest.\n");
    
    add_exit(RIBOS_DIR + "roads/road_03","southeast",0, 5);
    add_exit(RIBOS_DIR + "roads/road_05","northwest", 0, 5);
    reset_room();
}


