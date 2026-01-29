/*
 *      /d/Gondor/lebennin/wroad/cp1.c
 *
 *      Path below the Linhir bridge leading to a corsair camp
 *
 */

#pragma strict_types

#include "/d/Gondor/lebennin/std/defs.h"
#include <ss_types.h>
#include <macros.h>

inherit LEBENNIN_STD_DIR + "base";

void
create_lebennin_room()
{
    set_short("A small path");
    set_long("A small path leads from the foot of the old stone bridge, " +
        "south alongside the river Gilrain. The banks of the river stands " +
        "tall to the east, with dense bushes obscuring the view from the " +
        "plains above.\n");

    add_item(({"bridge", "old bridge", "old stone bridge"}), "");
    add_item(({"bush", "bushes"}), "");
    add_item(({"river", "gilrain"}), "");
    add_item(({"path", "small path"}), "");
    
    add_exit(AREA_DIR + "wroad/cp2", "southwest", 0, 1);
    set_no_exit_msg(({"west", "northwest"}), "The current of the river is " +
        "too swift for swimming.\n");
    set_no_exit_msg(({"east", "northeast", "southeast", "south"}), "The " +
        "riverbank is too steep to climb.\n");
    set_no_exit_msg(({"north"}), "Thick bushes prevent moving in that " +
        "direction.\n");
}

void
init()
{
    ::init();
   add_action("try_climb", "climb");
}

public int
try_climb(string str)
{
    if (!strlen(str))
    {
        notify_fail("What did you want to climb?\n");

        return 0;
    }

    if (member_array(str, ({"bridge", "up"})) == -1) 
    {
        notify_fail("Are you trying to climb up?\n");

        return 0;
    }

    if (this_player()->query_skill(SS_CLIMB) < 20)
    {
        this_player()->catch_msg("You inspect the bridge support and decide " +
            "your skills are not up to the task.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) + 
            " looks dubiously at the bridge support.\n", this_player());
        return 0;
    }

    this_player()->catch_msg("You place your fingers in the mortar cracks of " +
        "the bridge support and expertly climb up.\n");
    tell_room(environment(this_player()), QCTNAME(this_player()) + 
        " expertly climbs up the bridge support.\n", this_player());
    this_player()->move_living("climbing boulder", 
        AREA_DIR + "wroad/wr21", 1, 0);
    return 1;
}
