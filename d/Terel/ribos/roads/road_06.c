/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road_06.c
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
    
    add_exit(RIBOS_DIR + "roads/road_07","southwest",0, 1);
    add_exit(RIBOS_DIR + "roads/road_05","east", 0, 1);
    reset_room();
}


