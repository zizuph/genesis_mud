/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road_21.c
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
               "The road leads to the north and northeast.\n");
    
    add_exit(RIBOS_DIR + "roads/road_20","northeast",0, 2);
    add_exit(RIBOS_DIR + "roads/road_22","north", 0, 2);
    reset_room();
}