/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * house6.c
 *
 * An old house in Ribos
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("house");
    set_long("This is a small house, where a family in " +
	     "Ribos once lived.  There is smashed furniture all " +
	     "over the place.  You also notice a childs drawing in " +
	     "paint on one wall.  This childs parents probably didn't " +
	     "approve of this artwork.\n");


    add_item(({"painting", "wall", "drawing"}), "It depicts a large green " +
             "monster terrorizing a family of four.\n");

    add_item(({"furniture", "smashed furniture"}), "It was once " +
             "cheap furniture, but now it's firewood.\n");

    add_exit(RIBOS_DIR + "road6", "east", 0);
}

