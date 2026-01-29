/*
 *  /d/Gondor/guilds/rangers/hq/track_task17.c
 *
 *  A room for the rabbit tracking apprentice task
 *
 *  Coded by Alto, 07 December 2002
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "../../rangers.h"

inherit TRACKTASK_DIR + "tracktask_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_gondor()
{
    set_short("At the bottom of a hill");
    set_long("The path leads to the bottom of a small hill in the Druedain "
        + "forest. From here, the path splits into three directions. You may "
        + "follow it around the northern or southern margins of the hill, or "
        + "take a climbing route up the hill itself.\n");

    track_add_items();
    
    add_item(({"hill", "small hill"}), "The hill is largely devoid of trees, "
        + "which makes it seem a bald spot rising out of the surrounding forest.\n");
        
    add_exit(TRACKTASK_DIR + "track_task18", "west", &allowed(), 1);
    add_exit(TRACKTASK_DIR + "track_task10", "northeast", &allowed(), 1);
    add_exit(TRACKTASK_DIR + "track_task11", "southeast", &allowed(), 1);
    add_exit(TRACKTASK_DIR + "track_task16", "uphill", &allowed(), 1);

    reset_room();
}
