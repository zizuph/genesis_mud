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

    set_long(corridor_desc + " " + basic_desc + " Through an open portal" +
        " to" +
        " your east lies a banking facility, while a stairwell can be found" +
        " to the west. The corridor continues to the north and south.\n");
        
    add_item(({"portal", "portals"}), "They are arched, open portals.\n");

    add_exit(TOWER + "tower_corr_1_5.c", "north", 0, 1);
    add_exit(TOWER + "tower_corr_1_3.c", "south", 0, 1);
    add_exit(TOWER + "tower_bank.c", "east", 0, 1);
    add_exit(TOWER + "tower_stair_1.c", "west", 0, 1);

    make_college_room();
}