/* A corridor on the first floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/walkers/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";

create_room()
{
    set_short("Tower Corridor");

    set_long(corridor_desc + " " + basic_desc + " The corridor continues" +
        " to the north and east.\n");

    add_exit(TOWER + "tower_corr_1_1.c", "east", 0, 1);
    add_exit(TOWER + "tower_corr_1_3.c", "north", 0, 1);

    make_college_room();
}