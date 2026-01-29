/*
 *      /d/Gondor/lebennin/wroad/wr21.c
 *
 *      Road leading from Pelargir to Dol Amroth
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
    set_items_road();
    set_items_linhir();

    set_short("A bridge crossing Gilrain");
    set_long("A massive stone bridge crossing the river Gilrain. A " +
        "cobblestone road leads from the east across the bridge towards " +
        "Linhir in the west. North of here the river Serni joins up with the " +
        "river Gilrain and the river continues south until it washes out " +
        "into the sea.\n");

    add_item(({"bridge", "massive bridge", "stone bridge"}), "The old stone " +
        "bridge ");

    add_exit(AREA_DIR + "wroad/wr19", "east", 0, 1);
    add_exit(AREA_DIR + "linhir/l1", "west", 0, 1);

    set_no_exit_msg(get_all_no_exits(({"w","e"})), "You decide to stay on " +
        "the road.\n");
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

    if (member_array(str, ({"bridge", "down", "down from the bridge"})) == -1) 
    {
        notify_fail("Are you trying to climb down from the bridge?\n");

        return 0;
    }

    if (this_player()->query_skill(SS_CLIMB) < 20)
    {
        this_player()->catch_msg("You take a long look at the height down " +
            "from the bridge, and decide your skills are not up to the " +
            "task.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) + 
            " looks dubiously at the bridge.\n", this_player());
        return 0;
    }

    this_player()->catch_msg("You swing yourself over the railing of the " +
        "bridge and expertly climb down.\n");
    tell_room(environment(this_player()), QCTNAME(this_player()) + 
        " expertly swings over the bridge and climbs down below.\n",
        this_player());
    this_player()->move_living("climbing boulder", 
        AREA_DIR + "wroad/cp1", 1, 0);
    return 1;
}
