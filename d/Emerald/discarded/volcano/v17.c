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
   
	add_exit("v18.c", "east", 0, 2);
	add_exit("v36.c", "south", 0, 2);
	add_exit("v4.c", "southeast", 0, 4);
   
}
