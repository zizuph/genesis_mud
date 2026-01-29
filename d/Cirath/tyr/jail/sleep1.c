/* Guard quarter 1 on first floor in Jail of Tyr... /*
/* Zayn March 97 */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    bring_room_team(TYR_NPC+"jailgrd2.c", 1, 3);
}

void
create_room()
{
	set_short("guard quarter");
	set_long("There are only ten beds in this room. This room is used by "
		+"the guards when they are of duty and not sleeping. There "
		+"are various tables standing in the room. A lot of chairs "
		+"stand around the tables. There are a couple of games "
		+"going on at some of tables. To the south you can see "
		+"the guards sleeping quarter. An iron-bound thick door "
		+"stands open to the north.\n");

	add_item("door", "The door is very thick and iron-bound. It would "
		+"take many men to force this door open if it was closed and "
		+"locked. Though it looks rather rusty and fixed in its "
		+"position.\n");

	add_item("beds", "There are ten beds lined up against the south "
		+"wall.\n");

	add_item("tables", "There is plenty of tables in here. They stands "
		+"in a randomly order.\n");

	add_item("chairs", "The chairs stands mostly around the tables, there "
		+"are however chairs laying on the floor too.\n");

	add_cmd_item("door", "close", "It is impossible to close the door, it "
		+"is very rusty and fixed in its position. You will have to "
		+"oil it up to be able to move it from its position.\n");

	INSIDE

	add_exit(TYR_JAIL + "sleep2.c", "south", 0,1);
	add_exit(TYR_JAIL + "jail1_2.c", "north", 0,1);
	reset_room();
}
