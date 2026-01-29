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
#define KILLER "i_kill_dunlendings"

object guard;

int
block_people()
{
    object ob;
    if(objectp(ob = present("_dunlending_warrior_")) 
        && TP->query_prop(KILLER))
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
    set_long("You stand on a small dirt path between two fields. Far "
        + "to the northwest is a farm, while to the southeast is a "
        + "large forest. If you listen carefully, you can hear the "
        + "sounds of people talking in the forest.\n");

    add_cmd_item( "carefully", "listen", "You can't make out every word "
        + "but you do hear 'farm', 'wife', and some laughter.\n");

    add_exit(CAMP_ROOM_DIR + "p2", "northwest");
    add_exit(CAMP_ROOM_DIR + "m1", "southeast", block_people, 0, 0);

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



