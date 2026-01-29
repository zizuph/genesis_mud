/*
 * Tunnel room in Underdark
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_TUNNEL;

void
create_tunnel()
{
    add_prop(OBJ_S_SEARCH_FUN, "search_ceiling");
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_M_NO_TELEPORT,1);

    set_short("On a narrow ledge");
    set_long("You are on a precariously narrow ledge of rock, overlooking "+
      "a seemingly bottomless pit. The room you are within is quite large, "+
      "however most of it is open air, because of the chasm. Impenetrable "+
      "darkness lies below you.\n");
    add_item(({"narrow ledge","ledge"}),
        "This jutting shelf of rock looks barely large enough to hold you " +
        "and perhaps a few others.\n");
    add_item(({"bottomless pit", "pit", "chasm"}),
      "It is a yawning hole seems to go down forever. Peering into the pit, " +
      "it's full of darkness.\n");
    add_item(({"impenetrable darkness", "darkness"}),
        "it fills the bottomless pit. It's seems to suck all light into it.\n");
}

public string
search_ceiling(object me, string arg)
{
    if (arg != "ceiling")
	return "";
    if (this_player()->query_skill(SS_AWARENESS) < 30)
	return "";
    add_exit(TUN_DIR + "u04", "up");
    set_alarm(12.0,0.0,"remove_exit","up");
    return "You search the ceiling carefully and discover a hidden exit leading up.\n";
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

    this_player()->move_living("climbing down", TUN_DIR + "u06", 1);
    this_player()->add_fatigue(-5);
    return 1;
}

int
jump(string str)
{
    write("You try to jump as high as possible and you slip. It's seems to " +
      "be a long\nway down....\n");
    say(QCTNAME(this_player()) + " foolishly jumps and falls from the ledge.\n");

    this_player()->move_living("M", TUN_DIR + "falling",1);
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
	arr[i]->move(TUN_DIR + "falling");

    write("You throw " + COMPOSITE_DEAD(arr) + " off the ledge.\n");
    say(QCTNAME(this_player()) + " throws " + QCOMPDEAD + " off the ledge.\n");
    return 1;
}
