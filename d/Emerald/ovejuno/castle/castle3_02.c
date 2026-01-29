/* Corridor-Stairs Third floor (2).
 * Coded by Marisol (12/7/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types

#include "../defs.h"

inherit CASTLE_OV3;

#include <stdproperties.h>

void
create_castle_room()
{
    set_em_long("A persistent silence wraps up the old, dusty corridor. "+
        "Some dusty lamps are hanging on the walls unlit. The walls are "+
        "in a sorry condition, all dirty and abandoned. A lonely window "+
        "stands high at the end of this corridor. There are two closed "+
        "doors on both sides of the walls. The smell of dust is quite "+
        "strong here. @@special_long@@\n");

    add_item("corridor",
        "You are standing on a dusty corridor on the third floor of "+
        "the castle.\n");    

    add_item("window",
        "A glass window hangs on the south wall. The window is "+
        "painted all in black even the glass.\n");

    add_item("south wall",
        "The south wall doesn't differ much from the rest of the walls "+
        "in the corridor. The only difference is the glass window "+
        "set high on the wall.\n");

    add_exit("castle3_01", "east");
    add_exit("castle3_03", "north");
}                                                                         

string
special_long()
{
    object last_room = this_player()->query_prop(LIVE_O_LAST_ROOM);
    string filename;

    if (!last_room)
    {
        return "As you continue walking through the corridor, you "+
            "leave the stairs room behind. ";
    }

    filename = file_name(last_room);

    if (filename == (CASTLE_DIR + "castle3_01"))
    {
        return "As you continue walking through the corridor, you "+
            "leave the stairs room behind. ";
    }

    if (filename == (CASTLE_DIR + "castle3_03"))
    {
        return "To your left, it opens up the entrance to the stair room. ";
    }

    return "To your left, the corridor opens up to the entrance of "+
        "the stairs room. ";
}                                  
