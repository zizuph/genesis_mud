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

    set_long(corridor_desc + " " + basic_desc + " Open portals lead" +
        " west and east, into an alchemist's shop and an equipment store" +
        " respectively. To the south the corridor continues.\n");

    add_item(({"portal", "portals"}), "They are arched, open portals.\n"); 

    add_exit(TOWER + "tower_corr_1_5.c", "south", 0, 1);
    add_exit(TOWER + "tower_alchemist.c", "west", 0, 1);
    add_exit(TOWER + "tower_shop.c", "east", 0, 1);

    make_college_room();
}