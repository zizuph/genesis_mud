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

    set_long(corridor_desc + " " + basic_desc + " The corridor continues" +
        " to the west, while a gate to the east leads out of the" +
        " Tower.\n");

    add_item("gate", "The gate is unlocked and you would have no problems" +
        " passing through it.\n");

    add_exit(TOWER + "tower_corr_1_2.c", "west", 0, 1);
    add_exit(TOWER + "tower_outside1.c", "out", 0, 1);

    make_college_room();
}
