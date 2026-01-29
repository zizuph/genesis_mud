inherit "/std/room";

#include "defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void
create_room()
{
    set_short("Ground level of northern tower");
    set_long(break_string(
	  "You are on the ground level of the northern tower. "
	+ "It is quite dark here, and the air is damp. The tower "
	+ "has not been used for a very long time. Circular stairs "
	+ "go up to the first floor. Halfway the stairs is a window.\n", 70));

    add_item("stairs", break_string(
	  "The broad wooden staircase winds up towards the first floor, "
	+ "following the wall of the tower. Quite a lot steps, though, "
	+ "will probably be a long way up.", 70));

    add_item("window", "It looks possible to climb out through the window.\n");

    /* Climbing the stairs is tiresome... */
    add_exit(STAND_DIR + "tower12", "up", 0, 4);
    add_exit(STAND_DIR + "path13", "south");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    clone_object(STAND_DIR + "tower1_doorb")->move(this_object());
}

void
init()
{
    ::init();
    add_action("do_climb", "climb", 0);
}

int
do_climb(string str)
{
    if (str == "out")
    {
	this_player()->catch_msg("You climb out of the window, and fall "
				+ "down outside.\nYou didn't hurt yourself.");
	this_player()->move_living("X", STAND_DIR + "path13");
	tell_room(QCTNAME(this_player()) + " climbs out of the window and "
		+ "falls down outside.\n");
	return 1;
    }

    notify_fail("Climb where?\n");
    return 0;
}
