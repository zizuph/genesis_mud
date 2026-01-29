/* Stairwell on the first floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/guilds/colleges/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";

create_room()
{
    set_short("Stairwell on the first floor");

    set_long(stair_desc + " " + basic_desc + " To the west you see a" +
        " corridor and to the west, a large gathering place. A smaller" +
        " meeting room lies to the south.\n");

    add_item(({"stair", "stairs", "staircase"}), "This perfect marble" +
        " staircase is a marvel of symmetry. If the designer was standing" +
        " before you right now, you would shake his hand.\n");
    add_item(({"dome", "glass dome", "observatory"}), "You see the clear" +
        " dome of the observatory from here, but can't get a good look at" +
        " what is else up there.\n");

    add_exit(TOWER + "tower_corr_1_4.c", "east", 0, 1);
    add_exit(TOWER + "tower_public_board.c", "south", 0, 1);
    add_exit(TOWER + "tower_great_hall.c", "west", 0, 1);
    add_exit(TOWER + "tower_stair_2.c", "up", 0, 3);

    make_college_room();
}