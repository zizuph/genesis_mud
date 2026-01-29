/* A corridor on the second floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/walkers/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";

create_room()
{
    set_short("Tower Corridor");

    set_long("Long description of this room.\n");

    add_exit(TOWER + "tower_corr_2_2.c", "south", 0, 1);
    add_exit(TOWER + "tower_corr_2_4.c", "north", 0, 1);
    add_exit(TOWER + "tower_stair_2.c", "west", 0, 1);
    add_exit(TOWER + "tower_library_1.c", "east", 0, 1); 

    make_college_room();
}