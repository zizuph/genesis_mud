/* by Antharanos */
#include "/d/Kalad/defs.h"
#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>

inherit "/d/Kalad/std/room";

#define KALAD_FOUND_ROCK_EXIT "_kalad_found_rock_exit"

public void
create_kalad_room()
{
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_S_DARK_LONG,"A dark and moist place.\n");
    add_prop(OBJ_S_SEARCH_FUN, "search_ceiling");
    set_short("A dark tunnelway");
    set_long("This is a damp tunnelway located somewhere underneath the "+
      "spring in the rock plains above you. Some of the water from above "+
      "has leaked down here and has created a rather moist and cool "+
      "environment. Several mosses can be seen growing all over this "+
      "tunnel, which continues to the north.\n");
    add_item(({"damp tunnelway","tunnelway","tunnel"}),
      "A moisture-ridden underground passage.\n");
    add_item(({"water"}),
      "Surprisingly cool, it has created a moist cool environment here "+
      "where mosses can grow.\n");
    add_item(({"mosses","moss"}),
      "Green and clammy to the touch, they cover the walls and ceiling of "+
      "this tunnel.\n");
    add_item(({"walls","wall","ceiling","floor","ground"}),
      "The interior of this passage is composed of an extremely dense, "+
      "black rock, quite dissimilar to the composition of the many rocks "+
      "that lie on the rock plains above.\n");
    add_exit(CPASS(desert/rock/l2), "north");
    add_exit(CPASS(desert/rock/p34), "up", "@@exit_up", 1, 1);
}

int
exit_up()
{
    object *witnesses;
    if (TP->query_prop(KALAD_FOUND_ROCK_EXIT))
    {
        witnesses = filter(FILTER_CAN_SEE_IN_ROOM(AINV(E(TP)) - ({TP})),
                TP->check_seen);
        foreach (object witness: witnesses)
        {
            if (!witness->query_prop(KALAD_FOUND_ROCK_EXIT))
            {
                witness->add_prop(KALAD_FOUND_ROCK_EXIT, 1);
                witness->catch_msg(QCTNAME(TP) + 
                    " uses a passage hidden in the ceiling!\n");
            }
        }
        return 0;
    }
    write("There is no obvious exit up.\n");
    return 1;
}

string
search_ceiling(object me, string arg)
{
    if(arg != "ceiling")
	    return "";

    if (TP->query_skill(SS_AWARENESS) < 30)
	    return "";

    TP->add_prop(KALAD_FOUND_ROCK_EXIT, 1);
    return "You search carefully and discover a way up!\n";
}
