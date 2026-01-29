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
    
    set_long(corridor_desc + " " + basic_desc + " An open portal leads" +
        " west, into an herbalist's shop. The corridor continues to the" +
        " north and south.\n");
    
    add_item("portal", "It's an arched, open portal.\n"); 
    
    add_exit(TOWER + "tower_corr_1_6.c", "north", 0, 1);
    add_exit(TOWER + "tower_corr_1_4.c", "south", 0, 1);
    add_exit(TOWER + "tower_herbalist.c", "west", 0, 1);

    make_college_room();
}