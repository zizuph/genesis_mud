/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * r_bath_room.c
 *
 * Vader
 * Recoded by Sorgum 950712
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
    set_short("Bath room");
    set_long("You are in the bath room.  This is where the servants " +
	     "of the King and his family bath.  It consists of " +
	     "several holes in the ground for 'waste disposal', " +
	     "and a large pool of water for cleaning.\n");
 
    add_item(({"hole", "holes"}),
	     "They look disgusting...not to mention the smell.\n");
 
    add_item(({"tub", "pool", "water", "pool of water"}),
	     "A 10' by 10' pool, filled with water by servants weekly.  You " +
	     "wonder how anyone can escape this room with a clean body.\n");
 
    INSIDE;
    add_prop(ROOM_HAS_WATER, 1);
}
 
