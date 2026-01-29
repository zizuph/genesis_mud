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

void
create_water_room()
{

    make_tunnel_room();
    reset_room();
    add_exit(CAVE_LEV1 + "tunnel9", "west", 0, 0);
    add_exit(CAVE_LEV1 + "tunnel1", "east", 0, 0);
    add_exit(CAVE_LEV1 + "cave_med5", "north", 0, 0);

}

