/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * house5.c
 *
 * An old house in Ribos
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: query_moving_object_list
 * Description:   return list of moving_objects to clone at each reset.
 */
public string*
query_moving_object_list()
{
    return ({RIBOS_DIR + "monster/spider"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Run down house");
    set_long("This house was once home to a proud family, but " +
	     "now, it is just a roof over an empty shell.  The furniture is " +
	     "starting to collect dust, and cobwebs are forming " +
	     "throughout.  It looks like they left in a hurry, because " +
	     "the beds are not made, and there are still dirty dishes " +
	     "on the table.\n");

    add_item(({"dust"}), "It represents several days worth of heavy dust.\n");

    add_item(({"furniture"}), "It is made of fine wood imported from " +
             "Calathin.  How did they get\nit down here?\n");

    add_item(({"table"}), "This family was well to do.  They could afford " +
            "really nice furnishings.\n");

    add_item(({"dishes", "dirty dishes"}), "They contain the crusted on " +
             "remains of corn and meat.\n");

    add_item(({"cobwebs"}), "This house is now home to various species of " +
             "spiders now.\n");

    add_item(({"bed", "beds"}), "The sheets have been tossed wildly " +
            "accross the beds.\n");

    INSIDE;

    add_exit(RIBOS_DIR + "road5", "west", 0);
    reset_room();
}
