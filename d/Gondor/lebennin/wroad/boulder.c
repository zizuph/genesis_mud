
/*
 *      /d/Gondor/lebennin/wroad/boulder.c
 *
 *      A boulder standing in room wr7
 *
 */

#pragma strict_types

#include "/d/Gondor/lebennin/std/defs.h"
#include <ss_types.h>
#include <macros.h>

inherit LEBENNIN_STD_DIR + "base";

public int climb_boulder(string str);

void
create_plains_room()
{
    set_short("On top of a boulder");
    set_long("Below you can see the road continuing across the plains into " +
        "the horizon to the east and west. The boulder is the only " +
        "obstacle the road has to circumvent. The " + daylight() + " shines " +
        "upon the rolling hills to the north. Spreading out across a " +
        "massive area, the wide river delta of Ethir Anduin lies beyond " +
        "the plains to the south.\n");
    add_item(({"boulder", "large boulder"}), "Traces of debris litter the " +
        "flat top of the boulder. The sides of the boulder are covered with " +
        "various protrusions and crevices.\n");
    add_item(({"debris", "trash"}), "Various food scraps and burnt out " + 
        "remains of campfires clutter the top of the boulder.\n");

    set_no_exit_msg(get_all_no_exits(({})), "You are standing on the top of " +
        "a large boulder, you have to climb down before moving in that " +
        "direction.\n");
}

public int
climb_boulder(string str)
{
    if (!strlen(str))
    {
        notify_fail("What did you want to climb? The large boulder?\n");
        return 0;
    }

    if (member_array(str, ({"down", "down the boulder", "down the face of " +
        "the boulder"})) == -1)
    {
        notify_fail("Are you trying to climb down the face of the boulder?\n");

        return 0;
    }
 
    this_player()->catch_msg("Using the crevices and protrusions in the " +
        "rock, you climb down from the boulder.\n");
    tell_room(environment(this_player()), "Expertly utilizing the crevies " +
        "and protrusions in the rock, " + QCTNAME(this_player()) + " climbs " +
        "down the large boulder.\n", this_player());
    this_player()->move_living("climbing boulder",
        AREA_DIR + "wroad/wr7", 1, 0);
    
    return 1;
}


public void
init()
{
    ::init();

    add_action("climb_boulder", "climb");
}
