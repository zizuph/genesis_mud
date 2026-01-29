/* Stairwell on the fifth floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/walkers/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";

create_room()
{
    set_short("Stairwell on the fifth floor");

    set_long("Long description of this room.\n");

    add_exit(TOWER + "tower_stair_4.c", "down", 0, 1);
    add_exit(TOWER + "tower_stair_6.c", "up", 0, 3);

    make_college_room();
}