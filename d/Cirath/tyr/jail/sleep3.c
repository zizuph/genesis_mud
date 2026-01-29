/* Guard quarter 3 on first floor in Jail of Tyr... /*
/* Zayn March 97 */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    bring_room_team(TYR_NPC+"jailgrd2.c", 2, 1);
}

void
create_room()
{
	set_short("guard quarter");
	set_long("A bunch of beds, a table, a couple of chairs is the only "
		+"furniture in here, except for two racks on the wall. An "
		+"iron-bound thick door stands open to the east. This is a "
		+"sleeping quarter for the guards, here they sleep while they "
		+"are not on duty, which is most of the time. To the west "
		+"there is another guard quarter. The room is simple but "
		+"purpuse-made. It doesn't seem like the guards have very "
		+"high demands on their living situation.\n");

	add_item("beds", "The beads are many, but all of simple construction. "
		+"They stands two in height and five rows against both the "
		+"north and the south wall. In total you count it to twenty "
		+"beds.\n");

	add_item("table", "The table stands in the center of the room. On the "
		+"table you can see various bottles, it seems like the guards "
		+"have had a little drinking party in here.\n");

	add_item("chairs", "So few chair to so many guards? It must be that "
		+"they don't spend much time in here at all. They are "
		+"probably on duty most of their waken time.\n");

	add_item("racks", "The left rack is for weapons and the right one is "
		+"suited for armours. They are quite empty now, the guards "
		+"carry their weapons and armour, because the aren't here.\n");

	add_item("door", "The door is very thick and iron-bound. It would "
		+"take many men to force this door open if it was closed and "
		+"locked. Though it looks rather rusty and fixed in its "
		+"position.\n");

	add_cmd_item("door", "close", "It is impossible to close the door, it "
		+"is very rusty and fixed in its position. You will have to "
		+"oil it up to be able to move it from its position.\n");

	INSIDE

	add_exit(TYR_JAIL + "jail1_1.c", "east", 0,1);
	add_exit(TYR_JAIL + "sleep2.c", "west", 0,1);
	reset_room();
}
