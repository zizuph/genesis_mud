/*
 *  /d/Gondor/guilds/rangers/hq/track_task29.c
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
    set_short("A closed glade");
    set_long("There seems to be no way out of this place. All directions seem "
        + "blocked by bushes and fallen logs.\n");
        
    add_item(({"glade", "closed glade"}), "There seems to be no way to exit this "
        + "glade. Trees grow densely about you on all side, and the spaces "
        + "between them are blocked with bushes and logs.\n");
    add_item(({"bushes", "bush"}), "The bushes grow in thick clumps, "
        + "preventing movement beyond them.\n");
    add_item(({"log", "logs", "fallen log", "fallen logs"}), "These are "
        + "the remnants of once-great trees. Now, however, they seem to "
        + "serve no purpose beyond impeding your progress. There is something "
        + "strange about a particular fallen oak, however.\n");
    add_item(({"oak", "fallen oak", "oak tree"}), "The trunk of the "
        + "fallen oak is crumbling through decay and the ruin of time. "
        + "It looks like you might be able to get through to the northeast.\n");

    track_add_items();

    add_exit(TRACKTASK_DIR  + "track_task25",   "northeast", &allowed(), 1, 1);

    reset_room();
}
