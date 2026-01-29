/* Stairwell on the second floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/walkers/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";

create_room()
{
    set_short("Stairwell on the second floor");

    set_long("Long description of this room.\n");

    add_exit(TOWER + "tower_corr_2_6.c", "west", 0, 1);
    add_exit(TOWER + "tower_corr_2_3.c", "east", 0, 1);
    add_exit(TOWER + "tower_stair_1.c", "down", 0, 1);
    add_exit(TOWER + "tower_stair_3.c", "up", 0, 3);

    make_college_room();
}