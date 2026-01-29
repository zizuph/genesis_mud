/*
 * Filename:		road2.c
 * Description: 	Area around Newports, Abanasinia
 *
 * Coded by:		Aridor, 03/95
 *
 * Revision history:
 * Oct 25 1999 by Boron: Added warfare support
 *
 */

#include "local.h"

inherit BASE_FILE;

void
create_newport_room()
{
    set_short("An untravelled road");
    set_long("The main road you are standing on runs southwest and northeast. " +
	     "Far in the southwest it runs along a forest and eventually " +
	     "disappears into some distant hills. " +
	     "Looking northeast, you can see a crossroads up ahead. " +
	     "To the east, you can see several small cottages, the village of " +
	     "Newports. Water can be seen beyond the village.\n");

    add_item("road","This is a gravel road, leading northeast and southwest.\n");
    add_item("gravel","It looks very ordinary.\n");
    add_item(({"houses","cottages","village","newports"}),
	     "The few houses making up the village of Newports can be seen to " +
	     "the east.\n");
    add_item("water","This seems to be a quite large body of water, probably " +
	     "an ocean.\n");
    add_item("forest","The forest is quite some distance away, but can be seen " +
	     "very well, even from this distance. It lies to the southwest.\n");
    add_item("crossroads","It to the northeast from here. To see more, you have " +
	     "to go there.\n");

    add_exit(PAX + "road7","southwest","@@closed@@",3);
    add_exit(TDIR + "road1", "northeast",0,3);
}

int
closed()
{
    ("/d/Krynn/pax/obj/master")->try_enter_pax(this_player());

    return 0;
}
