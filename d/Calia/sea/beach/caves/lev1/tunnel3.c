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
    add_exit(CAVE_LEV1 + "cave_sm3", "northeast", 0, 0);
    add_exit(CAVE_LEV1 + "tunnel2", "southwest", 0, 0);
    add_exit(CAVE_LEV1 + "tunnel4", "northwest", 0, 0);

}

