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

    set_long(corridor_desc + " " + basic_desc + " Through an open portal to" +
        " the east lies a post office, while the corridor continues to the" +
        " north and south.\n");
        
    add_item("portal", "It's an arched, open portal.\n");

    add_exit(TOWER + "tower_corr_1_2.c", "south", 0, 1);
    add_exit(TOWER + "tower_corr_1_4.c", "north", 0, 1);
    add_exit(TOWER + "tower_post.c", "east", 0, 1);

    make_college_room();
}