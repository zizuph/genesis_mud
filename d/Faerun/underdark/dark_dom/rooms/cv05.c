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
    add_std_herbs("underground");

//    add_prop(OBJ_S_SEARCH_FUN, "search_ceiling");
    add_prop(ROOM_I_LIGHT,0);

    set_short("On a narrow ledge");
    set_long("This is a precariously narrow ledge of rock overlooking a " +
        "seemingly bottomless pit. The cave is quite large but most of " +
        "it is open air because of the chasm. Impenetrable darkness lies " +
        "below and surrounds you, and partially hides the ceiling. There " +
        "is a ledge on the other side of the chasm. The ceiling arches overhead.\n");
    add_item(({"narrow ledge","ledge"}),
        "This jutting shelf of rock looks barely large enough to hold you " +
//        "and perhaps a few others.\n");
        "and perhaps a few others. There are some well worn steps leading down.\n");
    add_item(({"bottomless pit", "pit", "chasm"}),
      "It is a yawning hole that seems to go down forever. Peering into the pit, " +
      "it's full of darkness.\n");
    add_item(({"impenetrable darkness", "darkness"}),
        "It fills the bottomless pit. It's seems to suck all light into it.\n");
    add_item("ceiling",
//        "It overhangs the ledge, partially hidden in shadows and darkness. There are some well worn steps leading down.\n");
        "It overhangs the ledge, partially hidden in shadows and darkness.\n");
    add_item(({"steps", "well worn steps", "well-worn steps"}),
        "They are well worn indentations cut into the cave.\n");

    reset_room();

    add_exit(TUN_DIR + "cv04", "up");
    add_exit(TUN_DIR + "cv06", "down");
}

void kill_exit()
{
    write("The exit suddenly flickers and disappears.\n");
    remove_exit("up");
    return ;
}    

public string
search_ceiling(object me, string arg)
{
    if (arg != "ceiling")
        return "";
    if (this_player()->query_skill(SS_AWARENESS) < 30)
        return "";
    add_exit(TUN_DIR + "cv04", "up");
//    set_alarm(90.0,0.0,"remove_exit","up");
    set_alarm(90.0,0.0,"kill_exit");
    return "You search the ceiling carefully and discover a hidden exit " +
        "leading up. It looks magical and probably disappears if not used quickly.\n";
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
//    notify_fail("Climb where, up or down?\n");
    notify_fail("Climb down?\n");

    if (!str || str != "down")
	return 0;

    this_player()->move_living("climbing down", TUN_DIR + "cv06", 1);
    this_player()->add_fatigue(-5);
    return 1;
}

int
jump(string str)
{
    if(str != "across chasm")
    {
        write("Jump where, across chasm?\n");
        return 1;
    }

    write("You try to jump as high as possible and you slip. It seems to " +
      "be a long way down ...\n");
    say(QCTNAME(this_player()) + " foolishly tries to jump across the " +
        "chasm and falls off the ledge.\n");

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

void
reset_room()
{
    set_searched(0);
}