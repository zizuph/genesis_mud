/* -*- Mode: C -*-
 * Sewer v-14.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

public int do_enter(string arg);

int
grate()
{
	write("A grate blocks your path east. Maybe you can <pass> it by force?\n");
	return 1;
}

void
create_sewer()
{
    set_checkpoint("v-14");

    add_exit(DOL_SEWER + "u-13", "northwest", 0, 2);
	add_exit(DOL_SEWER + "w-14", "east", &grate(), 2);
}

void
init()
{
	::init();
	add_action(do_enter, "pass");
}

public int
do_enter(string arg)
{
	if (arg == "grate" ||  arg == "through grate")
	{
		write("You enter the sewer grate.\n");
		say(this_player()->query_nonmet_name() + " leaves through the sewer grate.\n");
		this_player()->move_living("M", DOL_OTHER + "outside/stream", 1, 0);
		say(this_player()->query_nonmet_name() + " arrives from behind the grate.\n");
		return 1;
	}
	notify_fail("Climb what?\n");
	return 0;

}

