/*
 *  /d/Gondor/guilds/rangers/hq/track_task10.c
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
    set_short("Below the north side of a hill");
    set_long("The path leads around the northern edge of a small hill in "
        + "the forest. From here you can circle to the southwest or the "
        + "southeast. The trees to the north grow so close together that "
        + "there appears to be no easy way to enter the forest from here.\n");

    track_add_items();
    
    add_item(({"hill", "small hill"}), "The hill is largely devoid of trees, "
        + "which makes it seem a bald spot rising out of the surrounding forest.\n");
        
    add_exit(TRACKTASK_DIR + "track_task9", "southeast", &allowed(), 1);
    add_exit(TRACKTASK_DIR + "track_task17", "southwest", &allowed(), 1);

    reset_room();
}
