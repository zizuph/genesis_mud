/* -*- Mode: C -*-
 *
 * close.c
 *
 * Skippern 20(c)01
 *
 */
inherit "/d/Gondor/common/lib/area_room";

#include "../../defs.h"

public int do_climb(string arg);

void
create_area_room()
{
    set_areatype(AREATYPE_ROAD);
    set_land("Belfalas");
    set_areadesc("small hill");
    set_area("western");
    set_areaname("Dor-en-Ernil");

    set_extraline("A small stream trickles under the road. " +
		"In the horizon you see a city to the west.");

    add_item( ({ "horizon", "city" }), "As you scout west into the horizon " +
	      "to the west, you see a large groupe of houses surrounded by " +
	      "a wall. It is the city of Dol Amroth.\n");
	add_item( ({ "stream" }), "A small stream trickles under the road, " +
		"it looks like it is possible to climb down it.\n");

    add_exit(DOL_OTHER + "outside/near", "southwest", 0, 1);
    add_exit(DOL_OTHER + "outside/cross", "east", 0, 1);
}

void
init()
{
	::init();
	add_action(do_climb, "climb");
}

public int
do_climb(string arg)
{
	if (arg == "down" || arg == "stream")
	{
		write("You climb down the small stream.\n");
		say(this_player()->query_nonmet_name() + " leaves climbing down the small stream.\n");
		this_player()->move_living("M", DOL_OTHER + "outside/stream", 1, 0);
		say(this_player()->query_nonmet_name() + " arrives climbing from the hill above.\n");
		return 1;
	}
	notify_fail("Climb what?\n");
	return 0;

}