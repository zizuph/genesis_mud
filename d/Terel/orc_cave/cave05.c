/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave05.c
 *
 * A cave room near the entrance that is home to two young orcs.
 */

#include "/d/Terel/include/Terel.h"
inherit ORC_CAVE_DIR + "cave_room";

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({ORC_CAVE_DIR + "monster/orc",
	     ORC_CAVE_DIR + "monster/orc"});		 
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() + 
	     "This is a fairly small intersection. The ground is " +
	     "covered with many footprints.\n");

    add_item("footprints",
	     "There are several types.\n"+
	     "You manage to recognize the ones from orcs and a wolves.\n"+
	     "There is also a third and bigger animal-type print " +
	     "with 10 cm claws.\n");

    DARK;
    
    add_exit(ORC_CAVE_DIR +"cave03", "north");
    add_exit(ORC_CAVE_DIR +"cave04", "west");
    add_exit(ORC_CAVE_DIR +"cave06", "south");
    reset_room();
}

/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "There is a smell of foul creatures in the air.\n";
}

