/*
 *  /d/Gondor/guilds/rangers/hq/track_task19.c
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
    set_short("At the top of a ravine");
    set_long("You are perched at the top of a shallow ravine in the "
        + "Druedain forest. From here the only obvious direction to "
        + "go would be down into the ravine itself. All other ways "
        + "see blocked up with bushes and fallen logs.\n");
        
    add_item(({"bushes", "bush"}), "The bushes grow in thick clumps, "
        + "preventing movement beyond them. It looks like there might "
        + "be enough room to go northeast, however.\n");
    add_item(({"log", "logs", "fallen log", "fallen logs"}), "Dead and "
        + "decaying logs are strewn about the area, preventing passage "
        + "in most directions.\n");

    track_add_items();

    add_exit(TRACKTASK_DIR  + "ravine",         "down", &allowed(), 1);
    add_exit(TRACKTASK_DIR  + "track_task11",   "northeast", &allowed(), 1, 1);

    reset_room();
}
