/* The crypt by percy */

#include "local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <ss_types.h>
inherit INSIDE_BASE;

create_solace_room()
{
	set_short("Crypt room");
        set_long(BS("This very large well lit room has earthen walls and floor"
	 + ", water drips in many places from the ceiling forming many puddles"
	 + " all over the room. The centre of the room contains one particularly"
	 + " large puddle where most of the water has come to settle."
	 + " A ladder leads up.", 70));

	add_exit(TDIR + "crypt4", "up", 0);
	add_exit(TDIR + "crypt9", "north", 0);


	add_item(({"floor", "ground"}), "@@floor");
	add_item(({"puddle", "puddles", "large puddle", "large puddles"}),
		"@@puddle");
	add_item("water", "The water in all the puddles is murky.\n");
	add_item(({"wall", "walls", "earthen wall", "earthen walls",
		"ceiling", "roof"}), "@@wall");

	INSIDE
	LIGHT
}

puddle()
{
	write(BS("The room has many small scattered pools of water"
	 + " formed from the water dripping from the ceiling. The"
	 + " centre of the room contains one particularly large"
	 + " puddle.", 70));
	say(BS(QCTNAME(TP) + " studies the puddles carefully.", 70));
	return "";
}

floor()
{
	write(BS("The floor is just normal earth, it is a bit muddy.", 70));
	say(BS(QCTNAME(TP) + " studies the floor carefully.", 70));
	return "";
}


wall()
{
	write(BS("The walls and the ceiling of the room are earthen though"
	 + " they appear to be sturdy enough. Water drips slowly from the ceiling.", 70));
	say(BS(QCTNAME(TP) + " studies the room carefully.", 70));
	return "";
}


