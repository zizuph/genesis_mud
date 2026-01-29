/* -*- Mode: C -*-
 *
 * close.c
 *
 * Skippern 20(c)14
 *
 */
inherit "/d/Gondor/common/lib/area_room";

#include "../../defs.h"

public int do_climb(string arg);
public int do_enter(string arg);

void
create_area_room()
{
    set_areatype(AREATYPE_MARSH);
    set_land("Belfalas");
    set_areadesc("small stream");
    set_area("western");
    set_areaname("Dor-en-Ernil");

    set_extraline("A small stream trickles down from the hill above. There " +
		"is a sewer grate to the west.");

	add_item( ({ "stream" }), "A small stream trickles down from the hill above, " +
		"it looks like it is possible to climb up it.\n");
	add_item( ({ "grate", "sewer grate" }), "There is a sewer grate to the " +
		"west, leading into the city wall. The grating looks damaged, it " +
		"might be possible to enter it.\n");
}

void
init()
{
	::init();
	add_action(do_climb, "climb");
	add_action(do_enter, "enter");
}

public int
do_climb(string arg)
{
	if (arg == "up" || arg == "stream")
	{
		write("You climb up the small stream.\n");
		say(this_player()->query_nonmet_name() + " leaves climbing up the small stream.\n");
		this_player()->move_living("M", DOL_OTHER + "outside/close", 1, 0);
		say(this_player()->query_nonmet_name() + " arrives climbing from below the road.\n");
		return 1;
	}
	notify_fail("Climb what?\n");
	return 0;

}

public int
do_enter(string arg)
{
	if (arg == "grate" || arg == "sewer" || arg == "sewer grate")
	{
		write("You enter the sewer grate.\n");
		say(this_player()->query_nonmet_name() + " leaves through the sewer grate.\n");
		this_player()->move_living("M", DOL_SEWER + "v-14", 1, 0);
		say(this_player()->query_nonmet_name() + " arrives from behind the grate.\n");
		return 1;
	}
	notify_fail("Climb what?\n");
	return 0;

}

