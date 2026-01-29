/*
 * CRY2.c
 * Crypt just outside the Ruins of Kamesh
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("Inside a dark crypt");
    set_long("   You are in the center of what looks like an enormous "+
	     "crypt. There are coffins lined up in rows all about you. The "+
	     "coffins are of all sizes and styles. Some are decorated with "+
	     "intricate, ancient carvings, while others remain bare and "+
	     "smooth. A chill wind blows through the chamber, causing the "+
	     "dim light from the lamps to flicker and the cobwebs to "+
	     "flap in the breeze. All of your senses tell you that something "+
	     "is not entirely right about this place. Sarcophagi litter the "+
	     "gray stone floor to the east, and two small alcoves are to "+
	     "the north and south, each containing a bench and several "+
	     "lit candles.\n\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_item( ({"coffins", "sarcophagi", "sarcophagus", "coffin", "rows"}),
	     "The coffins are arrayed in neat rows all around you. Even "+
	     "standing in the middle of the chamber you can't quite count "+
	     "them all as some of them are hidden from the flickering "+
	     "lamplight. Some have been carved with ancient, undecipherable "+
	     "lettering and decoration, while others are simple, smooth "+
	     "stone. The sarcophagi are still a little too hard to see "+
	     "from here, as the light from the lamps and candles doesn't "+
	     "quite reach out to that area of the crypt.\n");

    add_item( ({"lamps", "candles", "lamp", "candle", "rings", 
		"iron rings"}),
	     "The lamps and candles are hanging from thick, iron rings "+
	     "which have been hammered into the stone walls of the "+
	     "crypt. There are even more candles in the small alcoves "+
	     "on either side of the coffins to the north or south.\n");

    add_item( ({"alcove", "alcoves", "north", "south"}),
	     "The alcoves to the north and south are small, little areas "+
	     "each with a bench and an assortment of candles. Some of the "+
	     "candles are lit.\n");

    add_item( ({"bench", "benches"}),
	     "The benches in the alcoves are made of a sturdy wood. You "+
	     "notice that there is no dust on the benches, yet dust blankets "+
	     "nearly everything else in the crypt.\n");

    add_item( ({"cobwebs", "webs", "spider webs"}),
	     "There are cobwebs hanging from every part of the crypt, "+
	     "including all of the corners and nearly all of the side "+
	     "walls.\n");

    add_exit(MONKRUIN_DIR + "cry4", "north");
    add_exit(MONKRUIN_DIR + "cry5", "south");
    add_exit(MONKRUIN_DIR + "cry1", "west");
    add_exit(MONKRUIN_DIR + "cry3", "east");
}
