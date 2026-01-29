/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * path2.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit PORT_DIR + "port_room";

object dog;

/*
 * Function name: reset_room
 * Description:   clone the dog if necessary
 */
public void
reset_room()
{
    if (!dog) {
        dog = clone_object(PORT_DIR + "monster/dog");
        dog -> move_living("arrives", TO);
    }
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Village path");
    set_long("You are standing on a muddy village path. The path " +
	     "continues in the east and northwest directions. There are " +
	     "houses around the path. " +
	     "There is a distinct smell in the air.\n");
    
    add_item(({"house", "houses"}), 
	     "The houses surrounding the path are all made of timber " +
	     "from the forest north of the village.\n");

    add_exit(PORT_DIR + "path3", "northwest", 0);
    add_exit(PORT_DIR + "path1", "east",      0);
    set_alarm(1.0, -1.0, "reset_room");
}
