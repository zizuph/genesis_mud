inherit "std/room";
#include "defs.h"
#include <stdproperties.h>

object mon=0;

void
create_room()
{
	set_short("Slave prison cell");
	set_long("This is a small, dingy cell made from dry, dusty "+
	   "sandstone. It is dimly lit by the torchlight from the "+
	   "hall. There is a rotting, vermin infested pile of straw "+
	   "that some people might call a bed.\n");
  add_item(({"straw","bed"}),("The pile of straw is dirty and "+
	   "full of bugs. It doesn't look very comfortable to sleep "+
     "on.\n"));

	LIGHT

	add_exit(TYR_PITS +"pen6.c", "south");
}
reset_room()
{
	seteuid(getuid(TO));
	if(mon)
	  return;
	tell_room(TO, "A jittery slave jumps out of bed at your "+
	   "approach.\n");
	mon = clone_object(TYR_NPC+"workslave");
	mon->move(TO);
}

