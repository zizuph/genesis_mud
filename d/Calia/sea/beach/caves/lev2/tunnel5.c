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

    make_underwater_tunnel();
    reset_room();
    add_exit(CAVE_LEV2 + "tunnel4", "east", 0, 0);
    add_exit(CAVE_LEV2 + "tunnel6", "west", 0, 0);
    add_exit(CAVE_LEV2 + "cave_large5", "northwest", 0, 0);
    add_exit(CAVE_LEV1 + "tunnel5", "up", 0, 0);

}

