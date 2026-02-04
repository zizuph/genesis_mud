/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * court.c
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({CASTLE_DIR + "monster/okayguard",
	     CASTLE_DIR + "monster/weakguard"});		 
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Castle courtyard");

    set_long("You are standing in the middle of a marvelous " +
	     "courtyard.  Its grass is green, its shrubs are trimmed " +
	     "in various shapes, and the buildings around it are " +
	     "covered in ivy.  There are several trees here that " +
	     "provide shade for a sunny day, although it usually " +
	     "does not get too hot.  You can see a large passageway " +
	     "to the north, many rows of seats to your east, a small " +
	     "passage to the west, a staircase up and the exit is to " +
	     "the south.\n");

    add_item(({"shrub", "shrubs", "shapes"}),
	     "These shrubs are well trimmed, and shaped.  You can " +
	     "see a horse, a Knight, and a large sword.\n");

    add_item(({"courtyard", "yard", "court"}),
	     "This is a fine green lawn with several buildings " +
	     "surrounding it.  The shrubs are well trimmed, in " +
	     "several familiar shapes, and there is a place for " +
	     "knights to practice.\n");

    add_item(({"ivy"}),
	     "The ivy coveres all of the walls in this courtyard.  As far " +
	     "as you can tell, you are in the middle of the wilderness.  If " +
	     "it weren't for the doorways and staircases, you might " +
	     "actually think that you were lost.\n");

    add_exit(CASTLE_DIR + "gate_ent",    "south", 0);
    add_exit(CASTLE_DIR + "throne_room", "north", 0);
    add_exit(CASTLE_DIR + "l_hall1_1", "west",  0);
    add_exit(CASTLE_DIR + "joust_yard",  "east", "@@j_closed");
    add_exit(CASTLE_DIR + "land2_1",     "up",    0);

    reset_room();
}

public int
j_closed()
{
   write("Sorry, area is closed for construction.\n");
   return 1;
}
 
