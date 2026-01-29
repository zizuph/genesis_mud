/*
 * Beach in Gont
 * By Finwe
 * April 1997
 */

#pragma strict_types
#pragma no_clone
 
#include "default.h"
#include <stdproperties.h>
 
inherit ROCKY;
 
public void
create_beach()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    add_my_desc("The rocky beach widens here as it heads " +
        "southeast. A cliff blocks further traffic to the " +
        "north from here.\n");
    add_item (({"beach", "rocky beach"}),
        "The beach is rocky with broken boulders from the " +
        "cliff and from rocks that have come in with " +
	"the tide.\n");
    add_item("cliff",
        "The cliff towers over the sandy beach. It " +
	"is impossible to climb over.\n");
 
    add_exit("beach02", "southeast");
}
