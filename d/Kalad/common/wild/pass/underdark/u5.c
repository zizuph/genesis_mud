/*
 * /d/Kalad/common/wild/pass/underdark/u5
 * Purpose    : Passage between Dark Dominion and Kalad surface
 * Located    : Under Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Aug'97: Adapted to dark_dom inherit
 *		Toby, 971014 (fixed typo)
 */

#pragma strict_types
#include "/d/Kalad/defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "dark_dom.h"

#define KALAD_FOUND_DOMINION_EXIT "_kalad_found_dominion_exit"

inherit DARK_DOM;

public void
create_dark_dom()
{
    add_prop(OBJ_S_SEARCH_FUN, "search_ceiling");
    set_short("On a narrow ledge");
    set_long("You are on a precariously narrow ledge of rock, overlooking "+
      "a seemingly bottomless pit. The room you are within is quite large, "+
      "however most of it is open air, because of the chasm. Impenetrable "+
      "darkness lies below you.\n");
    add_item(({"narrow ledge","ledge"}),"This jutting shelf of rock looks "+
      "barely large enough to hold you and perhaps a few others.\n");
    add_item(({"bottomless pit","pit","impenetrable darkness","darkness","chasm"}),
      "A yawning hole that seems darker than the most evil of hearts, it "+
      "looks like it leads straight to the depths of hell.\n");
    add_item(({"ceiling"}),"It seems to hang over you like a vulture waiting "+
      "to feed upon a corpse.\n");
    add_exit(DARK(u4), "up", "@@exit_up", 1, 1);
}

int
exit_up()
{
    object *witnesses;
    if (TP->query_prop(KALAD_FOUND_DOMINION_EXIT))
    {
        witnesses = filter(FILTER_CAN_SEE_IN_ROOM(AINV(E(TP)) - ({TP})),
                TP->check_seen);
        foreach (object witness: witnesses)
        {
            if (!witness->query_prop(KALAD_FOUND_DOMINION_EXIT))
            {
                witness->add_prop(KALAD_FOUND_DOMINION_EXIT, 1);
                witness->catch_msg(QCTNAME(TP) + 
                    " uses a passage hidden in the ceiling!\n");
            }
        }
        return 0;
    }
    write("There is no obvious exit up.\n");
    return 1;
}


public string
search_ceiling(object me, string arg)
{
    if (arg != "ceiling")
	    return "";
    if (this_player()->query_skill(SS_AWARENESS) < 30)
	    return "";
    TP->add_prop(KALAD_FOUND_DOMINION_EXIT, 1);
    return "You search the ceiling carefully and discover a hidden "
        + "passage leading up!\n";
}

void
init()
{
    ::init();

    add_action("try_climb", "climb");
    add_action("jump", "jump");
    add_action("xthrow", "throw");
}

int
try_climb(string str)
{
    notify_fail("Climb what, down?\n");

    if (!str || str != "down")
	return 0;

    this_player()->move_living("climbing down", DARK(u6), 1);
    this_player()->add_fatigue(-5);
    return 1;
}

int
jump(string str)
{
    write("You try to jump as high as possible and you slip. It's seems to " +
      "be a long\nway down....\n");
    say(QCTNAME(this_player()) + " foolishly jumps and falls from the ledge.\n");

    this_player()->move_living("M", "/d/Kalad/common/wild/pass/underdark/falling",1);
    return 1;
}

int
xthrow(string str)
{
    object *arr;/* Local variables, array of objects */
    int i;/* Local variable, integer, used in the for-loop */

    if (!str)
    {
	notify_fail("Throw what?\n");
	return 0;
    }

    arr = FIND_STR_IN_OBJECT(str, this_player());

    if (!sizeof(arr))
    {
	notify_fail("You don't have any '" + str + "'.\n");
	return 0;
    }

    for (i = 0; i < sizeof(arr); i++)
	arr[i]->move("/d/Kalad/common/wild/pass/underdark/falling");

    write("You throw " + COMPOSITE_DEAD(arr) + " off the ledge.\n");
    say(QCTNAME(this_player()) + " throws " + QCOMPDEAD + " off the ledge.\n");
    return 1;
}
