/*
 *  /d/Gondor/guilds/rangers/hq/track_task11.c
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
    set_short("Below the south side of a hill");
    set_long("The path leads around the southern edge of a small hill in "
        + "the forest. From here you can circle to the northwest or the "
        + "northeast. The trees to the south grow very close together and "
        + "darkness gathers beneath their boughs.\n");

    track_add_items();
    
    add_item(({"hill", "small hill"}), "The hill is largely devoid of trees, "
        + "which makes it seem a bald spot rising out of the surrounding forest.\n");
    add_item(({"bough", "boughs"}), "The boughs of the surrounding trees shield "
        + "out most of the light that might otherwise illuminate the forest "
        + "interior.\n");
    add_item(({"tree", "trees"}), "Although the trees grow very close together, "
        + "there seems to be a space large enough to pass between them to the "
        + "southwest.\n");
        
    add_exit(TRACKTASK_DIR + "track_task9", "northeast", &allowed(), 1);
    add_exit(TRACKTASK_DIR + "track_task17", "northwest", &allowed(), 1);
    add_exit(TRACKTASK_DIR + "track_task19", "southwest", &allowed(), 1, 1);

    reset_room();
}
