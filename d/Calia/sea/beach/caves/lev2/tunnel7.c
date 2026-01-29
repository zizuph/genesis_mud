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
    add_exit(CAVE_LEV2 + "tunnel6", "northeast", 0, 0);
    add_exit(CAVE_LEV2 + "cave_xlarge3", "northwest", 0, 0);
    add_exit(CAVE_LEV2 + "tunnel8", "southwest", 0, 0);

}

