/*  description: Cave LEV1 for small water
 *               krougs.  Nasty smelling,
 *               dark, and damp.
 */

#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"

inherit BASE_CAVE;
#include "larva.h"

void
create_water_room()
{

    make_tunnel_room();
    reset_room();
    add_exit(CAVE_LEV1 + "cave_sm1.c", "east", 0, 0);
    add_exit(CAVE_LEV1 + "tunnel10", "west", 0, 0);
    add_exit(CAVE_LEV1 + "entrance", "up", 0, 0);
    add_exit(CAVE_LEV1 + "tunnel2", "northeast", 0, 0);

}

