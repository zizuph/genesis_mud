/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * road1.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit PORT_DIR + "port_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Southern road");
    set_long("You are standing on the road to the enchanted forest. " +
	     "The road continues in the north and southwest " +
	     "directions. To the north you see a vast forest and to " +
	     "the south you catch a glimpse of the sea. There are " +
	     "quite a few trees here. To the west and east they grow so " +
	     "thick that it is impossible to go there.\n");

    add_item(({"forest", "enchanted forest"}),
	     "Most of the trees seem very old.");

    add_item(({"sea"}), "The sea is quite far to the south.\n");

    add_exit(ENCHANT_DIR + "road_s12", "north",     0);
    add_exit(PORT_DIR + "road2",       "southwest", 0);
}
