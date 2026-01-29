#include "local.h"
inherit "/d/Krynn/std/outside_room";
inherit CONQUER_BASE

int block()
{
    this_player()->catch_tell("Temporaly closed...\n");
    return 1;
}

void
create_krynn_room()
{
    set_short("On a high bridge");
    set_long("You are standing on a very high bridge spanning a wild river. " +
	     "Towards your northeast, the plains of Abanasinia spread out before " +
	     "your eyes, the road, known as the Sageway, leads northeast from the " +
	     "bridge into the plains. To the southwest, the road continues towards " +
	     "a distant forest.\n");
    
    add_item("road","A gravel road leads northeast and southwest away from the bridge.\n");
    add_item("bridge","There is a bridge leading northeast from here. The river " +
	     "is quite deep below you, and you marvel at the construction " +
	     "of the bridge, being so high above the river.\n");
    add_item("river","You cannot see much of the river from here except that it " +
        "seems to be flowing fast. A thunderous sound can be heard from the gorge.\n");
    add_item("forest","It is very far away and it looks green from here.\n");
    add_item("green","Probably the leaves of the forest.\n");

//    add_exit("", "northeast", block);
    add_exit(TDIR+"rooms/plain-5-23-1", "northeast");
    add_exit(NEWPORTS_VILLAGE, "southwest");

    set_area_name(WAR_AREA_NEWPORT);
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    reset_conquer_room();
}

/* Needed to initialize commands for war-area */
void
init()
{
    init_conquer();
    ::init();
}
