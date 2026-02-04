/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road_02.c
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
               "To the east you can see the western gate of Calathin. "+
               "The road continues to the west.\n");
    
    add_exit(RIBOS_DIR + "roads/road_01","east",0, 1);
    add_exit(RIBOS_DIR + "roads/road_03","west", 0, 1);
    reset_room();
}


