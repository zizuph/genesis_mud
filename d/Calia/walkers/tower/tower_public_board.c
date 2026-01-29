/* A room on the first floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/walkers/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";

create_room()
{
    set_short("Tower Public Board");

    set_long("Long description of this room.\n");

    add_exit(TOWER + "tower_stair_1.c", "north", 0, 1);

    make_college_room();
}