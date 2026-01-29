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
#include "xlarge_kroug.h"

void
create_water_room()
{

    make_underwater_cave();
    reset_room();
    add_exit(CAVE_LEV2 + "tunnel10", "south", 0, 0);

}

