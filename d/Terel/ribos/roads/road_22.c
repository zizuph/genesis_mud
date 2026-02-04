/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road_22.c
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
               "The road leads to the west and south.\n");
    
    add_exit(RIBOS_DIR + "roads/road_21","south",0, 1);
    add_exit(RIBOS_DIR + "roads/road_23","west", 0, 1);
    reset_room();
}