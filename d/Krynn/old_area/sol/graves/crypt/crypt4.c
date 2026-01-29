/* The crypt by percy */

#include <macros.h>
#include "local.h"
#include "/d/Krynn/common/defs.h"
inherit INSIDE_BASE;
object skel1, skel2;

create_solace_room()
{
	set_short("Crypt room");
        set_long(BS("This very large well lit room is bare and unexciting"
	 + ", a hole with a ladder leads down.", 70));

	add_exit(TDIR + "crypt7", "down", 0);
	add_exit(TDIR + "crypt2", "east", 0);

	add_item("floor", "@@floor");
	add_item(({"wall", "walls", "hall", "hallway", "ceiling", "roof"}),
		"@@wall");

	INSIDE
	LIGHT

	reset_room();
}

reset_solace_room()
{
    if (!skel1)
      {
	  skel1 = clone_object(MONSTER + "skhwarrior");
	  skel1->move(TO);
      }
    if (!skel2)
      {
	  skel2 = clone_object(MONSTER + "skhwarrior");
	  skel2->move(TO);
      }
}

floor()
{
	write(BS("The floor is just a clean bare normal stone floor.", 70));
	say(BS(QCTNAME(TP) + " studies the floor carefully.", 70));
	return "";
}

wall()
{
	write(BS("The walls and the ceiling of the room are black though"
	 + " they appear to only be made of normal stone, unlike the clean"
	 + " white floor.", 70));
	say(BS(QCTNAME(TP) + " studies the room carefully.", 70));
	return "";
}


