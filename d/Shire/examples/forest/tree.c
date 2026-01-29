#include "../local.h"
#include <tasks.h> 
#include <ss_types.h>

inherit FOREST_BASE;

object leader, orc1, orc2;

void
create_forest_room()
{
    set_short("High above within a tree");
    set_long("Long version(tm).\n");

    //  We don't want ppl searching for herbs in the tree!
    set_no_herbs();

}

//  Only way down is to climb down.

// We'll just redefine the do_climb function from the base_file
int
do_climb(string str)
{
    if (str != "down")
    {
	NF("Climb down, perhaps?\n");
	return 0;
    }
    if (TP->resolve_task(TASK_DIFFICULT,({TS_DIS,SS_CLIMB})) >= 0)
    {  
	// The player passed!
	write("You climb down the tree.\n");
	say(QCTNAME(TP)+" climbs down the tree.\n");
	TP->move_living("M",EXAMPLE_FOREST+"forest3");
	return 1;
    }
    //  The player failed.
    TP->add_panic(15);  // To scared to climb down
    write("You are too scared to climb down the tree.\n");
    say(QCTNAME(TP)+" becomes gripped with fear as "+HE_SHE(TP)+
      "attempts to climb down the tree.\n");
    return 1;
}

