// creator: Triana, Nov 1995
// Emerald/volano/v4.c
// note: climbing increases as u go up.
// bugs:
// to-do: eruptions, falling rocks ?

#include "/d/Emerald/defs.h"
inherit VOL + "vroom.c";

void
create_volcano()
{
   set_short("Volcano Side");
   
	add_exit("v1.c", "east");
	add_exit("v3.c", "south");
	add_exit("top.c", "southeast", 0, 6);
	add_exit("v5.c", "northwest", 0, 5);
}
