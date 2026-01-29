/*  description: Cave room for small water
 *               krougs.  Nasty smelling,
 *               dark, and damp.
 */

#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"

inherit BASE_CAVE;
#include "medium_kroug.h"

void
create_water_room()
{

    make_cave_room();
    reset_room();
    add_exit(CAVE_LEV1 + "tunnel7", "southeast", 0, 0);

}

