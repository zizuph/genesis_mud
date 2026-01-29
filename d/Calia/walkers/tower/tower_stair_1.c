/* Stairwell on the first floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/walkers/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";

create_room()
{
    set_short("Stairwell on the first floor");

    set_long("Long description of this room.\n");

    add_exit(TOWER + "tower_corr_1_4.c", "east", 0, 1);
    add_exit(TOWER + "tower_public_board.c", "south", 0, 1);
    add_exit(TOWER + "tower_great_hall.c", "west", 0, 1);
    add_exit(TOWER + "tower_stair_2.c", "up", 0, 3);

    make_college_room();
}