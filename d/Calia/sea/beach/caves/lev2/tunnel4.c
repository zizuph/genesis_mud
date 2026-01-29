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

    make_underwater_tunnel();
    reset_room();
    add_exit(CAVE_LEV2 + "tunnel3", "southeast", 0, 0);
    add_exit(CAVE_LEV2 + "cave_large4", "north", 0, 0);
    add_exit(CAVE_LEV2 + "tunnel5", "west", 0, 0);

}

