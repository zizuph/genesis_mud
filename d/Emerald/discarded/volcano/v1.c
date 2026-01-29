// Emerald/tmp/volcano/vol1.c
// creator: Triana, Nov 1995
// purpose: level 3 of the volcano
// note: climbing increases as u go up.
// bugs:
// to-do: eruptions, falling rocks ?


#include "/d/Emerald/defs.h"
inherit "/d/Emerald/mountains/volcano/vroom.c";

void
create_volcano()
{
   set_short("Volcano Side");
   
   add_exit("v2.c", "south");
   add_exit("v4.c", "west");
	add_exit("top.c", "southwest", 0, 6);
	add_exit("v8.c", "northeast", 0, 5);
   
}

init()
{
	::init();
	LOAD_CLONE_HANDLER(VOL + "clone_handler.c");
}
