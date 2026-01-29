inherit "/d/Krynn/std/room.c";
#include "/d/Krynn/common/defs.h"
#include "local.h"

void
create_room()
{
	LIGHT;
	INSIDE;
	set_short("A really dusty corridor");
	set_long(BS(
		"There is dust all over the place. It especially sticks to some "
		+ "cracks in the walls. There are iron tracks on the ground.", 70));
	
	add_exit(TDIR + "corridor3.c", "west", 0, 1);
	add_exit(TDIR + "corridor1.c", "north", 0, 1);

	add_item(({"tracks", "iron tracks"}) ,BS(
		"They seem to be used quite often. They run from "
		+ "the west to the north.", 70));
	add_item("dust", BS(
			"It sticks to some cracks in the walls clearly "
			+ "outlining their shape.", 70));
	add_item("ground", "There are tracks on the ground.\n");
	add_item(({"walls","cracks"}), "You discover two fine cracks in the walls "
			+ "which start here and broaden to the west.\n");
}

void
expl1()
{
	tell_room(TO, "Suddenly the ground starts to vibrate slightly.\n");
	set_alarm(20.0, -1.0, "expl2");
}


void
expl2()
{
	tell_room(TO, "There's an explosion somewhere to "
		+ "the west. Dust is raining from the ceiling!\n");
	set_alarm(20.0, -1.0, "expl3");
}

void
expl3()
{
	tell_room(TO, 
		"As suddenly as everything started it becomes quiet "
		+ "again.\n");
}

string area() {return "Inthecorridors";}
string wayout() {return "west north";}
string tohelp() {return "west";}
string fromhelp() {return "north";}
