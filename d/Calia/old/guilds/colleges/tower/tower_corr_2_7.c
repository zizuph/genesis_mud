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
        " to the east, while from the south you feel the unmistakable smell" +
        " of food being prepared.\n");

    add_exit(TOWER + "tower_corr_2_6.c", "east", 0, 1);
    add_exit(TOWER + "tower_cantina.c", "south", 0, 1);

    make_college_room();
}