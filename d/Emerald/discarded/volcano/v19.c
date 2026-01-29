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
   
	add_exit("v20.c", "east", 0, 2);
	add_exit("v18.c", "west", 0, 2);
   
}
