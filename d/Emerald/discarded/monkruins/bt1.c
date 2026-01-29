/*
 * BT1.c
 * Belltower. Woo!
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("A deteriorating room");
    set_long("   You are standing in the middle of a stone-walled "+
	     "room. There are broken, rotting wooden beams running "+
	     "in a cross-hatch pattern across the ceiling. You marvel "+
	     "at the miracle that the wood is even intact. The floor "+
	     "is barren and covered with dust, leaves, dirt and "+
	     "other grime. Whatever furniture was here before was either "+
	     "looted long ago or rotted into dust on the floor. There "+
	     "is a small crumbled exit leading east from here and the "+
	     "shattered doorway leading west.\n\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_item( ({"floor", "dust", "barren floor", "down", "ground"}),
	     "The floor of the room is made of cold, dull stone. There "+
	     "are cracks everywhere in the stone. It is covered in "+
	     "dust and a fine, dark brown powder which you can't quite "+
	     "identify.\n");

    add_item( ({"powder", "brown powder", "dark brown powder"}),
	     "It is a fine, dark brown powder. You can't quite figure "+
	     "out what it is though. It might have at one point "+
	     "been wood, but you aren't sure.\n");

    add_item( ({"exit", "crumbled exit", "east", "small exit"}),
	     "The small exit leading east opens up into another "+
	     "broken-down, nearly ruined room.\n");

    add_item( ({"beams", "wooden beams", "beam", "ceiling", "up",
		"pattern", "cross-hatch", "wood"}),
	     "The ceiling is a miracle in itself. You notice hundreds "+
	     "of cracks running in a web-like pattern across the stone "+
	     "surface. Underneath the stone is a cross-hatch pattern of "+
	     "thick wooden beams. It is a wonder that the beams have "+
	     "not crumbled to dust by now. You wonder if they weren't "+
	     "preserved somehow. The beams are all warped, and some of them "+
	     "are severely cracked.\n");

    add_exit(MONKRUIN_DIR + "bt2", "east");
    add_exit(MONKRUIN_DIR + "mr1", "out");

}




