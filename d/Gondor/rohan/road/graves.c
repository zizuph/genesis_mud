/*
 *	/d/Gondor/rohan/road/graves.c
 *
 *	Coded 1992 by Gus ???.
 *
 *	Modification log:
 *	       1994, Olorin:	Added code for lookout.
 *	28-Jan-1997, Olorin:	Changed inheritance,
 *				general revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include "/d/Gondor/defs.h"

#define LOOKOUT		(EDORAS_DIR + "lookout")

public void
create_roads() 
{
    set_street("dusty turnpike");
    set_where("southwest");
    set_county("Eastfold");
    set_land("Rohan");
    set_mountain("White Mountains");
    set_vegetation("juicy, green, grass");
    set_extraline("You are on a road north of the town Edoras. The road goes in "
      + "a north/south direction. You can see gravemounds to the west and "
      + "east of here. The graves to the east look newer than those to the west.");
    add_exit (ROH_DIR + "road/crossroad",   "north", 0, 2);
    add_exit (ROH_DIR + "road/graves_e",    "east",  0, 1);
    add_exit (ROH_DIR + "edoras/city_entr", "south", 0, 2);
    add_exit (ROH_DIR + "road/graves_w",    "west",  0, 1);
    add_item("turnpike", "You are on a dusty road in Rohan. "
	     + "To the south it leads to Edoras.\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob))
    {
        FIX_EUID
        LOOKOUT->load_me();
        LOOKOUT->enter_road(ob,from);
    }
}
