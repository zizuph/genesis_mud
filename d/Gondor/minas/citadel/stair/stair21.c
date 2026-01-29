/*
 *  /d/Gondor/minas/citadel/stair/stair21.c
 *
 *  Stairwell of the White Tower: Twenty-one
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

    add_exit(INNER_MINAS + "/citadel/stair/stair22", "up", 0, 5);
    add_exit(INNER_MINAS + "/citadel/stair/stair20", "north", 0, 1);

    reset_room();
}



