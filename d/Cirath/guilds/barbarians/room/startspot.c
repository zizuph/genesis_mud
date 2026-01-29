inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Start tent");
	set_long("You are standing inside a tent in the barbarian "+
		"camp. This tent is known as the 'start here' tent. It is "+
		"here barbarians begin their day. There is no furniture and "+
		"no decoration of any sort.\n");
	   
  	INSIDE;

  	add_exit(BARB_ROOM + "br4", "north", 0, 1);
}

void
init()
{
    	::init();
    	add_action("start" ,"start");
}

int
start(string str)
{
    NF("Start where?\n");
    if (str != "here") return 0;

    NF("Only the Gladiators of Athas may sleep here.\n");
    if (!IS_MEMBER(TP)) return 0;

    TP->set_default_start_location(BARB_ROOM+"bbk");
    write("This shall be the place to rest your weary head.\n");
    return 1;
}
