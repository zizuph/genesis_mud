/*
 *  /d/Gondor/guilds/rangers/hq/track_task22.c
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
    set_short("A meeting of paths");
    set_long("The animal track you have been following crosses that "
        + "of another here. One path seems to run in an east-west "
        + "direction while the other follows a northeast-southeast "
        + "bend. In all other directions, the way seems blocked "
        + "by bushes and fallen logs.\n");
        
    add_item(({"bushes", "bush"}), "The bushes grow in thick clumps, "
        + "preventing movement beyond them.\n");
    add_item(({"log", "logs", "fallen log", "fallen logs"}), "These are "
        + "the remnants of once-great trees. Now, however, they seem to "
        + "serve no purpose beyond impeding your progress. There is something "
        + "strange about a particular fallen maple, however.\n");
    add_item(({"maple", "fallen maple", "maple tree"}), "The trunk of the "
        + "fallen maple is crumbling through decay and the ruin of time. "
        + "It looks like you might be able to get through to the southwest.\n");

    track_add_items();

    add_exit(TRACKTASK_DIR  + "track_task21",   "east", &allowed(), 1);
    add_exit(TRACKTASK_DIR  + "track_task23",   "west", &allowed(), 1);
    add_exit(TRACKTASK_DIR  + "track_task24",   "northeast", &allowed(), 1);
    add_exit(TRACKTASK_DIR  + "track_task25",   "southeast", &allowed(), 1);
    add_exit(TRACKTASK_DIR  + "track_task26",   "southwest", &allowed(), 1, 1);

    reset_room();
}
