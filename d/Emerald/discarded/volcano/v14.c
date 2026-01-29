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
   
	add_exit("v15.c", "north");
	add_exit("v13.c", "east");
	add_exit("v3.c", "northeast", 0, 5);
	add_exit("v32.c", "southwest", 0, 4);
   
}
