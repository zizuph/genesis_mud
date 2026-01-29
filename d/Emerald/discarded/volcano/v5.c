// Emerald/tmp/volcano/vol1.c
// creator: Triana, Nov 1995
// purpose: level 3 of the volcano
// note: climbing increases as u go up.
// bugs:
// to-do: eruptions, falling rocks ?

#include "/d/Emerald/defs.h"
inherit VOL + "vroom.c";

void
create_volcano()
{
   set_short("Volcano Side");
   
	add_exit("v16.c", "south", 0, 2);
	add_exit("v6.c", "east");
	add_exit("v4.c", "southeast", 0, 6);
	add_exit("v17.c", "northwest", 0, 5);
   
}
