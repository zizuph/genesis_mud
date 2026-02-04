/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road_20.c
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
               "The road leads to the southwest and east.\n");
    
    add_exit(RIBOS_DIR + "roads/road_19","east",0, 2);
    add_exit(RIBOS_DIR + "roads/road_21","southwest", 0, 2);
    reset_room();
}
