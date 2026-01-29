/* A corridor on the first floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/guilds/colleges/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";

create_room()
{
    set_short("Tower Corridor");

    set_long(corridor_desc + " " + basic_desc + " A stairwell can be found" +
        " to the west. The corridor continues to the north and south.\n");
        
    add_exit(TOWER + "tower_corr_1_5.c", "north", 0, 1);
    add_exit(TOWER + "tower_corr_1_3.c", "south", 0, 1);
    add_exit(TOWER + "tower_stair_1.c", "west", 0, 1);

    make_college_room();
}