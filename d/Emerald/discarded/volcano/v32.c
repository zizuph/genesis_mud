// Emerald/tmp/volcano/vol1.c
// creator: Triana, Nov 1995
// purpose: level 3 of the volcano
// note: climbing increases as u go up.
// bugs:
// to-do: eruptions, falling rocks ?

#include "vol.h"
inherit VROOM;

#include "vol.h"
void
create_volcano()
{
   set_short("Volcano Side");
   
	add_exit("v33.c", "north");
	add_exit("v31.c", "east");
	add_exit("v14.c", "northeast", 0, 4);
   
}
