/* Stairwell on the second floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/guilds/colleges/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";

create_room()
{
    set_short("Stairwell on the second floor");

    set_long(stair_desc + " " + basic_desc + " To the west and east you see" +
        " corridors.\n");
        
    add_item(({"stair", "stairs", "staircase"}), "This perfect marble" +
        " staircase is a marvel of symmetry. If the designer was standing" +
        " before you right now, you would shake his hand.\n");
    add_item(({"dome", "glass dome", "observatory"}), "You see the clear" +
        " dome of the observatory from here, but can't get a good look at" +
        " what is else up there.\n");
        
    add_exit(TOWER + "tower_corr_2_6.c", "west", 0, 1);
    add_exit(TOWER + "tower_corr_2_3.c", "east", 0, 1);
    add_exit(TOWER + "tower_stair_1.c", "down", 0, 1);
    add_exit(TOWER + "tower_stair_3.c", "up", 0, 3);

    make_college_room();
}