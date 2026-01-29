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
        " to the north and south, while to the west you see a chamber" +
        " dominated by a huge tome.\n");
        
    add_item(({"tome", "book"}), "It is indeed a huge tome, perhaps you" +
        " should move closer if you wish to examine it in detail.\n");

    add_exit(TOWER + "tower_corr_2_3.c", "south", 0, 1);
    add_exit(TOWER + "tower_corr_2_5.c", "north", 0, 1);
    add_exit(TOWER + "tower_joinroom.c", "west", 0, 1);

    make_college_room();
}