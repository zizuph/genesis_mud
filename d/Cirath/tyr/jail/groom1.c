/* Guard captains room on first floor in Jail of Tyr... /*
/* Zayn March 97 */

#pragma strict_types

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
	bring_room_mob("cirgol", TYR_NPC+"cirgol.c", 1, 1);
	bring_room_mob("slave", TYR_NPC+"jailslav.c", 1);
}

void
create_room()
{
	set_short("guardroom");
	set_long("Everything is ordered in a military fashion in here. The "
		+"desk in the center of the room is polished free from dust "
		+"and sand. A small window in the west wall gives some view "
		+"of the outside, besides from that the only light source "
		+"in this room is an oil-lamp standing on the desk. \n");

	add_item("desk", "A slave must have polished this desk, cleaned it "
		+"of dust and sand. The slave is probably also the one filling "
		+"the lamp with oil to keep it alight.\n");

	add_item("window", "When you look out the window you don't see much. "
		+"The only thing of interest is a bunch of corpses outside.\n");

	add_item(({"lamp", "oil-lamp"}), "This is the only light source in the "
		+"room besides the window.\n");

	INSIDE

	add_exit(TYR_JAIL + "groom2.c", "south", 0,1);
	reset_room();
}
