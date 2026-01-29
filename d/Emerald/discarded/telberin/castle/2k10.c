/*
 * 2k10.c
 * Walled-off Passage on the second floor of Castle Telberin
 *    - Alaron September 11, 1996
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Passage");
    set_long("   The hallway here is narrow and feels closed in. The "+
	     "dim light from the hallway to the southwest barely "+
	     "illuminates the small passage. The northeast end of the "+
	     "passage is walled off. The bricks of emerald stone there "+
	     "look to be far newer and of much less quality than the "+
	     "stones in the hallway.\n\n");

    add_item( ({"bricks", "emerald stone", "bricks of emerald stone",
		"walled off passage", "northeast", "brick wall"}),
	     "It looks like this passage may have lead further, but "+
	     "has apparently been walled off, and probably recently.\n");
   
   add_exit(CASTLE_DIR + "2k4","southwest",0);
}
