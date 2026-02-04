/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road_30.c
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
               "The road turns towards the west and southeast.\n");
    
    add_exit(RIBOS_DIR + "roads/road_29","southeast",0, 5);
    add_exit(RIBOS_DIR + "path1","west", 0, 5);
    reset_room();
}
