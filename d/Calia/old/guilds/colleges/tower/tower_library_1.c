/* A room on the second floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/guilds/colleges/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";


create_room()
{
    set_short("Tower Library, Submissions Section");

    set_long("Long description of this room.\n");

    add_exit(TOWER + "tower_corr_2_3.c", "west", 0, 1);
    add_exit(TOWER + "tower_library_2.c", "south", 0, 1);
    add_exit(TOWER + "tower_study.c", "north", 0, 1);

    make_college_room();
}