/*
 *  /d/Gondor/guilds/rangers/hq/track_task26.c
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
    set_short("At the top of a gully");
    set_long("You are perched at the top of a shallow gully in the "
        + "Druedain forest. From here the only obvious direction to "
        + "go would be down into the gully itself. All other ways "
        + "see blocked up with bushes and fallen logs.\n");
        
    add_item(({"bushes", "bush"}), "The bushes grow in thick clumps, "
        + "preventing movement beyond them.\n");
    add_item(({"log", "logs", "fallen log", "fallen logs"}), "These are "
        + "the remnants of once-great trees. Now, however, they seem to "
        + "serve no purpose beyond impeding your progress. There is something "
        + "strange about a particular fallen maple, however.\n");
    add_item(({"maple", "fallen maple", "maple tree"}), "The trunk of the "
        + "fallen maple is crumbling through decay and the ruin of time. "
        + "It looks like you might be able to get through to the northeast.\n");

    track_add_items();

    add_exit(TRACKTASK_DIR  + "gully",         "down", &allowed(), 1);
    add_exit(TRACKTASK_DIR  + "track_task22",   "northeast", &allowed(), 1, 1);

    reset_room();
}
