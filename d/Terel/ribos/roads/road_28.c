/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road_28.c
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
               "The road leads the west and northwest.\n");
    
    add_exit(RIBOS_DIR + "roads/road_27","northwest",0, 5);
    add_exit(RIBOS_DIR + "roads/road_29","west", 0, 5);
    reset_room();
}