/* The crypt by percy */

#include "local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
inherit INSIDE_BASE;

create_solace_room()
{
	set_short("Crypt room");
        set_long(BS("This is a narrow tunnel that winds itself"
	 + " northwards but up ahead you can see that it leads"
	 + " to the east and into another room", 70));

	add_exit(TDIR + "crypt10", "east", 0);
	add_exit(TDIR + "crypt7", "south", 0);

	add_item(({"floor", "ground"}), "@@floor");
	add_item(({"wall", "walls", "earthen wall",
		"earthen walls", "ceiling", "roof"}), "@@wall");

	INSIDE
	LIGHT
}

floor()
{
	write(BS("The floor is just normal earth, it is a bit muddy.", 70));
	say(BS(QCTNAME(TP) + " studies the floor carefully.", 70));
	return "";
}


wall()
{
	write(BS("The walls and the ceiling of the tunnel are earthen though"
	 + " they appear to be sturdy enough.", 70));
	say(BS(QCTNAME(TP) + " studies the room carefully.", 70));
	return "";
}


