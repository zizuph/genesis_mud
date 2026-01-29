/* Guard quarter 2 on first floor in Jail of Tyr... /*
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
	set_long("Beds are lined up against the walls, a lonely table stands "
		+"in the southwest corner of the room. There aren't any "
		+"chairs to sit on in here. A large crude chest stands "
		+"beside the table. Above the east door is a tapestry. "
		+"Two racks hang on the west wall.\n");

	add_item("beds", "The beads are many, but all of simple construction. "
		+"They stands two in height and five rows against both the "
		+"north and the south wall. In total you count it to twenty "
		+"beds.\n");

	add_item("racks", "The left rack is for weapons and the right one is "
		+"suited for armours. They are quite empty now, the guards "
		+"carry their weapons and armour, because the aren't here.\n");

	add_item("table", "There are no chairs to sit on around this table. "
		+"The surface of the table is scratched, and different "
		+"strange objects is engraved. Some bored, lonely guard must "
		+"have made them when he had nothing better to do.\n");

	add_item("chest", "It is crude and made of wood. The chest is closed "
		+"and seems to be locked. You can't however see a lock of "
		+"any kind on the chest.\n");

	add_item("lock", "You can't find any locks.\n");

	add_item("tapestry", "The tapestry show a scene where two guards "
		+"hold a mob of people way from the jail gates.\n");

	add_cmd_item("chest", "open", "You can't force the lid opened. It is "
		+"probably locked.\n");

	INSIDE

	add_exit(TYR_JAIL + "sleep3.c", "east", 0,1);
	add_exit(TYR_JAIL + "sleep1.c", "north", 0,1);
	reset_room();
}
