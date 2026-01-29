/* Guard room 4 on first floor in Jail of Tyr... /*
/* Zayn March 97 */

#pragma strict_types

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    bring_room_team(TYR_NPC+"jailgrd.c", 1, 3);
}

void
create_room()
{
	set_short("guard room");
	set_long("This is an inner guardroom, in case an outside enemy would "
		+"get this far into the jail to free prisoners. Or if a "
		+"prisoner would escape he would probably be taken by the "
		+"guards in this room. The walls are bare and empty. The only "
		+"thing in the room are some chairs for the guards to sit on "
		+"and a couple of tables. This is also the passage to the "
		+"dining room to the east.\n");

	add_item("chairs", "The chairs are made of wood, and "
		+"of a very simple construction. They do however fullfill "
		+"their purpose, to be sat on.\n");

	add_item("tables", "The tables is of very simple "
		+"construction. The guards use to play card or other simple "
		+"games on them.\n");

	add_item("walls", "They are bare and empty. You can however see some "
		+"strange marks on the walls.\n");

	add_item("marks", "When you take a closer look at the marks you can "
		+"see that they are marks from tapestries or paintings that "
		+"have decorated the walls in the past. This room has "
		+"probably been used for other purposes than a guardroom "
		+"in the past.\n");

	INSIDE

	add_exit(TYR_JAIL + "jail1_1.c", "west", 0,1);
	add_exit(TYR_JAIL + "diningh.c", "east", 0,1);
	reset_room();
}
