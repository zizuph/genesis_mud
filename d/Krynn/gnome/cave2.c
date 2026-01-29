inherit "/d/Krynn/std/room.c";

#include "/d/Krynn/common/defs.h"
#include "local.h"

object guard1, guard2;

void
create_room()
{
	LIGHT;
	INSIDE;
	set_short("Cave guardroom");
	set_long(
		"You find yourself in an makeshift guardroom. "
		+ "There are a table, a few\nchairs but little else. "
		+ "Everything looks improvised. The Gnomes don't\nseem to "
		+ "have used this room for a long time yet. Everything "
		+ "looks new.\nBut there's a thin layer of dust all around "
		+ "though.\n");
	
	add_exit(CAVES + "cav1", "north", 0, 1);
	add_exit(TDIR + "cave1", "south", 0, 5);

	add_item(({"table","chair", "chairs"}), "Only the most functional "
		+ "furniture.\n");
	add_item("dust", "Even you are covered with it!\n");
	add_item(({"ground", "ceiling"}), BS(
			"There are fine cracks in the ground, walls "
			+ "and  ceiling all over this place. You do not "
			+ "feel too safe in here.", 70));
	add_item(({"smoke", "clouds"}), "You can see smoke clouds to "
			+ "the south.\n");

	set_alarm(1.0, -1.0, "reset_room");
}


void
reset_room()
{
	if (!guard1)
	{
		guard1 = clone_object(MON + "caveguard");
		guard1->move_living("xxx", TO);
	}
	if (!guard2)
	{
		guard2 = clone_object(MON + "caveguard");
		guard2->move_living("xxx", TO);
	}
}
string
area() {return "Intheguardsroom";}

string
wayout() {return "south";}

string
tohelp() {return "done";}

string
fromhelp() {return "south";}
