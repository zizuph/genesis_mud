/*********************************************************************
 * - sit.c                                                         - *
 * - This is the sitting room of the Gentlemans Club               - *
 * - Created by Damaris 10/2001                                    - *
 *********************************************************************/
#pragma no_clone
#pragma no_inherit
#pragma strict_types
#include <stdproperties.h>  
#include "/d/Raumdor/defs.h"
#include "../guild.h"
inherit CLUB;

#include "fireplace.c"
#include "seating2.c"
public void
create_guild_room()
{
    set_short("An informal sitting room");
    set_long("This is an informal sitting room. It is warm with "+
        "a lovely fire dancing within the depths of a large fireplace "+
        "in the southern wall. Delicate finely crafted lanterns hang "+
        "on the walls along side a few paintings.\n");
    add_item(({"room", "sitting room", "area"}), query_long);
    add_item(({"chair","chairs"}), seat_desc);
    add_my_desc(seat_desc, this_object());
    add_item(({"north", "south", "west", "northwest", "northeast",
        "southwest", "southeast"}),
        "There is a wall in that direction.\n");
    add_item(({"east"}),
        "There is a doorway in that direction.\n");
    add_item(({"lantern", "lanterns"}),
        "The lanterns are finely crafted with gold and glass and quite "+
        "delicate.\n");
    add_item(({"wall", "walls"}),
        "The walls have dark wooden panels one them with delicate gold "+
        "lanterns.\n");
    add_item(({"painting", "paintings"}),
        "There are a few paintings that have been placed upon the walls "+
        "in here. Each one has been uniquely crafted and placed in golden "+
        "frames.\n");
    add_item(({"frame", "frames"}),
        "The frames are golden and quite elegant.\n");
    add_exit("lobby", "east");
    set_no_exit_msg(({"north", "south", "west", "northeast", "northwest",
        "southeast", "southwest"}),
        "You walked into a wall!\n"+
        "Ouch! That's gotta hurt!\n");
}

public void
init()
{
    ::init();
    init_seat();
    init_fire();
}
