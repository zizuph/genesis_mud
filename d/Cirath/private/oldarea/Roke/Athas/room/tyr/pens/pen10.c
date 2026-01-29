inherit "std/room";
#include "/d/Roke/common/defs.h"
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
        add_item(({ "straw", "bed"}) "The pile of straw is dirty and "+
	   "full of bugs. It doesn't look very comfortable to sleep "+
	   "on.\n");

	LIGHT

	add_exit(PEN_DIR +"pen6.c", "north");
}
reset_room()
{
	seteuid(getuid(TO));
	if(mon)
	  return;
	tell_room(TO, "A dirty slave runs to the corner of the "+
	   "room when you enter.");
	mon = clone_object(A_NPC_D+"dirtyslave");
	mon->move(TO);
}

