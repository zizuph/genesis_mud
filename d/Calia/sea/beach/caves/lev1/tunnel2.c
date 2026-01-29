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
#include "larva.h"

void
create_water_room()
{

    make_tunnel_room();
    reset_room();
    add_exit(CAVE_LEV1 + "tunnel3", "northeast", 0, 0);
    add_exit(CAVE_LEV1 + "cave_sm2", "east", 0, 0);
    add_exit(CAVE_LEV1 + "tunnel1", "southwest", 0, 0);

}

