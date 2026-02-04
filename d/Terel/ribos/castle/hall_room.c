/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * hall_room.c
 *
 * A generic hall in the Ribos castle.
 *
 * Vader
 * Recoded by Sorgum 950708
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

create_room()
{
    ::create_room();

    set_short("A hallway");
    set_long("This is a large, regal hallway.  It is decorated by " +
	     "paintings and busts of great people.\n");

    add_item(({"painting", "paintings"}),
	     "They are mostly of the king, and those kings before him.\n");

    add_item(({"bust", "busts"}),
	     "They are mostly of the king, and those kings before him.\n");

    INSIDE;
}
