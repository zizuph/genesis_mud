/*
 *  /d/Gondor/minas/citadel/stair/stair7.c
 *
 *  Stairwell of the White Tower: Seven
 *
 *  Alto, 20 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/minas/lib/dinen_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"


public void
create_gondor()
{
    add_stair_items();

    add_exit(INNER_MINAS + "/citadel/stair/stair8", "up", 0, 5);
    add_exit(INNER_MINAS + "/citadel/stair/stair6", "east", 0, 1);

    reset_room();
}



