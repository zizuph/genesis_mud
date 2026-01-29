/* A room on the second floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/walkers/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";


create_room()
{
    set_short("Tower Council Chambers");

    set_long("Long description of this room.\n");

    add_exit(TOWER + "tower_corr_2_1.c", "east", 0, 1);

    make_college_room();
}