/*
 * CRY4.c
 * Crypt outside/under the Ruins of Kamesh
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("A dark, cold crypt");
    set_long("   You are standing in a small alcove off of the main "+
	     "hall in the crypt. There are no decorations or carvings "+
	     "or anything of the kind here. There is a simple wooden "+
	     "bench on the floor in front of several rows of small "+
	     "candles. Each candle is being held by a small, red glass "+
	     "cylinder. Some of the candles are lit, and some aren't.\n\n");

    INSIDE;

    add_item( ({"bench", "wooden bench", "simple bench"}),
	     "The bench is small and simple. It is three pieces of wood "+
	     "which have been meshed together with wooden wedges. "+
	     "Oddly enough, you can find no dust on the bench at all, like "+
	     "you notice everywhere else.\n");

    add_item( ({"candles", "small candles", "cylinders", "glass cyldinders",
		"red cylinders", "cylinder", "candle"}),
	     "The candles layed out in front of the bench seem to form some "+
	     "sort of pattern, but you don't recognize it. You're sure "+
	     "that there is some sort of religious significance to these "+
	     "candles but you can't quite figure out what.\n");

    add_exit(MONKRUIN_DIR + "cry2", "south");

}
