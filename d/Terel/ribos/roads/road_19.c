/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road_19.c
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
    
    add_exit(RIBOS_DIR + "roads/road_18","south",0, 2);
    add_exit(RIBOS_DIR + "roads/road_20","west", 0, 2);
    reset_room();
}