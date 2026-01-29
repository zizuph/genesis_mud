/*
 *  /d/Shire/bree/rooms/town/stable/stable_yard.c
 *
 *  The stable yard of the Bree Stables
 *
 *  By, Palmer
 *  Date December 2002
 */

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "stables.h"
#include <stdproperties.h>
#include <terrain.h>

// this is a base file for outdoor rooms in Faerun
inherit FAERUN_OUTDOOR_BASE;

void
create_faerun_room()
{
    set_short("In the stable yard");
    set_long("This is the stable yard. The paved inn yard ends here and opens up into a dirt yard. To the northeast is a large wooden building. The stable yard continues to the east.\n");
    add_item("shop", 
        "A shop of some sort. The entrance is rather large.\n");
    add_item("entrance", 
        "The entrance to the shop is very wide. Wide enough for a horse to pass through.\n");
    add_item(({"dirt yard", "yard", "ground"}), 
        "The dirt yard is level and free of debris.\n");
    add_item(({"building", "stable", "stables", "wooden building", "large wooden building"}), 
        "The large wooden building to the northeast seems to be " +
        "a stable, judging from the sounds and smells coming from that way.\n");
    add_prop(ROOM_I_INSIDE, 0);
    add_exit("east_yard", "east", 0, 0);
    add_exit("tack_shop", "south", 0, 0);
}
