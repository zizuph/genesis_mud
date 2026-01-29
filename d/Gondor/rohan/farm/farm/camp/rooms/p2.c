/*
 * Dunlending Camp Outdoor Room
 *
 * --Raymundo, March 2020
 */

#pragma strict_types

inherit "/d/Gondor/rohan/farm/farm/camp/lib/base_room";

#include <macros.h>
#include "/d/Gondor/defs.h"
#include "defs.h"


object guard;

int
block_people()
{
    object ob;
    if(objectp(ob = present("_dunlending_warrior_")))
    {
        write("The " + ob->query_short() + " prevents you from "
            + "walking that way.\n");
        return 1;
    }
    return 0;
}

void
create_dunlending()
{
    set_short("On the path");
    set_long("Golden wheat grows tall in fields on each side of the path. "
        + "Stalks of wheat (and some weeds) sway gently in the wind. "
        + "To the northwest is a farmhouse. You see smoke rising from "
        + "it, quite a lot actually. Southeast the path continues toward "
        + "an ancient forest.\n");

    add_cmd_item( "carefully", "listen", "You can't make out every word "
        + "but you do hear 'farm', 'wife', and some laughter.\n");

    add_exit(CAMP_ROOM_DIR + "p1", "west");
    add_exit(CAMP_ROOM_DIR + "p3", "southeast", 0, 0, 0);

    path_adds();
    add_guard_down();
}
void
reset_room()
{
    set_searched(0);
    if(!present("dunlending"))
    {
        add_guard_down();
    }
   
    
}



