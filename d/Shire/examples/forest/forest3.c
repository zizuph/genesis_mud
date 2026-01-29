#include "../local.h"
#include <tasks.h>

inherit FOREST_BASE;

void
create_forest_room()
{
    set_short("Within a gloomy forest");
    set_long("Long version(tm)\n");

    add_exit(EXAMPLE_FOREST + "forest2", "east",0, 3);
}

//  We want to allow players to climb a tree here
int
do_climb(string str)
{
    if (str == "tree")
    {
	NF("You are unable to climb up that tree.\n");
	return 0;
    }
    if (str == "oak tree")
    {
	if (TP->resolve_task(TASK_ROUTINE,({SS_CLIMB})) >= 0)
	{
	    write("You climb the tree.\n");
	    say(QCTNAME(TP)+" climbs up a tree.\n");
	    TP->move_living("M", EXAMPLE_FOREST + "tree");
	    return 1;
	}
	write("You slip and fall as you try to climb the tree.\n");
	say(QCTNAME(TP)+" slips and falls as "+HE_SHE(TP)+
	  " tries to climb a tree.\n");
	TP->heal_hp(-10);  // Hurt themself
	return 1;
    }
    NF("Climb what?\n");
    return 0;
}
