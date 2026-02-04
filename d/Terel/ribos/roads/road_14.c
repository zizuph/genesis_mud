/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road_14.c
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
               "The road leads to the northwest and east.\n");
    
    add_exit(RIBOS_DIR + "roads/road_15","northwest",0, 1);
    add_exit(RIBOS_DIR + "roads/road_13","east", 0, 1);
    reset_room();
}


