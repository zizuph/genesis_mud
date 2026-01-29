/* A corridor on the second floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/guilds/colleges/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";

create_room()
{
    set_short("Tower Corridor");
    
    set_long(corridor_desc + " " + basic_desc + " The corridor continues" +
        " to the east, to the west you see a staircase.\n");

    add_exit(TOWER + "tower_stair_2.c", "east", 0, 1);
    add_exit(TOWER + "tower_corr_2_7.c", "west", 0, 1);

    make_college_room();
}