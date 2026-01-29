/*
 *      /d/Gondor/lebennin/wroad/wr7.c
 *
 *      Road leading from Pelargir to Dol Amroth
 */

#pragma strict_types

#include "/d/Gondor/lebennin/std/defs.h"
#include <ss_types.h>
#include <macros.h>

inherit LEBENNIN_STD_DIR + "base";

public int climb_boulder(string str);

void
create_lebennin_room()
{
    set_items_road();
    set_lebennin_herbs();

    set_short("Road in Lebennin");
    set_long("An old cobblestone road running across the " +
        "rolling plains. The road continues across the plains into the " +
        "horizon to the east and west. A large boulder is the only obstacle " +
        "the road has to circumvent. The " + daylight() + " shines " +
        "upon the rolling hills to the north. Spreading out across a " +
        "massive area, the wide river delta of Ethir Anduin lies beyond " +
        "the plains to the south.\n");
    add_item(({"boulder", "large boulder"}), "A large boulder stands " +
        "near the road, with the road having to take a turn around it. " +
        "The face of the boulder has many protrusions.\n");
    add_item("protrusions", "The protrusions in the boulder cover the " +
        "entire surface of the boulder.\n");

    add_exit(AREA_DIR + "wroad/wr6", "east", 0, 1);
    add_exit(AREA_DIR + "wroad/wr8", "west", 0, 1);
    set_no_exit_msg(get_all_no_exits(({"w","e"})), 
        "You decide to stay on the road.\n");
}


/*
 * Function name:        plains_climb_tree
 * Description  :        This code lets people hide in trees by adding a tree
 *                       shadow.
 * Thanks:               This code is based on work by Carnak
 */
public int
climb_boulder(string str)
{
    if (!strlen(str))
    {
        notify_fail("What did you want to climb? The large boulder?\n");

        return 0;
    }

    if (member_array(str, ({"boulder", "up", "up the boulder", 
            "up the face of the boulder"})) == -1)
    {
        notify_fail("Are you trying to climb up the face of the boulder?\n");

        return 0;
    }

    if (this_player()->query_skill(SS_CLIMB) < 20)
    {
        this_player()->catch_msg("You place your toes in a protrusion, and " +
            "grab a crevice in the face of the boulder. When you try to " +
            "hoist yourself up, you fail miserably and fall down landing on " +
            "your feet.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) + 
            " fails to scale the large boulder.\n", this_player());
        return 0;
    }

    this_player()->catch_msg("Using the crevices and protrusions in the " +
        "rock, you manage to climb up to the top of the boulder.\n");
    tell_room(environment(this_player()), "Expertly utilizing the crevies " +
        "and protrusions in the rock, " + QCTNAME(this_player()) + " scales the " +
        "large boulder.\n", this_player());
    this_player()->move_living("climbing boulder", AREA_DIR + "wroad/boulder", 1, 0);
    return 1;
}


public void
init()
{
    ::init();

    add_action("climb_boulder", "climb");
}
