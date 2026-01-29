/* Center Hall on first floor in Jail of Tyr... /*
/* Zayn March 97 */

inherit "/std/room";
#include "defs.h"

void
create_room()
{
	set_short("center hall");
	set_long("This hall is the center room of the jail. Everything going "
		+"out or in must pass though this room. There are stairs "
		+"leading up to the second floor. There are strange marks "
		+"on the floor from the south up through the stairs. To the "
		+"east there is a guard room, which checks everyone passing "
		+"through this room. The exit from the jail is to the south. "
		+"You can hear sound from the next floor. A corridor is to "
		+"the northwest and to the notheast.\n");

	add_item("stairs", "They are leading to the second floor. There are "
		+"drag marks on the stairs, and stains of some sort in a red "
		+"brownish colour. The steps are made of stone, and are "
		+"rather worn down.\n");

	add_item("sound", "You can hear prisoners scream, or maybe slaves. "
		+"It sounds just like if someone was being tortured.\n");

	add_item("floor", "There are sand all over the floor. It is probably "
		+"very hard to keep it clean. You can see drag marks on the "
		+"floor, trails made through the dust.\n");

	add_item("corridor", "There are two corridors, one to the northeast "
		+"and one to the northwest. It seems like the runs deeper "
		+"into the tower.\n");

	INSIDE;
	MARKS;
	STAINS;

	add_exit(TYR_JAIL + "jailentr.c", "south", 0,1);
	add_exit(TYR_JAIL + "groom4.c", "east", 0,1);
	add_exit(TYR_JAIL + "jail1_3.c", "northeast", 0,1);
	add_exit(TYR_JAIL + "jail1_2.c", "northwest", 0,1);
	add_exit(TYR_JAIL + "sleep3.c", "west", 0,1);
	add_exit(TYR_JAIL + "", "stairs", 0,1);
}
